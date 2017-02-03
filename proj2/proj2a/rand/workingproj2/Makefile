SHELL = /bin/bash
default: lab2_add.c
	gcc -g -pthread -Wall lab2_add.c -o lab2_add -lrt

graphs:
	/u/cs/grad/zhou/iloveos/gnuplot lab2_add.gp

make clean:

make tarball: 
tests:
	./lab2_add --threads=1 --iterations=100 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100 >>lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 >>lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100 >>lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 >>lab2_add.csv
	./lab2_add --threads=8 --iterations=100 >>lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 >>lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 >>lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 >>lab2_add.csv
	./lab2_add --threads=12 --iterations=100 >>lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 >>lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 >>lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 >>lab2_add.csv
	./lab2_add --threads=2 --iterations=10 --yield >>lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --yield >>lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --yield >>lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --yield >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield >>lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield >>lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --yield >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield >>lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield >>lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield >>lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield >>lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield >>lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield >>lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield >>lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield >>lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield >>lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield >>lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield >>lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield >>lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield >>lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield >>lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield >>lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield >>lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield >>lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield >>lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield >>lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield >>lab2_add.csv
	./lab2_add --threads=1 --iterations=10 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=20 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=40 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=80 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=100 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield --sync=m >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield --sync=c >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield --sync=s >>lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield --sync=s >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=s >>lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=s >>lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=s >>lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=s >>lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=s >>lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=s >>lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=m >>lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=m >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=m >>lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=m >>lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=m >>lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=s >>lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=s >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=s >>lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=s >>lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=s >>lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=c >>lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=c >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=c >>lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=c >>lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=c >>lab2_add.csv
