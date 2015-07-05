# vim:set noet:

default: test

NAME   = test
CC     = cc
CFLAGS = 
SRC    = test.c bool_test.c string.c string_test.c stack.c stack_test.c \
		 queue.c queue_test.c
OBJ    = $(SRC:c=o)
UNAME  = $(shell uname)

test: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)
ifeq ($(UNAME), Linux)
	@touch $(NAME).log
	@env MALLOC_TRACE=$(NAME).log ./$(NAME)
	@echo "======> leaks detection <======="
	@mtrace $(NAME) $(NAME).log
else
	./$(NAME)
endif

clean:
	rm -rf $(NAME) $(NAME).log $(OBJ)
