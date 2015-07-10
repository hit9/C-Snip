# vim:set noet:

default: runtest

.DEFAULT:
	make $@ -C src
