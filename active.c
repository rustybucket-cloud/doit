#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./todos.h"

#define BUFFER_SIZE 100

typedef enum ACTIVE_ACTIONS {
	CREATE,
	EDIT,
	DELETE,
	EXIT,
	INVALID
} ACTIVE_ACTIONS;

ACTIVE_ACTIONS get_active_action(void);
void create_todo_from_input(void);
void prompt(char* prompt, char* buffer);
void trim(char* buffer);
void edit_todo_from_input(void);
void delete_todo_from_input(void);

void start_active_mode(void) {
	bool should_continue = true;
	while(should_continue) {
		puts("Current todos:");
		list_todos();

		puts("");
		puts("c - create");
		puts("e - edit");
		puts("d - delete");
		puts("");

		ACTIVE_ACTIONS active_action = get_active_action();

		switch(active_action) {
			case CREATE:
				create_todo_from_input();
				break;
			case EDIT:
				edit_todo_from_input();
				break;
			case DELETE:
				delete_todo_from_input();
				break;
			case EXIT:
				should_continue = false;
				break;
			default:
				puts("Invalid action");
		}
		puts("");
	}
}

ACTIVE_ACTIONS get_active_action(void) {
	char action_text[BUFFER_SIZE];
	memset(action_text, 0, BUFFER_SIZE);
	prompt("What would you like to do?", action_text);
	trim(action_text);
	if (strcmp(action_text, "c") == 0) {
		return CREATE;
	} else if (strcmp(action_text, "e") == 0) {
		return EDIT;
	} else if (strcmp(action_text, "d") == 0) {
		return DELETE;
	} else if (strcmp(action_text, "exit") == 0) {
		return EXIT;
	} else {
		return INVALID;
	}
}

void create_todo_from_input(void) {
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	prompt("Enter the todo you would like to create", buffer);
	add_todo(buffer);
}

void edit_todo_from_input(void) {
	char id[BUFFER_SIZE];
	memset(id, 0, BUFFER_SIZE);
	prompt("Enter the todo id you would like to change", id);
	trim(id);

	char text[BUFFER_SIZE];
	memset(text, 0, BUFFER_SIZE);
	prompt("Enter the update text", text);
	edit_todo(id, text);
}

void delete_todo_from_input(void) {
	char id[BUFFER_SIZE];
	memset(id, 0, BUFFER_SIZE);
	prompt("Enter the todo id you would like to change", id);
	trim(id);

	delete_todo(id);
}

void prompt(char* prompt, char* buffer) {
	printf("%s\n", prompt);
	if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
		puts("There was a problem getting input.");
		exit(1);
	}
}

void trim(char* buffer) {
	char temp[BUFFER_SIZE];
	memset(temp, 0, BUFFER_SIZE);
	for (int i = 0; i < strlen(buffer); i++) {
		if (
			buffer[i] != '\n' &&
			buffer[i] != ' ' &&
			buffer[i] != '\t'
		) {
			temp[strlen(temp)] = buffer[i];
		}
	}
	strcpy(buffer, temp);
}
