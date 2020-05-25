CC = gcc

File: m2_shell.o
	gcc m2_shell.o -o shell

m2_shell.c: m2_shell.o
	gcc m2_shell.c -c

clean:
	rm -rf m2_shell.o shell