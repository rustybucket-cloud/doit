#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

enum ACTIONS {
	CREATE,
	LIST,
	INVALID // this shouldn't happen if argument_guard and get_action are working
};

void argument_guard(int argc, char *argv[]);
void add_todo(char* input);
void list_todos();
enum ACTIONS get_action(char *argv[]);
FILE* get_readable_file();
FILE* get_appendable_file();

int main(int argc, char *argv[]) {
	argument_guard(argc, argv);

	enum ACTIONS action = get_action(argv);

	switch(action) {
		case CREATE:
			add_todo(argv[2]);
			break;
		case LIST:
			list_todos();
			break;
		default:
			printf("Invalid action.\n");
			exit(1);
	}
	
	return 0;
}

void argument_guard(int argc, char *argv[]) {
	if (argc == 1) {
		printf("One argument is required.\n");
		exit(1);
	}
	
	// check if flag is valid
	int FLAG_COUNTS = 2;
	char* valid_flags[] = {"-c", "-l"};
	bool is_valid_flag = false;
	for (int i = 0; i < FLAG_COUNTS; i++) {
		if (strcmp(argv[1], valid_flags[i]) == 0) {
			is_valid_flag = true;
		}
	}
	if (is_valid_flag == false) {
		printf("Flag argument is not valid.\nThe following flags are valid: ");
		// list valid flags
		for (int i = 0; i < FLAG_COUNTS; i++) {
			printf("%s", valid_flags[i]);
			if (i != FLAG_COUNTS - 1) {
				printf(", ");
			} else {
				printf(".\n");
			}
		}
		exit(1);
	}
}

enum ACTIONS get_action(char *argv[]) {
	if (strcmp(argv[1], "-c") == 0) {
		return CREATE;
	}
	if (strcmp(argv[1], "-l") == 0) {
		return LIST;
	}
	return INVALID;
}

int create_todo_id();
void add_todo(char* input) {
	if (input == NULL) {
		printf("Todo to create not provided.\n");
		exit(1);
	}

	FILE *fptr = get_appendable_file();
	
	int todo_id = create_todo_id();
	fprintf(fptr, "%d: %s\n", todo_id, input);
	printf("Todo created: %s\n", input);
	fclose(fptr);
}

int create_todo_id() {
	FILE *fptr = get_readable_file();
	int id = 0;
	char buffer[100];
	while(fgets(buffer, 100, fptr)) {
		id++;
	}

	fclose(fptr);

	return id;
}

void list_todos() {
	FILE *fptr = get_readable_file();
	char todo[100];
	while(fgets(todo, 100, fptr)) {
		printf("%s", todo);
	}
	fclose(fptr);
}

FILE* get_file_ptr(char* mode);
FILE* get_readable_file() {
	return get_file_ptr("r");
}

FILE* get_appendable_file() {
	return get_file_ptr("a");
}

FILE* get_file_ptr(char* mode) {
	FILE *fptr;
	fptr = fopen("./todos.txt", mode);
	if (fptr == NULL) {
		printf("There was a problem reading the file.\n");
		exit(1);
	}
	return fptr;
} 
