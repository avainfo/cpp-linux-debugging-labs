CC := gcc

CFLAGS := -std=c11 -g -O0 -Wall -Wextra -Wpedantic

.PHONY: all clean

all: buggy

buggy: buggy.c
	$(CC) $(CFLAGS) buggy.c -o buggy

clean:
	rm -f buggy fixed
