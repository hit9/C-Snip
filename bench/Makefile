# vim:set noet:

default: runbench

NAME=bench
CC=cc -std=c99
OPTIMIZATION?=-O2
CFLAGS=-Wall $(OPTIMIZATION) -D_GNU_SOURCE -g -I../include
LDFLAGS=-Wall -pthread
BIN=$(NAME)
SRC:=$(wildcard ../src/*.c) $(wildcard *.c)
EV_EPOLL:=$(wildcard ../src/event_epoll.c)
EV_KQUEUE:=$(wildcard ../src/event_kqueue.c)
SRC:=$(filter-out $(EV_EPOLL), $(SRC))
SRC:=$(filter-out $(EV_KQUEUE), $(SRC))
OBJ:=$(SRC:c=o)

$(BIN): $(OBJ)

runbench: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN) $(OBJ)
