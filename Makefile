CC = gcc
CFLAGS = -g -std=c99 -Wall -fsanitize=address,undefined

all: program good bad

program: mymalloc.o memgrind.o
	$(CC) $(CFLAGS) -o $@ $^

good: mymalloc.o good.o
	$(CC) $(CFLAGS) -o $@ $^

bad: mymalloc.o bad.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

mymalloc.c: mymalloc.h
memgrind.c: mymalloc.h
good.c: mymalloc.h
bad.c: mymalloc.h

clean:
	rm -f program err success *.o