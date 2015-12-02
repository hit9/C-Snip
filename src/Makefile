# vim:set noet:

default: runtest

NAME=test
CC=cc
OPTIMIZATION?=-O2
CFLAGS=-Wall $(OPTIMIZATION)
LDFLAGS=-Wall -pthread
BIN=$(NAME)
SRC:=$(wildcard *.c)
EV_EPOLL:=$(wildcard event_epoll.c)
EV_KQUEUE:=$(wildcard event_kqueue.c)
EXAMPLE:=$(wildcard *_example.c)
SRC:=$(filter-out $(EV_EPOLL), $(SRC))
SRC:=$(filter-out $(EV_KQUEUE), $(SRC))
SRC:=$(filter-out $(EXAMPLE), $(SRC))
INC:=$(wildcard *.h)
OBJ:=$(SRC:c=o)
LOG:=$(NAME)-mtrace.log
UNAME=$(shell uname)

$(BIN): $(OBJ)
$(OBJ): $(INC) $(SRC)

runtest: $(BIN)
ifeq ($(UNAME), Linux)
	@env MALLOC_TRACE=$(LOG) ./$(BIN)
	@mtrace $(BIN) $(LOG)
else
	./$(BIN)
endif

clean:
	rm -f $(BIN) $(LOG) $(OBJ) test.log* *.out
