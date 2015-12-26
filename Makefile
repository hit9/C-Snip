# vim:set noet:

runtests:
	make runtests -C test

examples:
	make example -C example

clean:
	rm -f src/*.o
	make clean -C test
	make clean -C example
