#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int comp(const void*, const void*);

int main() {
	setlocale(0, "Russian");
	int* tmp_mass = NULL;
	int* mass_count_str = NULL;
	int count = 0;
	int num_sym = 0;
	char input = '0';
	FILE* In = NULL;
	fopen_s(&In, "input.txt", "r");
	if (In == NULL) {
		perror("error");
		return 0;
	}

	while (!feof(In)) {
		input = fgetc(In);
		++num_sym;
		if (input == '\n') {
			++count;
			tmp_mass = (int*)realloc(mass_count_str, (count) * sizeof(int));
			if (tmp_mass != NULL) {
				mass_count_str = tmp_mass;
				mass_count_str[count - 1] = num_sym;
				num_sym = 0;
			}
			else {
				free(mass_count_str);
				free(tmp_mass);
				printf("ERROR of memory\n");
				return 0;
			}
		}
		else if (input == '\0') break;
	}
	char** main_mass = NULL;
	main_mass = (char**)malloc((count) * sizeof(char*));
	for (int i = 0; i < count; i++) {
		main_mass[i] = (char*)malloc(mass_count_str[i] * sizeof(char));
		for (int j = 0; j < mass_count_str[i]; j++) {
			main_mass[i][j] = 0;
		}
	}
	rewind(In);
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < mass_count_str[i]; j++) {
			main_mass[i][j] = fgetc(In);
		}
	}
	fclose(In);
	free(mass_count_str);
	qsort(main_mass, (count), sizeof(char*), comp);

	for (int i = 0; i < count; ++i) {
		for (int j = 0; main_mass[i][j] != '\n'; ++j) {
			printf("%c", main_mass[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < count; ++i) {
		free(main_mass[i]);
	}
	free(main_mass);
	return 0;
}

int comp(const void* val1, const void* val2) {
	const char** str1 = (char**)val1;
	const char** str2 = (char**)val2;
	return((strlen(*str1)) - (strlen(*str2)));
}