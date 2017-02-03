SHELL = /bin/bash
default: lab2_add.c lab2_list.c SortedList.c
	gcc -g -pthread -Wall lab2_add.c -o lab2_add -lrt
	gcc -o lab2_list -g lab2_list.c SortedList.c  -pthread -lrt -Wall

build: lab2_add.c lab2_list.c SortedList.c
	gcc -g -pthread -Wall lab2_add.c -o lab2_add -lrt
	gcc -o lab2_list -g lab2_list.c SortedList.c  -pthread -lrt -Wall

profile: lab2_list Makefile
	-rm -f ./raw.gperf
	LD_PRELOAD=/u/cs/ugrad/jennifel/cs111/proj2/proj2b/gperftools/lib/libprofiler.so.0 CPUPROFILE=./raw.gperf ./lab2_list --threads=12 --iterations=1000 --sync=s
	./pprof --text ./lab2_list ./raw.gperf > profile.gperf
	./pprof --list=thread_func ./lab2_list ./raw.gperf >> profile.gperf
	rm -f ./raw.gperf

graphs:
	/u/cs/grad/zhou/iloveos/gnuplot lab2b.gp
	#/u/cs/grad/zhou/iloveos/gnuplot lab2_add.gp
	#/u/cs/grad/zhou/iloveos/gnuplot lab2_list.gp

make clean:
	@rm -rf *~ lab2_add lab2_list *.o 

tarball:
	@tar -cvzf lab2b-904299916.tar.gz *.c Makefile README.txt *.png *.h *.csv *.gperf lab2b.gp

tests:	lab2_add lab2_list lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=100 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=1000 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=10000 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=100000 >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=100 >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=1000 >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=10000 >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=100000 >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=100 >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=1000 >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=10000 >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=100000 >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=100 >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=1000 >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=10000 >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=100000 >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=100 >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=1000 >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=10000 >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=100000 >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=10 --yield >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=20 --yield >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=40 --yield >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=80 --yield >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=100 --yield >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=1000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=10000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=100000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=10 --yield >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=20 --yield >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=80 --yield >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=100 --yield >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=1000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=10000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=100000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=10 --yield >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=20 --yield >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=40 --yield >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=80 --yield >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=100 --yield >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=1000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=10000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=100000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=10 --yield >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=20 --yield >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=40 --yield >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=80 --yield >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=100 --yield >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=1000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=10000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=100000 --yield >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=10 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=20 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=40 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=80 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=100 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=1000 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=10000 >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=100000 >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=100 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=1000 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=10000 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=100 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=1000 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=10000 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=100 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=1000 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=10000 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=100 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=1000 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=10000 --yield --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=100 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=1000 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=10000 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=100 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=1000 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=10000 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=100 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=1000 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=10000 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=100 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=1000 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=10000 --yield --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=100 --yield --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=1000 --yield --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=100 --yield --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=1000 --yield --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=100 --yield --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=1000 --yield --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=100 --yield --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=1000 --yield --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=10000 --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=10000 --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=10000 --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=10000 --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=10000 --sync=m >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=10000 --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=10000 --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=10000 --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=10000 --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=10000 --sync=s >>lab_2b_list.csv
	-./lab2_add --threads=1 --iterations=10000 --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=2 --iterations=10000 --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=4 --iterations=10000 --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=8 --iterations=10000 --sync=c >>lab_2b_list.csv
	-./lab2_add --threads=12 --iterations=10000 --sync=c >>lab_2b_list.csv

	#list
	-./lab2_list --threads=1 --iterations=10 >>lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=100 >>lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 >>lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=10000 >>lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=20000 >>lab_2b_list.csv
	# conflicts w/o yielding
	-./lab2_list --threads=2 --iterations=10 >>lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=100 >>lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 >>lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=10 >>lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=100 >>lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 >>lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=10 >>lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=100 >>lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=10 >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=100 >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 >>lab_2b_list.csv
	# generate insert conflicts
	-./lab2_list --threads=2 --iterations=2 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=4 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=8 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=16 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=32 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=32 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=32 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=i >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=32 --yield=i >>lab_2b_list.csv
	# generate delete conflicts
	-./lab2_list --threads=2 --iterations=2 --yield=d >>lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=4 --yield=d >>lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=8 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=16 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=32 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=32 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=32 --yield=d >>lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=d >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=32 --yield=d >>lab_2b_list.csv
	# generate insert/lookup conflicts
	-./lab2_list --threads=2 --iterations=2 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=4 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=8 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=16 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=32 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=32 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=32 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=il >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=32 --yield=il >> lab_2b_list.csv
	# generate delete/lookup conflicts
	-./lab2_list --threads=2 --iterations=2 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=4 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=8 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=16 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=32 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=32 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=32 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=dl >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=32 --yield=dl >> lab_2b_list.csv
	# measure the performance
	-./lab2_list --threads=1 --iterations=1000 >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=24 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=1000 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=24 --iterations=1000 --sync=s >> lab_2b_list.csv
	# demonstrate the efficacy of mutex and spin-lock synchronization
	#-./lab2_list --threads=12 --iterations=32 --yield=i --sync=m >> lab_2b_list.csv
	#-./lab2_list --threads=12 --iterations=32 --yield=d --sync=m >> lab_2b_list.csv
	#-./lab2_list --threads=12 --iterations=32 --yield=il --sync=m >> lab_2b_list.csv
	#-./lab2_list --threads=12 --iterations=32 --yield=dl --sync=m >> lab_2b_list.csv
	#-./lab2_list --threads=12 --iterations=32 --yield=i --sync=s >> lab_2b_list.csv
	#-./lab2_list --threads=12 --iterations=32 --yield=d --sync=s >> lab_2b_list.csv
	#-./lab2_list --threads=12 --iterations=32 --yield=il --sync=s >> lab_2b_list.csv
	#-./lab2_list --threads=12 --iterations=32 --yield=dl --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=2 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=4 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=8 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=16 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=2 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=4 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=8 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=16 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=2 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=4 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=8 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=16 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=2 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=4 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=8 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=16 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=1 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=2 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=4 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=8 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=16 --lists=4 --yield=id >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=10 --lists=4 --yield=id --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=20 --lists=4 --yield=id --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=40 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=80 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=10 --lists=4 --yield=id --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=20 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=40 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=80 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=10 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=20 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=40 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=80 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=10 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=20 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=40 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=80 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=10 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=20 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=40 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=80 --lists=4 --yield=id --sync=m  >> lab_2b_list.csv

	-./lab2_list --threads=1 --iterations=10 --lists=4 --yield=id --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=20 --lists=4 --yield=id --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=40 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=80 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=10 --lists=4 --yield=id --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=20 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=40 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=80 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=10 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=20 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=40 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=80 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=10 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=20 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=40 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=80 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=10 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=20 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=40 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=80 --lists=4 --yield=id --sync=s  >> lab_2b_list.csv

	-./lab2_list --threads=1 --iterations=1000 --list=1 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --list=1 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --list=1 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --list=1 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --list=1 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=24 --iterations=1000 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 --list=4 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --list=4 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --list=4 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --list=4 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --list=4 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 --list=8 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --list=8 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --list=8 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --list=8 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --list=8 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 --list=16 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --list=16 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --list=16 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --list=16 --sync=m >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --list=16 --sync=m >> lab_2b_list.csv

	-./lab2_list --threads=1 --iterations=1000 --list=1 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --list=1 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --list=1 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --list=1 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --list=1 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=16 --iterations=1000 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=24 --iterations=1000 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 --list=4 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --list=4 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --list=4 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --list=4 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --list=4 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 --list=8 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --list=8 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --list=8 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --list=8 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --list=8 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=1 --iterations=1000 --list=16 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --list=16 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --list=16 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --list=16 --sync=s >> lab_2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --list=16 --sync=s >> lab_2b_list.csv
