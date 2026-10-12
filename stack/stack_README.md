# Stack

## 정의

- stack : ADT(Abstract Data Type)
	- **LIFO** 구조를 가지며 기본 연산 push, pop을 가지는 자료 형태
- stack : Data Structure
	- **선형 자료구조**
	- stack ADT는 array, linked list 등으로 자료 구조 구현 가능

---

## 보조 설명

- 선형 자료구조 : 데이터가 일렬로 연속되거나 순차적으로 나열되어 요소간의 관계가 1:1인 구조

---

## 구현 (C)

- StackType 구조체
	- array
	- top_idx : 가장 최근에 들어온 데이터의 위치 인덱스
		- empty : top_idx == -1
		- full : top_idx == SIZE - 1
- init, push, pop, top 구현
	- is_empty, is_full 보조 연산 활용하여 예외 처리

---

## 문제 상황

- pop, top method 구현 시 empty 상태 반환값 처리
	- std::stack (C++)는 예외 처리를 어떻게 하는지?
		- stack이 비어있는지 확인하는 예외를 직접 처리하않음
	- 우선 exit(1) (비정상 프로그램 종료 처리)로 마무리
	- 통일성을 위해 push 함수도 동일하게 처리
