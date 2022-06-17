#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_SCORE 5

struct Student {
	int age;
	char* surname;
	char* name;
	char* group;
	char* phone;
	int marks[MAX_SCORE];
	struct Student* next;
};
typedef struct Student student;

struct LinkedList {
	student* head;
	student* tail;
	size_t size;
};
typedef struct LinkedList linkedlist;

linkedlist* createlist() {
	linkedlist* tmp = (linkedlist*)malloc(sizeof(linkedlist));
	if (tmp) {
		tmp->size = 0;
		tmp->head = 0;
		tmp->tail = 0;
	}
	else printf_s("error : can't allocate memory in linkedlist");
	return tmp;
}

student* newStudent(int age, char* name, char* surname, char* group, char* phone, int score[MAX_SCORE]) {
	student* new_student = (student*)malloc(sizeof(student));
	if (new_student) {
		new_student->age = age;

		size_t length;
		if (name != NULL) {
			length = strlen(name) + 1;
			new_student->name = (char*)malloc(sizeof(char) * length);
			strcpy_s(new_student->name, length, name);
		}
		else new_student->name = NULL;

		if (surname != NULL) {
			length = strlen(surname) + 1;
			new_student->surname = (char*)malloc(sizeof(char) * length);
			strcpy_s(new_student->surname, length, surname);
		}
		else new_student->surname = NULL;

		if (group != NULL) {
			length = strlen(group) + 1;
			new_student->group = (char*)malloc(sizeof(char) * length);
			strcpy_s(new_student->group, length, group);
		}
		else new_student->group = NULL;

		if (phone != NULL) {
			length = strlen(phone) + 1;
			new_student->phone = (char*)malloc(sizeof(char) * length);
			strcpy_s(new_student->phone, length, phone);
		}
		else new_student->phone = NULL;

		if (score != NULL) {
			for (int i = 0; i < MAX_SCORE; i++) {
				new_student->marks[i] = score[i];
			}
		}
		else {

			for (int i = 0; i < MAX_SCORE; i++) {
				new_student->marks[i] = 0;
			}
		}
	}
	return new_student;
}

void pushBack(linkedlist* l, student* s) {
	if (l->tail != 0) l->tail->next = s;
	l->tail = s;
	if (l->head == 0) l->head = s;
	l->size++;
	l->tail->next = 0;
}

void printStudent(student* s) {
	printf_s("%d ", s->age);
	printf_s("%s ", s->surname);
	printf_s("%s ", s->name);
	printf_s("%s ", s->group);
	printf_s("%s ", s->phone);
	for (int i = 0; i < MAX_SCORE; i++) {
		printf_s("%d ", s->marks[i]);
	}
}

void print_list(linkedlist* l) {
	printf_s("linkedList : \n");
	student* current = l->head;
	while (current != 0) {
		printStudent(current);
		current = current->next;
	}
	printf_s("\n");
}

void saveListToTxtFile(linkedlist* l, char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "w") != 0) {
		printf_s("error on opening file \"%s\"\n", filename);
		return;
	}
	fprintf(file, "%llu\n", l->size);
	student* current = l->head;
	while (current != 0) {
		fprintf(file,
			"%d\n%s\n%s\n%s\n%s\n",
			current->age, current->name, current->surname, current->group, current->phone);
		for (int i = 0; i < MAX_SCORE; ++i) {
			fprintf(file, "%d ", current->marks[i]);
		}
		fprintf(file, "\n");

		current = current->next;
	}
	fclose(file);
}

#define STR_BUF_SIZE 256
linkedlist* loadListFromTxtFile(char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "r") != 0) {
		printf_s("error on opening file \"%s\"\n", filename);
		return NULL;
	}
	linkedlist* list = createlist();
	fscanf_s(file, "%llu\n", &list->size);
	for (size_t i = list->size; i > 0; --i) {
		int age = 0, score[MAX_SCORE];
		char name[STR_BUF_SIZE], surname[STR_BUF_SIZE], group[STR_BUF_SIZE], tel_number[STR_BUF_SIZE];
		fscanf_s(file, "%d\n", &age);

		fgets(name, STR_BUF_SIZE, file);
		name[strlen(name) - 1] = '\0';
		fgets(surname, STR_BUF_SIZE, file);
		surname[strlen(surname) - 1] = '\0';
		fgets(group, STR_BUF_SIZE, file);
		group[strlen(group) - 1] = '\0';
		fgets(tel_number, STR_BUF_SIZE, file);
		tel_number[strlen(tel_number) - 1] = '\0';
		for (int i = 0; i < MAX_SCORE; ++i) {
			fscanf_s(file, "%d", &score[i]);
		}
		pushBack(list, newStudent(age, name, surname, group, tel_number, score));
	}
	fclose(file);
	return list;
}

void saveListToBinFile(linkedlist* l, char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "wb") != 0) {
		printf_s("error on opening file \"%s\"\n", filename);
		return;
	}
	fwrite(&l->size, sizeof(l->size), 1, file);
	student* current = l->head;
	while (current != 0) {
		size_t lengths[] = { strlen(current->name), strlen(current->surname), strlen(current->group), strlen(current->phone) };
		fwrite(lengths, sizeof(*lengths), 4, file);
		fwrite(&current->age, sizeof(current->age), 1, file);
		fwrite(current->marks, sizeof(*current->marks), MAX_SCORE, file);
		fwrite(current->name, sizeof(*current->name), lengths[0], file);
		fwrite(current->surname, sizeof(*current->surname), lengths[1], file);
		fwrite(current->group, sizeof(*current->group), lengths[2], file);
		fwrite(current->phone, sizeof(*current->phone), lengths[3], file);

		current = current->next;
	}
	fclose(file);
}

linkedlist* loadListFromBinFile(char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "rb") != 0) {
		printf_s("error file \"%s\"\n", filename);
		return NULL;
	}

	linkedlist* list = createlist();
	fread(&list->size, sizeof(list->size), 1, file);
	for (size_t i = list->size; i > 0; --i) {
		student* current = newStudent(0, NULL, NULL, NULL, NULL, NULL);
		size_t lengths[4];
		fread(lengths, sizeof(*lengths), 4, file);
		current->name = (char*)calloc(lengths[0] + 1, sizeof(char));
		current->surname = (char*)calloc(lengths[1] + 1, sizeof(char));
		current->group = (char*)calloc(lengths[2] + 1, sizeof(char));
		current->phone = (char*)calloc(lengths[3] + 1, sizeof(char));

		fread(&current->age, sizeof(current->age), 1, file);
		fread(current->marks, sizeof(*current->marks), MAX_SCORE, file);
		fread(current->name, sizeof(*current->name), lengths[0], file);
		fread(current->surname, sizeof(*current->surname), lengths[1], file);
		fread(current->group, sizeof(*current->group), lengths[2], file);
		fread(current->phone, sizeof(*current->phone), lengths[3], file);

		pushBack(list, current);
	}
	fclose(file);
	return list;
}
void excellent(linkedlist* l) {
	student* current = l->head;
	while (current != 0) {
		int summ = 0;
		for (int i = 0; i < MAX_SCORE; i++) {
			summ += current->marks[i];
		}
		if (summ / MAX_SCORE >= 4) {
			printStudent(current);
		}
		current = current->next;
	}
}

void surname(linkedlist* l) {
	student* current = l->head;
	while (current != 0) {
		if (current->surname[0] == 'È' && current->surname[1] == 'â') {
			printStudent(current);
		}
		current = current->next;
	}
}

void telephone(linkedlist* l) {
	student* current = l->head;
	while (current != 0) {
		if (current->phone[strlen(current->phone) - 2] == '9' && current->phone[strlen(current->phone) - 1] == '9') {
			printStudent(current);
		}
		current = current->next;
	}
}

void delete_bad_students(linkedlist* l) {
	student* current = l->head;
	student* tmp;
	while (current != 0) {
		int summ = 0;
		tmp = current->next;
		for (int i = 0; i < MAX_SCORE; i++) {
			summ += current->marks[i];
		}
		if (summ / MAX_SCORE < 4) {
			free(current);
			current = tmp;
		}
	}
}


int main(int argc, char** argv) {
	setlocale(LC_ALL, "Rus");
	linkedlist* l = createlist();
	student* stud = newStudent(18, "IkarI", "Sindzy", "Evangelion", "Eva02", (int[MAX_SCORE]) { 2, 2, 2, 2, 2 });
	pushBack(l, stud);

	student* stud2 = newStudent(18, "Ayanami", "Ray", "Evangelion", "Eva01", (int[MAX_SCORE]) { 5, 5, 5, 5, 5 });
	pushBack(l, stud2);
	print_list(l);

	saveListToTxtFile(l, "list.txt");
	student* lFromTxt = loadListFromTxtFile("list.txt");
	print_list(lFromTxt);

	saveListToBinFile(l, "list.bin");
	student* lFromBin = loadListFromBinFile("list.bin");
	print_list(lFromBin);
	return 0;
}