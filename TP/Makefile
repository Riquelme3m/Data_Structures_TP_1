CC = gcc
CFLAGS = -Wall -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
BIN = bin/tp1.out

all: $(BIN)

bin:
	mkdir -p bin

obj:
	mkdir -p obj

$(BIN): bin obj $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj bin

.PHONY: all clean
