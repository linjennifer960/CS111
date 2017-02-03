# purpose:
#	generate data refuction graphs for lab2b
#
#

# general plot parameters
set terminal png
set datafile separator ","

set title "Scalability-1: Synchronized Throughput"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set ylabel "Throughput (operations/sec)"
set logscale y 10
set output 'lab2b_1.png'
set key left top

#grep out only successful (sum=0) yield runs
plot \
     "< grep add-m lab_2b_list.csv" using ($2):(1000000000/($6)) \
	title 'adds w/ mutex' with linespoints lc rgb 'green', \
     "< grep add-s lab_2b_list.csv" using ($2):(1000000000/($6)) \
	title 'adds w/ spin' with linespoints lc rgb 'blue',\
	 "< grep list-none-m,[0-9]*,1000,1, lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'mutex list' with linespoints lc rgb 'orange',\
     "< grep list-none-s,[0-9]*,1000,1, lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'spin list' with linespoints lc rgb 'violet'

# lab2b_2.png
set title "Scalability-2: Per-operation Times for List Operations"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set ylabel "average time/operation (ns)"
set logscale y 10
set output 'lab2b_2.png'
set key left top

plot \
     "< grep list-none-m,[1,2,4,8][4,6]*,1000,1, lab_2b_list.csv" using ($2):($7) \
	title 'average time per op' with linespoints lc rgb 'orange',\
     "< grep list-none-m,[1,2,4,8][4,6]*,1000,1, lab_2b_list.csv" using ($2):($8) \
	title 'wait for lock' with linespoints lc rgb 'red'

# lab2b_3.png
set title "Scalability-3: Correct Synchronization of Partitioned Lists"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set ylabel "average time/operation (ns)"
set output 'lab2b_3.png'
set key left top

plot \
	"<grep list-id-none lab_2b_list.csv" using ($2):($7)\
	title "yield=id" with points lc rgb 'red',\
	"<grep list-id-m lab_2b_list.csv" using ($2):($7)\
	title "mutex" with points lc rgb 'green',\
	"<grep list-id-s lab_2b_list.csv" using ($2):($7)\
	title "spin-lock" with points lc rgb 'blue'

# lab2b_4.png
set title "Scalability-4: Mutex Synchronized Throughput of Partitioned Lists"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set ylabel "Throughput (operations/sec)"
set output 'lab2b_4.png'
set key left top

plot \
     "< grep list-none-m,[1,2,4,8]2*,1000,1, lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'lists=1' with linespoints lc rgb 'violet', \
     "< grep list-none-m,[0-9]*,1000,4 lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'lists=4' with linespoints lc rgb 'green',\
	 "< grep list-none-m,[0-9]*,1000,8 lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'lists=8' with linespoints lc rgb 'blue',\
     "< grep list-none-m,[0-9]*,1000,16 lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'lists=16' with linespoints lc rgb 'orange'

# lab2b_5.png
set title "Scalability-5: Spin-Lock Synchronized Throughput of Partitioned Lists"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set ylabel "Throughput (operations/sec)"
set logscale y 10
set output 'lab2b_5.png'
set key left top

plot \
     "< grep list-none-s,[1,2,4,8]2*,1000,1, lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'lists=1' with linespoints lc rgb 'violet', \
     "< grep list-none-s,[0-9]*,1000,4 lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'lists=4' with linespoints lc rgb 'green',\
	 "< grep list-none-s,[0-9]*,1000,8 lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'lists=8' with linespoints lc rgb 'blue',\
     "< grep list-none-s,[0-9]*,1000,16 lab_2b_list.csv" using ($2):(1000000000/($7)) \
	title 'lists=16' with linespoints lc rgb 'orange'




