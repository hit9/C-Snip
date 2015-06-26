# vim:set noet:

default: all

ifeq ($(shell uname), Linux)
define runtest
	$(eval name := $(strip $1))
	touch $(name).log
	env MALLOC_TRACE=$(name).log ./$(name)
	mtrace $(name) $(name).log
endef
else
define runtest
	$(eval name := $(strip $1))
	./$(name)
endef
endif

###
# Test Items
###
bool_test: bool_test.c
string_test: string_test.c string.c

###
# Other Rules
###
all: bool_test string_test

test: all
	$(call runtest, bool_test)
	$(call runtest, string_test)

clean:
	rm *_test *.log
