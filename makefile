all: mymalloc.c mymalloc.h

first: first.c
	gcc -Wall -Werror -fsanitize=address -std=c11 first.c -o first

clean: 
	rm -rf first

