#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./main.h"

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
		case DELETE:
			delete_todo(argv[2]);
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
	int FLAG_COUNTS = 3;
	char* valid_flags[] = {"-c", "-l", "-d"};
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
	if (strcmp(argv[1], "-d") == 0) {
		return DELETE;
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

void delete_todo(char* id) {
	// get all todos except the todo with the matching id
	FILE *fptr = get_readable_file();
	char* content;
	size_t content_size = 500;
	content = (char*)calloc(content_size, sizeof(char));
	char buffer[100];
	while(fgets(buffer, 100, fptr)) {
		char id_str[100];
		memset(id_str, 0, sizeof(id_str));
		bool should_continue = true;
		int i = 0;
		while(should_continue) {
			if (buffer[i] == ':') {
				should_continue = false;
				continue;
			}
			id_str[strlen(id_str)] = buffer[i];
			i++;
		}
		if (strcmp(id_str, id) != 0) {
			strcat(content, buffer);
		}
		memset(id_str, 0, sizeof(id_str));
	}
	fclose(fptr);

	// overwrite the file
	FILE* writable_file = get_writable_file();
	fprintf(writable_file, content);

	free(content);
	fclose(writable_file);
}

FILE* get_readable_file() {
	return get_file_ptr("./todos.txt", "r");
}

FILE* get_writable_file() {
	return get_file_ptr("./todos.txt", "w");
}

FILE* get_appendable_file() {
	return get_file_ptr("./todos.txt", "a");
}

FILE* get_temp_file() {
	return get_file_ptr("./todos.tmp", "w");
}

FILE* get_file_ptr(char* file_name, char* mode) {
	FILE *fptr;
	fptr = fopen(file_name, mode);
	if (fptr == NULL) {
		printf("There was a problem reading the file.\n");
		exit(1);
	}
	return fptr;
} 
