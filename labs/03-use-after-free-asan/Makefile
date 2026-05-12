CC := gcc

CFLAGS := -std=c11 -g -O0 -Wall -Wextra -Wpedantic -fsanitize=address  -fno-omit-frame-pointer

.PHONY: all clean

all: buggy fixed

buggy: buggy.c
	$(CC) $(CFLAGS) buggy.c -o buggy

fixed: fixed.c
	$(CC) $(CFLAGS) fixed.c -o fixed

clean:
	rm -f buggy fixed
