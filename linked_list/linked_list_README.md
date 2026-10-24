# Linked List

- List : ADT
	- 순서가 있는 원소들의 모음. 원소를 추가하거나 제거해도 나머지 원소들의 순서가 유지된다. 구현을 위해 선형 자료구조가 쓰인다.

- List : 자료구조
	- array
		- 동일한 자료형의 데이터를 연속된 메모리 공간에 순차적으로 저장하는 자료구조
	- singly linked list
		- link가 다음 원소만 존재한다.
	- doubly linked list
		- 앞 뒤 node로의 link가 모두 존재한다.
	- circular linked list
		- head node와 tail node가 연결돼 순환이 있는 linked list를 의미한다.

- Linked List
	- 동적 할당으로 인해 사용 도중 자유롭게 크기 변경이 가능하다는 장점이 있다.
	- 메모리 오버헤드(link)가 있어 배열에 비해 메모리 효율이 좋지 않다.
	- 데이터 접근이 느리다. (순차 탐색 필요)
	- 삽입 삭제가 $O(1)$ 로 빠르지만 맨 앞 위치와 같은 특수한 위치의 삽입 삭제가 아니라면 탐색 $O(N)$ 이 필요하다.
---

## 구현 (C)

- Linked List를 C에서 구현할 때 실제로 사용자가 List에 접근하는 방법은 Head Node Pointer를 쓰는 것이다. 
- 사용자가 `head` 노드를 직접 만지지 않도록 `List` 구조체를 통해 리스트 전체를 제어하도록 캡슐화를 하였다.

```c
// 구현
typedef struct Node {
	Element data;
	struct Node *link;
} Node;

typedef struct List {
	Node *head;
	// List 객체 추가 정보 저장
	int size;
} List;
```

---

## 문제 상황

- 최초로 singly linked list를 만들 경우 이전 node에 접근할 수 없다는 문제 때문에 삭제를 구현할때 문제가 생겼다.
	- `singly_linked_list.c` 소스 코드에선 다음과 같이 다음 다음 노드를 매번 찾아가며 애초에 이전 node에 위치하도록 설계하였다.
	- 이후 tree 구현에서 link 자체의 주소를 저장하는 방식(이중 포인터)이 더 깔끔하다는 것을 깨달았다.

```c
while (current->link->link != NULL) {
        current = current->link;
}
```
