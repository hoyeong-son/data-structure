# Queue

## 정의

- queue : ADT
	- **FIFO**  구조를 가지며 기본 연산 enqueue, dequeue를 가지는 자료 형태
- queue : 자료 구조
	- **선형 자료구조**
	- stack ADT는 linear queue, circular queue 등으로 자료 구조 구현 가능

---

## 구현 (C)

### Linear Queue

- QueueType 구조체
	- array
	- front_idx
	- rear_idx

### Circular Queue

- Index의 순환을 modulus를 활용해 표현하면 선형 자료구조인 array를 순환되게 (원처럼) 사용이 가능

```c
// index(정수)의 순환은 modulus
idx % SIZE
```

- Queue의 full, empty 상태 처리를 idx 상대 위치로 처리함.

---

## 문제 상황

### Linear Queue

- enqueue는 rear에서, dequeue는 front에서 하는 과정에 data의 index가 뒤로 밀리며 queue의 사용량이 한정되있다는 문제 발생
	- enqueue 함수에 rear_idx가 마지막 index를 넘어가기 전, data 전체를 array의 0번 index로 shift하도록 처리 (data를 미는 과정O(n)이 주기적으로 소모)

### Circular Queue

- full, empty 상태를 front, rear index의 상대 위치로 처리하는 과정에서 full, empty 구분이 되지 않는 현상이 발생
	- rear index가 순환 한바퀴를 돌아 마지막 칸까지 채운 후에 다시 front index와 같은 위치가 됨
	- front index가 rear index보다 한칸 앞에 있는 상태를 full로 처리
		- 이 과정에서 배열의 1칸을 쓰지 못하는 손실이 생긴다

```c
front_idx == rear_idx // empty (최초 상태 : empty)
front_idx == (rear_idx + 1) % SIZE // full (empty와의 구분을 위함)
```

- index 상대 위치가 아닌 size 변수를 구조체에 추가하면 배열의 1칸을 쓰지 못하는 손실을 막을 수 있음
