# Heap

- priority queue : ADT
	- 들어온 순서에 상관없이 **우선순위가 가장 높은 데이터**가 가장 먼저 나가는 자료형
	- 일반적인 queue와 유사하지만 FIFO(먼저 들어온 데이터가 우선순위가 높은 형태)와 달리 각 원소마다 고유한 우선순위를 가진다.
- heap
	- 가장 일반적인 priority queue의 구현 방법은 heap이다.
		- Complete Binary Tree 기반의 자료구조이다.
	- push : 새로운 원소를 트리의 가장 마지막 node에 삽입 후 부모 노드와 비교하며 올린다
	- pop : root node를 꺼낸 뒤 해당 자리에 마지막 node를 삽입, 자식 node와 비교하며 내린다.
	- 시간복잡도
		- 선형 자료구조로 priority queue를 구현하려 한다면 Push혹은 Pop 에서 $O(N)$의 시간복잡도를 가진다.
		- heap은 삽입, 삭제에서 $O(\log N)$ 의 시간복잡도를 가진다. (peek : $O(1)$)
			- tree의 level을 $h$ 라 하면 최대 노드의 개수는 $n = 2^h - 1$, $h \approx \log_{2}{n}$
			- 삽입, 삭제에서 트리의 깊이와 비례하는 수의 연산이 일어난다.

---

## 구현

- heap은 Complete Binary Tree 기반의 자료구조이기에 배열을 사용하기로 했다.
	- linked 형태는 포인터 오버헤드 필요 (rlink, llink), Node 접근이 느림
	- 스택에 선언하기엔 스택 오버플로 위험
		- 동적 배열로 결정

- 1-based index
	- 부모 node  : idx / 2
	- 왼쪽 자식 node : idx * 2
	- 오른쪽 자식 node : idx * 2 + 1

