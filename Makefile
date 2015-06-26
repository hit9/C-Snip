# vim:set noet:

default: test

.DEFAULT:
	make $@ -C src
