SHELL = /bin/bash

default: gcc -g lab0.c -o lab0

check: lab0
	@echo "Input test" >in.txt
	@./lab0 --input=in.txt --output=out.txt
	@diff in.txt out.txt > /dev/null && echo -e "Passed Test 1, for more details please open README" || echo -e "Test 1 failed, for more details please open README"

	@./lab0 --segfault --catch; true) >& catch1
	@./lab0 --catch --segfault; true) >& catch2
	@diff catch1 catch 2 > /dev/null @@ echo -e "Passed Test 2, segfault successfully caught" || echo -e "Test 2 failed, for more details please open README"

clean: rm lab0

dist: tar -cvzf lab0-904299916.tar.gz lab0.c README Makefile backtrace.jpg breakpoint.jpg
