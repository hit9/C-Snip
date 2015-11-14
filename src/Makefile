# vim:set noet:

default: runtest

NAME    = test
CC      = cc
CFLAGS  =
LDFLAGS = -pthread
SRC     = bool_test.c\
		  buf.c\
		  buf_test.c\
		  cfg.c\
		  cfg_test.c\
		  datetime.c\
		  datetime_test.c\
		  dict.c\
		  dict_test.c\
		  event.c\
		  event_test.c\
		  heap.c\
		  heap_test.c\
		  ketama.c\
		  ketama_test.c\
		  list.c\
		  list_test.c\
		  log.c\
		  log_test.c\
		  md5.c\
		  queue.c\
		  queue_test.c\
		  stack.c\
		  stack_test.c\
		  strings.c\
		  strings_test.c\
		  test.c\
		  utils_test.c\

OBJ    = $(SRC:c=o)
BIN    = $(NAME)
UNAME  = $(shell uname)

$(BIN): $(OBJ)

runtest: $(BIN)
ifeq ($(UNAME), Linux)
	@touch $(NAME).log
	@env MALLOC_TRACE=leaks-$(NAME).log ./$(BIN)
	@echo "[leaks detection]" && printf "  "
	@mtrace $(BIN) leaks-$(NAME).log
else
	./$(BIN)
endif

clean:
	rm -rf $(BIN) leaks-$(NAME).log $(OBJ) test.log* *.out
