#include <stdio.h>
#include <stdlib.h>
 
typedef int Element;
 
typedef struct Node {
	Element data;
	struct Node *rlink;
	struct Node *llink;
} Node;
 
typedef struct Bst {
	Node *root;
} Bst;



/* ---------------------------------------- */
// private method
/* ---------------------------------------- */



/*
- plink : link의 주소 (rlink, llink, root)
	- plink를 사용하면 root 예외 처리가 불필요
- 반환값 : key node/key node가 될 자리의 주소를 가리키는 link의 주소
	- *plink == NULL : key 존재X
	- *plink != NULL : key 존재
*/
static Node** _find_link(Bst* bst, Element key) {
	Node** plink = &(bst->root);
	
	// *plink != NULL : key가 존재하지 않는 경우
	// (*plink)->data != key : data와 key가 같을 경우 plink 갱신하지 않고 loop 종료 
	while (*plink != NULL && (*plink)->data != key) {
		if ((*plink)->data < key) {
			plink = &((*plink)->rlink);
		}
		else {
			plink = &((*plink)->llink);
		}
	}
 
	return plink;
}

static void _destroy(Node* node) {
	// leaf node 도달 시 재귀 종료
	if (node == NULL) return;
	
	_destroy(node->llink);
	_destroy(node->rlink);

	free(node);
}

static void _inorder(Node* node) {
	// leaf node 도달 시 재귀 종료
	if (node == NULL) return;
	// 왼쪽 자식 방문
	_inorder(node->llink);
	// 현재 노드 방문 (출력)
	printf("%d ", node->data);
	// 오른쪽 자식 방문
	_inorder(node->rlink);
}



/* ---------------------------------------- */
// public method (사용자 함수)
/* ---------------------------------------- */



// BST 생성. 실패 시 NULL 반환
Bst* bst_create() {
	Bst* bst = (Bst*)malloc(sizeof(Bst));
	if (!bst) {
		printf("error: malloc fail\n");
		return NULL;
	}
 
	bst->root = NULL;
	return bst;
}
 
// key 삽입. 1: 성공, 0: 실패 (중복 key 또는 malloc 실패)
int bst_insert(Bst* bst, Element key) {
	Node** plink = _find_link(bst, key); // plink : link를 가리키는 포인터 변수
 
	// node data == key : error
	if (*plink != NULL) {
		printf("error: key already exist\n");
		return 0;
	}
 
	// node 생성
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node) {
		printf("error: malloc fail\n");
		return 0;
	}
 
	node->data = key;
	node->llink = NULL;
	node->rlink = NULL;
 
	// 새로 만든 node의 주소값을 현재 link에 넣어 연결
	*plink = node;
	return 1;
}

int bst_delete(Bst* bst, Element key) {
	Node** plink = _find_link(bst, key);
 
	// target node로의 link를 해제해야 하기 때문에 target node 주소를 따로 저장
	Node* target = *plink; // target : delete node 주소
 
	// link doesn't exist (삭제할 key node가 존재하지 않는 경우 삭제 실패처리)
	if (target == NULL) {
		printf("error: key doesn't exist\n");
		return 0;
	}
 
	// target의 자식 node가 하나인 경우 target의 부모 node와 target의 자식 node만 연결하면 끝난다.
	// target의 자식이 0개 혹은 오른쪽 자식만 있는 case
	if (target->llink == NULL) {
		*plink = target->rlink;
	}
	// target이 왼쪽 자식만 있는 case
	else if (target->rlink == NULL) {
		*plink = target->llink;
	}
	// target이 두 자식 node를 모두 가지고 있을 때
	// target의 오른쪽 subtree의 최솟값 node(successor)으로 target 위치를 대체
	else {
		// successor node를 가리키는 link 찾기
		Node** succ_link = &(target->rlink);
		while ((*succ_link)->llink != NULL) {
			succ_link = &((*succ_link)->llink);
		}
		
		Node* successor = *succ_link;
		
		// succ_link에서 successor 분리
		*succ_link = successor->rlink;
 
		// successor를 target 위치로 이동 (plink에 연결 및 target의 llink, rlink 계승)
		successor->llink = target->llink;
		successor->rlink = target->rlink;
		*plink = successor;
	}
 
	free(target);
	return 1;
}

void bst_print_inorder(Bst* bst) {
	_inorder(bst->root);
	printf("\n");
}

void bst_destroy(Bst* bst) {
	_destroy(bst->root);
	free(bst);
}





int main() {
	Bst *myBst = bst_create();
	
	bst_insert(myBst, 10);
	bst_insert(myBst, 5);
	bst_insert(myBst, 15);
	bst_insert(myBst, 1);
	bst_insert(myBst, 6);

	bst_print_inorder(myBst);
	
	bst_delete(myBst, 5);

	bst_print_inorder(myBst);

	return 0;
} 
