#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

// typedef : 기존 자료형에 새로운 이름을 붙이는 것
/*
ex)
typedef int Integer
Integer num = 1;
*/

// 구조체 타입 정의 자체에는 기본값 초기화 불가.

typedef struct StackType {
	int data[SIZE];
	int top_idx;
	// int top_idx = -1 #error
} StackType;

/*
- (*s).member 와 s->member 는 정확히 같게 동작함
- -> 는 가독성을 높이기 위한 문법적 편의
*/

void init(StackType *s) {
	s->top_idx = -1;
}

int is_empty(StackType *s) {
	if (s->top_idx == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

int is_full(StackType *s) {
	if (s->top_idx == SIZE - 1) {
		return 1;
	}
	else {
		return 0;
	}
}

void push(StackType *s, int value) {
	if (is_full(s)) {
		printf("error : Stack is full\n");
		// return;
		exit(1);
	}
	else {
		s->data[++(s->top_idx)] = value; // Operator Precedence 주의
	}
}

/*
int pop(StackType *s) {
	if (is_empty(s)) {
		printf("error : Stack is empty\n");
		// return ??
	}
	else {
		return s->data[(s->top_idx)--];
	}
}
*/

/*
- empty 처리
	- pop과 top에서 stack이 비어있는 상황에 데이터에서는 쓰이지 않는 return 값을 정하기 어려움.
	- data[-1] : UB / 버퍼 언더플로 등의 문제도 생길 수 있음.
	- 강제종료 하는 방향으로 결정

- std::stack(C++) 의 처리 방식
	- 출력과 삭제를 동시에 하길 기대했는데 오류가 발생하면 출력값 자체가 날아가는 상황 발생
	- 위와 같은 상황을 방지하기 위해 안전한 조회 top() 과 위험한 삭제 pop() 을 완전히 분리시켜 둠 + 함수가 두 가지 일을 하다가 중간에 에러가 나면 데이터가 유실됨을 방지
*/

void pop(StackType *s) {
	if (is_empty(s)) {
		printf("error : Stack is empty\n");
		exit(1);
	}
	else {
		(s->top_idx)--;
	}
}

int top(StackType *s) {
	if (is_empty(s)) {
		printf("error : Stack is empty\n");
		exit(1);
	}
	else {
		return s->data[(s->top_idx)];
	}
}

int main() {
	
	int user_input = 0;
	StackType stk;

	while(1) {
		printf("0 : init\n1 : push\n2 : pop\n3 : top\n4 : quit\nenter : ");
		scanf("%d", &user_input);
		
		if (user_input == 0) {
			init(&stk);
		}

		else if (user_input == 1) {
			int push_value;
			printf("push : ");
			scanf("%d", &push_value);
			push(&stk, push_value);
		}

		else if (user_input == 2) {
			pop(&stk);
		}

		else if (user_input == 3) {
			printf("%d\n", top(&stk));
		}

		else if (user_input == 4) {
			break;
		}

		else {
			printf("Invalid Input\n");
		}
	}

	return 0;
}
