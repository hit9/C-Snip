# vim:set noet:

default: all

.DEFAULT:
	make $@ -C src
