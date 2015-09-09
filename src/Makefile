# vim:set noet:

default: runtest

NAME    = test
CC      = cc
CFLAGS  =
LDFLAGS = -pthread
SRC     = test.c\
		  log.c\
		  bool_test.c\
		  buf.c buf_test.c\
		  stack.c stack_test.c\
		  queue.c queue_test.c\
		  list.c list_test.c\
		  dict.c dict_test.c\
		  array.c array_test.c\
		  utils.c utils_test.c\
		  event.c event_test.c\
		  ketama.c ketama_test.c\
		  cfg.c cfg_test.c\

OBJ    = $(SRC:c=o)
BIN    = $(NAME)
UNAME  = $(shell uname)

$(BIN): $(OBJ)

runtest: $(BIN)
ifeq ($(UNAME), Linux)
	@touch $(NAME).log
	@env MALLOC_TRACE=$(NAME).log ./$(BIN)
	@echo "[leaks detection]" && printf "  "
	@mtrace $(BIN) $(NAME).log
else
	./$(BIN)
endif

clean:
	rm -rf $(BIN) $(NAME).log $(OBJ)
