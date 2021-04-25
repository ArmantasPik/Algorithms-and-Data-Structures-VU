all: main run

main: main.c
	gcc -o main main.c functions.c vector.c BST.c

run: main.c
	./main

.PHONY: all main run