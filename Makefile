CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic-errors -O3
LDFLAGS=

SRC=$(shell find . -name *.c)
OBJ=$(SRC:%.c=%.o)
BIN=bin/htcpcp

all: $(BIN)

run: $(BIN)
	$(BIN) ${ARGS}

$(BIN): $(OBJ)
	mkdir -p ./bin/
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r ./bin
	rm $(shell find . -name *.o)
