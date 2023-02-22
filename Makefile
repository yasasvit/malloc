CC = gcc
CFLAGS = -g -std=c99 -Wall -fsanitize=address,undefined

program: mymalloc.o memgrind.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

mymalloc.c: mymalloc.h
memgrind.c: mymalloc.h

clean:
	rm -f program *.o