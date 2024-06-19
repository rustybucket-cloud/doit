#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./todos.h"
#include "./active.h"

typedef enum ACTIONS {
	CREATE,
	LIST,
	DELETE,
	EDIT,
	HELP,
	ACTIVE,
	SEARCH,
	INVALID // this shouldn't happen if get_action is working
} ACTIONS;

ACTIONS get_action(char *argv[], int argc);
bool is_selected(char* arg, char* short_arg, char* verbose_arg);
void list_help_options(void);

int main(int argc, char *argv[]) {
	ACTIONS action = get_action(argv, argc);
	char input[100];
	switch(action) {
		case CREATE:
			if (argc >= 3) {
				strcpy(input, argv[2]);
				strncat(input, "\n", 2);
			}
			add_todo(input);
			break;
		case LIST:
			list_todos();
			break;
		case DELETE:
			delete_todo(argv[2]);
			break;
		case EDIT:
			if (argc >= 3) {
				strcpy(input, argv[3]);
				strncat(input, "\n", 2);
			}
			edit_todo(argv[2], input);
			break;
		case HELP:
			list_help_options();
			break;
		case ACTIVE:
			start_active_mode();
			break;
		case SEARCH:
			search_todos(argv[2]);
			break;
		default:
			exit(EXIT_FAILURE);
	}
	
	return EXIT_SUCCESS;
}

ACTIONS get_action(char *argv[], int argc) {
	if (argc == 1) {
		return ACTIVE;
	}
	if (argc >= 2) {
		if (is_selected(argv[1], "-c", "--create")) {
			return CREATE;
		}
		if (is_selected(argv[1], "-l", "--list")) {
			return LIST;
		}
		if (is_selected(argv[1], "-d", "--delete")) {
			return DELETE;
		}
		if (is_selected(argv[1], "-e", "--edit")) {
			return EDIT;
		}
		if (is_selected(argv[1], "-h", "--help")) {
			return HELP;
		}
		if (is_selected(argv[1], "-s", "--search")) {
			return SEARCH;
		}
	}
	puts("Invalid action. Enter \"--help\" for available actions.");
	exit(1);
}

bool is_selected(char* arg, char* short_arg, char* verbose_arg) {
	return strcmp(short_arg, arg) == 0 || strcmp(verbose_arg, arg) == 0;
}

void list_help_options(void) {
	puts("The following actions are available:");
	puts("Action\t\tCommand\t\t\tDescription\t\tExample");
	puts("------------------------------------------------------------------------------------");
	puts("Create\t\t\"-c\" or \"--create\"\tCreates a new todo\tdoit -c \"walk the dog\"");
	puts("List\t\t\"-l\" or \"--list\"\tList all created todos\tdoit -l");
	puts("Delete\t\t\"-d\" or \"--delete\"\tDelete a todo by id\tdoit -d 1");
	puts("Edit\t\t\"-e\" or \"--edit\"\tEdit a todo\t\tdoit -e 1 \"Walk the cat\"");
}
