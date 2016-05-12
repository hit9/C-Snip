# vim:set noet:

runtests:
	make runtests -C test

examples:
	make example -C example

runbench:
	make runbench -C bench

lint:
	python lint.py

lintfix:
	python lint.py fix

clean:
	rm -f src/*.o
	make clean -C test
	make clean -C example
	make clean -C bench
