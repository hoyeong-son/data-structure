#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 5

// queue : rear 삽입 / front 추출
// front_idx : 추출 위치
// rear_idx : 삽입 위치

// linear queue 활용 시 문제점 : rear_idx가 SIZE가 되면 더 이상 사용 불가
// 해결책 : rear index가 SIZE 도달 시 전체 데이터를 0번 index로 shift

typedef struct QueueType {
	int data[SIZE];
	int front_idx;
	int rear_idx;
} QueueType;

void init(QueueType *q) {
	q->front_idx = 0;
	q->rear_idx = 0;
}

bool isEmpty(QueueType *q) {
	return q->front_idx == q->rear_idx;
}

bool isFull(QueueType *q) {
	return q->rear_idx == SIZE && q->front_idx == 0;
}

void enqueue(QueueType *q, int value) {
	if (isFull(q)) {
		printf("error : Queue is full\n");
		exit(1);
	}
	// rear index size 도달 시 shift
	else if (q->rear_idx == SIZE) {
		int size = q->rear_idx - q->front_idx;
		for (int i = 0; i < size; i++) {
			q->data[i] = q->data[i+q->front_idx];
		}
		q->rear_idx = size;
		q->front_idx = 0;
	}
	q->data[(q->rear_idx)++] = value;
}

void dequeue(QueueType *q) {
	if (isEmpty(q)) {
		printf("error : Queue is empty\n");
		exit(1);
	}
	else {
		q->front_idx++;
	}
}

int front(QueueType *q) {
	if (isEmpty(q)) {
		printf("error : Queue is empty\n");
		exit(1);
	}
	else {
		return q->data[q->front_idx];
	}
}

int main() {

	QueueType que;
	init(&que);

	return 0;

}
