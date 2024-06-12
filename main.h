#include <stdio.h>
#include "./actions.h"


void argument_guard(int argc, char *argv[]);
void add_todo(char* input);
void list_todos();
void delete_todo(char* id);
enum ACTIONS get_action(char *argv[]);
FILE* get_readable_file();
FILE* get_writable_file();
FILE* get_appendable_file();
FILE* get_file_ptr(char* file_name, char* mode);
FILE* get_temp_file();
