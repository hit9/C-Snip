# vim:set noet:

default: runtests

NAME=test
CC=cc -std=c99
OPTIMIZATION?=-O2
CFLAGS=-Wall $(OPTIMIZATION) -D_GNU_SOURCE -g -I../include
LDFLAGS=-Wall -pthread
BIN=$(NAME)
SRC:=$(wildcard ../src/*.c) $(wildcard *.c)
EV_EPOLL:=$(wildcard ../src/event_epoll.c)
EV_KQUEUE:=$(wildcard ../src/event_kqueue.c)
EV_TIMER:=$(wildcard ../src/event_timer.c)
SRC:=$(filter-out $(EV_EPOLL), $(SRC))
SRC:=$(filter-out $(EV_KQUEUE), $(SRC))
SRC:=$(filter-out $(EV_TIMER), $(SRC))
OBJ:=$(SRC:c=o)
LOG:=$(NAME)-mtrace.log
UNAME=$(shell uname)

$(BIN): $(OBJ)

runtests: $(BIN)
ifeq ($(UNAME), Linux)
	@env MALLOC_TRACE=$(LOG) ./$(BIN)
	@mtrace $(BIN) $(LOG)
else
	./$(BIN)
endif

clean:
	rm -f $(BIN) $(LOG) $(OBJ) test.log*
