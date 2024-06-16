#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./todos.h"

typedef enum ACTIONS {
	CREATE,
	LIST,
	DELETE,
	EDIT,
	HELP,
	INVALID // this shouldn't happen if get_action is working
} ACTIONS;

ACTIONS get_action(char *argv[], int argc);
bool is_selected(char* arg, char* short_arg, char* verbose_arg);
void list_help_options(void);

int main(int argc, char *argv[]) {
	ACTIONS action = get_action(argv, argc);

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
			edit_todo(argv[2], argv[3]);
			break;
		case HELP:
			list_help_options();
			break;
		default:
			printf("Invalid action.\n");
			exit(EXIT_FAILURE);
	}
	
	return EXIT_SUCCESS;
}

ACTIONS get_action(char *argv[], int argc) {
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
	}
	puts("Invalid action. Enter \"help\" for available actions.");
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
