#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./files.h"

int create_todo_id(void);

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

int create_todo_id(void) {
	FILE *fptr = get_readable_file();
	int id = 0;
	char buffer[100];
	while(fgets(buffer, 100, fptr)) {
		id++;
	}

	fclose(fptr);

	return id;
}

void list_todos(void) {
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

void edit_todo(char* id, char* new_text) {
	if (id == NULL || new_text == NULL) {
		puts("Edit requires an id and updated text");
		exit(EXIT_FAILURE);
	}
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
			printf("size: %zu\n", strlen(id_str));
			id_str[strlen(id_str)] = buffer[i];
			i++;
		}
		if (strcmp(id_str, id) != 0) {
			strcat(content, buffer);
		} else {
			strcat(content, new_text);
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
