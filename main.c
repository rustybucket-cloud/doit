#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display_todos(char todos[][100], int todo_count) {
	int i;
	for (i = 0; i < todo_count; i++) {
		printf("%d: %s\n", i + 1, todos[i]);
	}
}

void add_todo(char* input) {
	FILE *fptr;
	fptr = fopen("./todos.txt", "a");
	if (fptr == NULL) {
		printf("There was a problem reading the file.\n");
		exit(1);
	}

	fprintf(fptr, "%s\n", input);
	printf("Todo created: %s\n", input);
	fclose(fptr);
}

int main(int argc, char *argv[]) {
	int todo_count = 0;
	size_t todo_size = 5;
	char todos[todo_size][100];

	if (argc == 1) {
		printf("One argument is required\n");
		exit(1);
	}
	
	if (strcmp(argv[1], "-c") == 0) {
		if (argc > 2) {
			add_todo(argv[2]);
		} else {
			printf("A todo is required\n");
			exit(1);
		}
	} else if (strcmp(argv[1], "-l") == 0) {
		
	}

	display_todos(todos, todo_count);

	return 0;
}

