#include <stdlib.h>
#include <stdio.h>


struct Array {
	int* array;
	int size;
	int v;// מבת¸ל(גלוסעטלמסעü)
};

typedef struct Array mass;

mass* create(int capacity) {
	mass* array = (mass*)malloc(sizeof(mass));
	array->size = 0;
	array->v = capacity;
	array->array = (int*)malloc(capacity * sizeof(int));
	return array;
}

void resize_array(mass* temp, int capacity) {
	int* new_array = (int*)realloc(temp->array, capacity * sizeof(int));
	if (new_array) {
		temp->array = new_array;
		temp->v = capacity;
	}
	if (temp->size > capacity) {
		temp->size = capacity;
	}
}

void add(mass* temp, int number) {
	if (temp->size == temp->v) {
		resize_array(temp, temp->v * 2);
	}
	temp->array[temp->size] = number;
	temp->size++;
}

int at(mass* temp, int index) {
	if (index >= 0 && index < temp->size) {
		return temp->array[index];
	}
	else {
		return 0;
	}
}

void remove_el(mass* temp, int index) {
	if (index >= 0 && index < temp->size) {
		for (int i = index + 1; i < temp->v; i++) {
			temp->array[i - 1] = temp->array[i];
		}
		temp->size--;
	}
}

void removeAll(mass* temp) {
	temp->size = 0;
}

void print(mass* temp) {
	for (int i = 0; i < temp->size; ++i) printf("%d", temp->array[i]);
	printf("\n");
}

int find_range(mass* temp, int num, int begin, int end) {
	if (begin < 0 || begin > temp->size) begin = 0;
	if (end < 0 || end > temp->size) end = temp->size;

	for (int i = begin; i < end; ++i) {
		if (temp->array[i] == num) return i;
	}
	return -1;
}

void find(mass* temp, int num) {
	int check = 0;
	check= find_range(temp, num, 0, temp->size);
	if (check == 0) {
		printf("Exists\n");
	}
	else {
		printf(" Dont Exists\n");
	}
}

int counter(mass* temp, int num) {
	int ind = -1;
	int count = -1;
	do {
		ind = find_range(temp, num, ind + 1, temp->size);
		count++;
	} while (ind != -1);
	return count;
}

int compare(int* num1, int* num2) {
	return (*num1 - *num2);
}

int uniq(mass* temp) {
	int count = 0;
	for (int i = 0; i < temp->size; i++) {
		if (counter(temp, temp->array[i]) == 1) count++;
	}
	return count;
}

void sort(mass* temp) {
	qsort(temp->array, temp->size, sizeof(int), compare);
}

int main(int argc, char** argv) {
	int check = 0;
	mass* arr = create(3);
	add(arr, 9);
	add(arr, 6);
	add(arr, 9);
	print(arr);
	find(arr,9);
	check = counter(arr, 9);
	printf("%d\n", check);
	remove_el(arr,0);
	print(arr);
	int un = uniq(arr);
	printf_s("%d\n", un);
	sort(arr);
	print(arr);
	removeAll(arr);
	print(arr);
	return 0;
}