#ifndef TODOS_H
#define TODOS_H

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
	if (id == NULL) {
		puts("Edit requires an id and updated text");
		exit(EXIT_FAILURE);
	}
	// get all todos except the todo with the matching id
	FILE *fptr = get_readable_file();
	FILE *tmp = get_temp_file();
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
			fputs(buffer, tmp);
		}
	}
	fclose(fptr);
	fclose(tmp);

	remove("todos.txt");
	rename("todos.tmp", "todos.txt");
}

void edit_todo(char* id, char* new_text) {
	if (id == NULL || new_text == NULL) {
		puts("Edit requires an id and updated text");
		exit(EXIT_FAILURE);
	}
	// get all todos except the todo with the matching id
	FILE *fptr = get_readable_file();
	FILE *tmp = get_temp_file();
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
			fputs(buffer, tmp);
		} else {
			char content[500];
			memset(content, 0, 500);
			strcat(content, id);
			strcat(content, ": ");
			strcat(content, new_text);
			strcat(content, "\n");
			printf("%s", content);
			fputs(content, tmp);
		}
	}
	fclose(fptr);
	fclose(tmp);

	remove("todos.txt");
	rename("todos.tmp", "todos.txt");
} 

void search_todos(char* search) {
	if (search == NULL) {
		puts("Search query is required.");
		return;
	}
	FILE* fptr = get_readable_file();
	char buffer[100];
	while(fgets(buffer, 100, fptr)) {
		if (strstr(buffer, search) != NULL) {
			printf("%s", buffer);
		}
	}
}
#endif
