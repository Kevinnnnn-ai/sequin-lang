CC = gcc
CFLAGS = -Wall -g -std=c11 -Wextra
SRC = $(wildcard src/*.c)
OBJ = $(SRC: src/%.c = build/%.o)

sequin: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build sequin

.PHONY: clean