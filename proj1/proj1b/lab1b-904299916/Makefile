SHELL = /bin/bash

default: client.c server.c
	gcc -g -pthread -lmcrypt client.c -o client
	gcc -g -pthread -lmcrypt server.c -o server

client: client.c
	gcc -g -pthread -lmcrypt client.c -o client

server: server.c
	gcc -g -pthread -lmcrypt server.c -o server

clean:
	@rm -rf *~ client server *.o *.txt

dist:
	@tar -cvzf lab1b-904299916.tar.gz client.c server.c README Makefile my.key
