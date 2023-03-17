CC = gcc
CFLAGS = -g -Wall -Werror -lm

build: main

main1: main.c
	$(CC) -o  main main.c $(CFLAGS)
clean:
	rm -f main
