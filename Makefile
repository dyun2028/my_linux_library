CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11 -Iinclude
SRC = src/echo_server.c src/echo_client.c
BINS = build/echo_server build/echo_client

.PHONY: clean all
all: $(BINS)
	
build/%: src/%.c | build
	$(CC) $(CFLAGS) $< -o $@
build:
	mkdir -p build
clean:
	rm -rf build/*
