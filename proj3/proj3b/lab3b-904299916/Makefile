SHELL = /bin/bash

default: lab3b.py
	@echo "No compilation required for Python script, use 'make run' to run program"

run:	lab3b.py
	python lab3b.py

clean:
	@rm -rf *~ *txt

dist:
	@tar -cvzf lab3b-904299916.tar.gz README lab3b.py Makefile
