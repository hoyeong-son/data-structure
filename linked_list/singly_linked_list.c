#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element; //list에 담을 data type : Element (default : int로 설정)

// node struct : data, 다음 node 주소를 담을 포인터 변수 (자기 참조 구조체)
typedef struct Node {
	Element data;
	struct Node *link;
} Node;

// list struct
typedef struct List {
	Node *head;
} List;

/* Method 정의 */
void init(List*); //list 초기화 (반드시 최초 1회만 실행), clear을 하지 않고 init 실행 시 메모리 누수 발생
bool is_empty(List*);
void insert_first(List*, Element);
void delete_first(List*);
void insert_last(List*, Element);
void delete_last(List*);
void insert(List*, int idx, Element); // index 원소 삽입 (first index : 0)
void delete(List*, int idx); // index 원소 삭제
void clear(List*); // list 객체를 더 이상 사용하지 않는다면 반드시 clear() 함수를 통해 메모리 해제를 해야한다.
void display(List*); // 모든 원소 출력



int main() {
	List myList;
	init(&myList);
	
	int command, idx, value;
	
	/* data type : int */ // list type 변경 방법 : typedef (int) Element 변경 후 switch-case문의 format specifier 변경
	while (1) {
		printf("\n1: insert_first 2: insert_last 3: insert(idx)\n4: delete_first 5: delete_last 6: delete(idx)\n7: display 8: clear 0: exit\n");
		
		scanf("%d", &command);
		if (command == 0) break;
		
		switch (command) {
		case 1:
			printf("Value: ");
			scanf("%d", &value);
			insert_first(&myList, value);
			break;
		case 2:
			printf("Value: ");
			scanf("%d", &value);
			insert_last(&myList, value);
			break;
		case 3:
			printf("idx value: ");
			scanf("%d %d", &idx, &value);
			insert(&myList, idx, value);
			break;
		case 4:
			delete_first(&myList);
			break;
		case 5:
			delete_last(&myList);
			break;
		case 6:
			printf("idx: ");
			scanf("%d", &idx);
			delete(&myList, idx);
			break;
		case 7:
			display(&myList);
			break;
		case 8:
			clear(&myList);
			break;
		default:
			printf("error : Invalid command\n");
			continue;
		}

	}

	return 0;

}



void init(List *list) {
	list->head = NULL;
}

bool is_empty(List *list) {
	return list->head == NULL;
}

void insert_first(List *list, Element value) {
	// node 메모리 할당
	Node *n = malloc(sizeof(Node));
	// malloc : 메모리 동적 할당 실패 NULL 반환 (우선은 return으로 처리)
	if (n == NULL) {
		return;
	}

	n->data = value;
	// link 갱신
	n->link = list->head;
	list->head = n;
}

void delete_first(List *list) {
	if (list->head == NULL) {
		printf("error : List is empty\n");
		return;
	}
	
	// link 갱신
	Node *deleted = list->head;
	list->head = deleted->link;

	// 첫번째 node 동적 할당 해제
	free(deleted);
}

void insert_last(List *list, Element value) {
	Node *n = malloc(sizeof(Node));
	
	if (n == NULL) {
		return;
	}
	
	n->data = value;
	n->link = NULL;
	
	Node *current = list->head;
	// 예외처리 current == NULL, NULL->link (UB) 발생 방지
	if (current == NULL) {
		list->head = n;
		return;
	}

	while (current->link != NULL) {
		current = current->link;
	}

	current->link = n;
}

void delete_last(List *list) {
	Node *current = list->head;
	// data : 0
	if (current == NULL) {
		printf("error : List is empty\n");
		return;
	}
	// data : 1
	else if (current->link == NULL) {
		free(current);
		list->head = NULL;
		return;
	}
	else {
		// 다음 node가 last node일때까지 반복
		while (current->link->link != NULL) {
			current = current->link;
		}
		free(current->link);
		current->link = NULL;
	}
}

// insert, delete 함수의 loop문(순차 접근)이 중복

void insert(List* list, int idx, Element value) {

	if (idx < 0) {
		printf("error : Invalid index\n");
		return;
	}
	
	// idx == 0일 경우 while문을 돌지 않고 1번 index에 insert 해버림 (예외 처리)
	if (idx == 0) {
		insert_first(list, value);
		return;
	}

	Node *current = list->head;
	int current_idx = 0;
	
	// idx-1번째 노드까지 이동, 도중에 NULL이면 범위 초과
	while (current != NULL && current_idx < idx - 1) {
		current = current->link;
		current_idx++;
	}
	if (current == NULL) {
		printf("error : Invalid index\n");
		return;
	}
	
	Node *n = malloc(sizeof(Node));
	if (n == NULL) {
		return;
	}

	n->data = value;
	n->link = current->link;
	current->link = n;
}

void delete(List* list, int idx) {

	if (idx < 0) {
		printf("error : Invalid index\n");
		return;
	}

	// idx == 0일 경우 while문을 돌지 않고 1번 index를 delete 해버림 (예외 처리)
	if (idx == 0) {
		delete_first(list);
		return;
	}

	Node *current = list->head;
	int current_idx = 0;

	// idx-1번째 노드까지 이동, 도중에 NULL이면 범위 초과
	// idx-1번째 노드가 마지막 노드인 경우 범위 초과
	while (current != NULL && current_idx < idx - 1) {
		current = current->link;
		current_idx++;
	}
	if (current == NULL || current->link == NULL) {
		printf("error : Invalid index\n");
		return;
	}

	Node *deleted = current->link;
	current->link = deleted->link;
	
	free(deleted);
	
}

void clear(List *list) {
	Node *current = list->head;
	while (current != NULL) {
		Node *next = current->link;
		free(current);
		current = next;
	}
	
	list->head = NULL;
}

void display(List *list) {
	if (list->head == NULL) {
		printf("List is empty\n");
		return;
	}
	for (Node *current = list->head; current != NULL; current = current->link) {
		printf("%d", current->data);
		if (current->link != NULL) {
			printf(" -> ");
		}
	}
	printf("\n");
}
