CC = gcc
CFLAGS = -Wall

all: main

main: main.c matriz.c matriz.h
	$(CC) $(CFLAGS) -o main main.c matriz.c -I.

clean:
	rm -f main
