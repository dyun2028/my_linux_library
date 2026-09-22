CC = gcc
FLAGS = -Wall -Wextra -g -std=c11
SRC = src/echo_server.c
TARGET = build/echo_server

.PHONY: clean
$(TARGET): $(SRC)
	mkdir -p build
	$(CC) $(FLAGS) $(SRC) -o $(TARGET)
clean:
	rm -rf build/*
