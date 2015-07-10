# vim:set noet:

default: runtest

NAME   = test
CC     = cc
CFLAGS = 
SRC    = test.c 				\
		 bool_test.c 			\
		 string.c string_test.c \
		 stack.c stack_test.c 	\
		 queue.c queue_test.c 	\
		 list.c list_test.c 	\
		 dict.c dict_test.c

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
