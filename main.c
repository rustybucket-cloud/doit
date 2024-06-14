#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./todos.h"
#include "./actions.h"

void argument_guard(int argc, char *argv[]);
enum ACTIONS get_action(char *argv[]);

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
		case EDIT:
			printf("argv[3]: %s\n", argv[3]);
			edit_todo(argv[2], argv[3]);
		default:
			printf("Invalid action.\n");
			exit(EXIT_FAILURE);
	}
	
	return EXIT_SUCCESS;
}

void argument_guard(int argc, char *argv[]) {
	if (argc == 1) {
		printf("One argument is required.\n");
		exit(1);
	}
	
	// check if flag is valid
	int FLAG_COUNTS = 4;
	char* valid_flags[] = {"-c", "-l", "-d", "-e"};
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
	if (strcmp(argv[1], "-e") == 0) {
		return EDIT;
	}
	return INVALID;
}

