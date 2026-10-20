#include <stdio.h>
#include <stdlib.h>

// MAX heap
// 1-based index

typedef int Element;

typedef struct Heap {
	Element* arr;
	int capacity;
	int size; // 마지막 원소의 index와 동일
} Heap;

static void _swap(Element* a, Element* b) {
	Element temp = *a;
	*a = *b;
	*b = temp;
}

Heap* heap_create(int max) {
	if (max <= 0) {
		return NULL;
	}

	Heap* heap = (Heap*)malloc(sizeof(Heap));
	if (!heap) {
		return NULL;
	}

	heap->arr = (Element*)malloc(sizeof(Element) * (max + 1));
	if (!heap->arr) {
		free(heap);
		return NULL;
	}

	heap->capacity = max;
	heap->size = 0;

	return heap;
}

int heap_push(Heap* heap, Element value) {
	if (heap->size == heap->capacity) {	
		return 0;
	}
	
	Element* target_arr = heap->arr;
	target_arr[++(heap->size)] = value;
	
	int idx = heap->size;
	while (idx > 1) {
		int parent = idx / 2;
		if (target_arr[idx] > target_arr[parent]) {
	 		_swap(&target_arr[idx], &target_arr[parent]);		
			idx = parent;
		}
		else {
			break;
		}
	}

	return 1;
}

int heap_pop(Heap* heap, Element* out) {
	if (heap->size == 0) {
		return 0;
	}

	*out = heap->arr[1];
	heap->arr[1] = heap->arr[(heap->size)--];

	int idx = 1;
	while ((idx * 2) <= heap->size) {
		int larger_child = idx * 2;
		if (larger_child + 1 <= heap->size && heap->arr[larger_child + 1] > heap->arr[larger_child]) {
			larger_child++;
		}
		
		if (heap->arr[larger_child] <= heap->arr[idx]) {
			break;
		}

		_swap(&heap->arr[larger_child], &heap->arr[idx]);
		idx = larger_child;
	}

	return 1;
}

int heap_peek(const Heap* heap, Element* out) {
	if (heap->size == 0) {
		return 0;
	}
	
	*out = heap->arr[1];
	return 1;
}

void heap_destroy(Heap* heap) {
	if (heap == NULL) {
		return;
	}
	
	free(heap->arr);
	free(heap);
}





int main() {

	// 테스트 코드	
	Heap* max_heap = heap_create(10);

	printf("--- push test ---\n");
	int values[] = { 10, 4, 20, 1, 5, 15, 30, 25, 20, 10, 13 };

	for (int i = 0; i < 11; i++) {
		if (heap_push(max_heap, values[i])) {
			printf("pushed: %d\n", values[i]);
		}
		else {
			printf("failed to push: %d\n", values[i]);
		}
	}

	printf("--- peek test ---\n");
	Element top_val;
	if (heap_peek(max_heap, &top_val)) {
		printf("\npeek: %d (Expected: 30)\n", top_val);
	}

	printf("\n--- pop test ---\n");
	Element popped;
	while (heap_pop(max_heap, &popped)) {
		printf("Popped: %d\n", popped);
	}

	heap_destroy(max_heap);

	return 0;
}
