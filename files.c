#include <stdio.h>
#include <stdlib.h>

FILE* get_file_ptr(char* file_name, char* mode);

FILE* get_readable_file(void) {
	return get_file_ptr("./todos.txt", "r");
}

FILE* get_writable_file(void) {
	return get_file_ptr("./todos.txt", "w");
}

FILE* get_appendable_file(void) {
	return get_file_ptr("./todos.txt", "a");
}

FILE* get_temp_file(void) {
	return get_file_ptr("./todos.tmp", "w");
}

FILE* get_file_ptr(char* file_name, char* mode) {
	FILE *fptr;
	fptr = fopen(file_name, mode);
	if (fptr == NULL) {
		printf("There was a problem reading the file.\n");
		exit(EXIT_FAILURE);
	}
	return fptr;
} 
