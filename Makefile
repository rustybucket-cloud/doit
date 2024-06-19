main:
	gcc -o doit main.c files.c todos.c active.c
run:
	make && ./doit

