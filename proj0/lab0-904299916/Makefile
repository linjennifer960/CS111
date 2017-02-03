SHELL = /bin/bash

default:lab0.c
	gcc -g lab0.c -o lab0

check: lab0
	@echo "Input test" >in.txt
	@./lab0 --input=in.txt --output=out.txt
	@diff in.txt out.txt > /dev/null && echo -e "Passed Test 1, input correctly copied to output" || echo -e "Test 1 failed, for more details please open README"

	@(./lab0 --segfault --catch; true) >& catch1
	@(./lab0 --catch --segfault; true) >& catch2
	@diff catch1 catch2 > /dev/null && echo -e "Passed Test 2, segfault successfully caught" || echo -e "Test 2 failed, for more details please open README"
	@echo "Input for test 3" >test3.txt
	@cat test3.txt | ./lab0 --output=test3Result.txt
	@diff test3.txt test3Result.txt > /dev/null && echo -e "Passed Test 3, file input matches with stdout" || echo -e "Test 3 failed, for more details please open README"

	@echo "Passed all tests"

clean:
	@rm -rf lab0 in.txt out.txt catch1 catch2 test3.txt test3Result.txt *.o *~

dist:
	@tar -cvzf lab0-904299916.tar.gz lab0.c README Makefile backtrace.png breakpoint.png
