CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11 -pthread -Iinclude -fsanitize=thread
SRC = src/echo_server.c src/echo_client.c
BINS = build/echo_server build/echo_client

.PHONY: clean all
all: $(BINS)
	
build/%: src/%.c | build logs
	$(CC) $(CFLAGS) $< -o $@
build:
	mkdir -p build
logs:
	mkdir -p logs
clean:
	rm -rf build/*
