# vim:set noet:

default: all

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
	./bool_test
	./string_test

clean:
	rm -r *_test
