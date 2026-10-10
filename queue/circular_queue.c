#include <stdio.h>
#define MAX_QUEUE_SIZE 5
// 실제 사용 가능한 queue 공간 : MAX_QUEUE_SIZE - 1

// empty, full 상태를 구분하는 과정에서 array 공간 1칸을 쓰지 못하게 됨.

// empty : front(추출 위치) == rear(삽입 위치)
// full : front(추출 위치) == (rear(삽입 위치) + 1) % MAX_QUEUE_SIZE
// 마지막 칸까지 채우고 rear가 front 위치까지 들어오면 empty와 구분되지 않는다.

// circular queue
// 순환 : modulus 사용

// empty 상태에서 front 함수 처리를 위해 front_result 변수 추가
typedef struct QueueType {
	int data[MAX_QUEUE_SIZE];
	int front_idx;
	int rear_idx;
	int front_result;
} QueueType;

void init(QueueType *q) {
	q->front_idx = q->rear_idx = q->front_result = 0;
}

int isEmpty(QueueType *q) {
	// 삽입 위치와 추출 위치가 같으면 empty
	return q->front_idx == q->rear_idx;
}

int isFull(QueueType *q) {
	// (삽입 위치 + 1) % MAX_QUEUE_SIZE 와 추출 위치가 같으면 full
	return q->front_idx == (q->rear_idx + 1) % MAX_QUEUE_SIZE;
}

void enqueue(QueueType *q, int value) {
	if (isFull(q)) {
		printf("warning : Queue is full\n");
		return;
	}
	q->data[q->rear_idx] = value;
	q->rear_idx = (q->rear_idx + 1) % MAX_QUEUE_SIZE;
}

void dequeue(QueueType *q) {
	if (isEmpty(q)) {
		printf("warning : Queue is empty\n");
		return;
	}
	q->front_idx = (q->front_idx + 1) % MAX_QUEUE_SIZE;
}

// empty queue에서 front 조회 시 이전 값이 출력된다
void front(QueueType *q) {
	if (isEmpty(q)) {
		printf("warning : Queue is empty\n");
		return;
	}
	q->front_result = q->data[q->front_idx];
}


int main() {
	QueueType que;
	init(&que);
	
	int userInput = 0;
	int value = 0;

	while (1) {
		
		printf("1 : init\n");	
		printf("2 : enqueue\n");	
		printf("3 : dequeue\n");
		printf("4 : front\n");
		printf("5 : exit\n");	

		printf("enter : ");
		scanf("%d", &userInput);

		if (userInput == 1) {
			init(&que);
		}
		else if (userInput == 2) {
			printf("enqueue : ");
			scanf("%d", &value);
			enqueue(&que, value);
		}
		else if (userInput == 3) {
			dequeue(&que);
		}
		else if (userInput == 4) {
			front(&que);
			printf("front : %d\n", que.front_result);
		}
		else if (userInput == 5) {
			break;
		}
		else {
			printf("invalid input\n");
		}

		// while문 안에 switch-case문을 사용한다면 while문의 break 사용 불가
		// break 대신 while 조건을 바꾸면 해결 가능
		/*
		switch(userInput) {
			case 1:
				init(&que);
				break;
			case 2:
				printf("enqueue : ");
				scanf("%d", &value);
				enqueue(&que, value);
				break;
			case 3:
				dequeue(&que);
				break;
			case 4:
				front(&que);
				printf("front : %d\n", que.front_result);
				break;
			case 5:
				break; // while문 탈출을 위한 break 사용 불가
			default:
				printf("invalid input\n");
		}
		*/
	}
}

// front_idx, rear_idx 대신 front(출력 횟수), rear(입력 횟수) 사용 가능
// rear(입력 횟수) - front(출력 횟수) : queue 원소의 개수
// 내 코드와 달리 실제 인덱스의 순환을 직접 변수에 반영하지는 않는 방식
// 이 방식으로는 array 전체에 data를 넣을 수 있다는 장점 + front, rear 오버플로 발생 가능 단점

// 코드 핵심 통찰 : modulus 를 통해 연속으로 늘어나는 정수의 순환 표현 가능
