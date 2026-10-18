# Binary Search Tree

- 효율적인 탐색, 삽입, 삭제를 위해 각 노드가 특정한 크기 규칙을 따르는 이진 트리 자료구조
- 왼쪽 서브트리는 부모 노드보다 작은 값들만 포함
- 오른쪽 서브트리는 부모 노드보다 큰 값들만 포함
- **Inorder traversal** 로 정렬
	- 위 서브트리 규칙에 의함
	- left -> node -> right 순서의 방문은 오름차순이 된다.

- 균형 잡힌 상태의 연산(탐색, 삽입, 삭제)는 $O(\log N)$ 의 시간복잡도를 따른다.
- key의 삽입 순서에 따라 편향된 상태 (마치 singly linked list같은 상태)가 된다면 위 연산의 시간복잡도가 $O(N)$ 이 된다.

---

## 구현(C)

- Node 구조체 (data, rlink, llink)
- BST 객체 구조체 (root)

- 연산
	- bst_search() : 삽입
	- bst_delete() : 삭제
	- bst_print_inorder() : 중위순회 및 출력
	- bst_destroy() : tree 객체 전체 삭제

- 삽입과 삭제에서 key를 찾아가는 탐색을 공통으로 사용하여 탐색 내부함수를 따로 구현했다.
	- search연산은 key값이 들어있는 (중복) node로 가거나 key값이 들어가야 할 node의 부모 node로 가도 무관하다.
	- delete연산은 key값이 들어있는 node의 부모 node로 가야하며 존재 시에도 부모 node로 가야한다.
	- 부모 node를 반환할 시에 rlink 혹은 llink 둘 중 어디를 연결/삭제해야 할지 추가 연산이 필요한 단점이 생겼다.
		- rlink, llink, root 포인터 변수의 주소를 반환하기로 했다.
		- `Node**` : 이중 포인터를 사용했다.
			- 탐색 함수가 탐색을 전부 담당할 수 있어 가장 깔끔하다.

- 삭제 연산에서 삭제 node의 자식이 둘인 경우는 오른쪽 서브트리의 최소값 node 혹은 왼쪽 서브트리의 최댓값 node로 대체하는 방식을 사용할 수 있다.

- 순회
	- 중위순회는 재귀로 구현하였다.
	- Call Stack의 원리 (LIFO)를 따라 다음과 같이 코드를 작성하였다.

```c
static void _inorder(Node* node) {
        // 종료 조건 : leaf node link 타고 간 NULL node일 경우
	    // *NULL : UB 방지
	    // 재귀 함수 작성 시 종료 조건 작성은 필수
        if (node == NULL) return;
        // 왼쪽 자식 방문
        _inorder(node->llink);
        // 현재 노드 방문 (출력)
        printf("%d ", node->data);
        // 오른쪽 자식 방문
        _inorder(node->rlink);
}
```



