lab4: lab4a.c lab4b.c
	@gcc -g -lmraa -Wall lab4a.c -o lab4a -lm
	@gcc -g -lmraa -Wall lab4b.c -o lab4b -lm -lpthread

clean:
	@rm log1.txt
	@rm log2.txt
	@rm lab4a
	@rm lab4b

test:
	@./lab4a
	@./lab4b

tarball:
	@tar -cvzf lab4-904299916.tar.gz lab4a.c lab4b.c log1.txt log2.txt Makefile
