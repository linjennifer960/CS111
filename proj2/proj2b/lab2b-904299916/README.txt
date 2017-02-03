Jennifer Lin
CS111 Project 2B
UID: 904299916


Included files:
	 -SortedList.h: header file containing interfaces for linked list operations
	 -SortedList.c: implements insert, delete, lookup, and length methods for a sorted doubly linkedlist
	 -lab2_list.c: implements (--threads, --iterations, --yield, --sync, --lists) according to the specc
	 -Makefile: provide build, tests, profile, graphs, tarball, and clean targets
	 -lab_2b_list.csv: containing data results from make tests
	 -graphs (lab2b_1.png ~ lab2b_5.png): created from make graphs using data in lab_2b_list.csv
	 -README.txt: briefly discuss included files and answers questions in the spec


Question 2.3.1:
	 When there's only 1 or 2 threads, most of the cycles are spent in the operation themselves because
	 chances of conflicts are lower so it wouldn't go into locking. Moreover, when there is only 1 thread,
	 there will be no contention. When it is the case of high-threads, however, the chances of conflicts
	 are higher, therefore most of the cycles are spent in spinning or waiting for locks.

Question 2.3.2:
	 Lines of code involving spin lock:    ( while (__sync_lock_test_and_set(&lock, 1))
	 are consuming most of the cycles when the list exerciser
	 is run with a large number of threads. This operation is expensive because time is spent on
	 waiting and spinning and it cannot do other operations and execute elsewhere.

Question 2.3.3:
	 The average lock-wait time rises dramatically with the number of contending threads because
	 only 1 thread can enter critical sections at a time. Therefore when there are more threads, more threads
	 will be kept waiting and thus resulting in a longer lock-wait time. Completion time per operation
	 rises less dramatically because the overhead is distributed among the threads, resulting in a more
	 gradual increase in completion time compared to average lock-wait time. Wait time per operation
	 appears to go up higher than completion time per operation because wait for lock time is CPU time
	 while completion time is wall time.

Question 2.3.4:
	 It seems that as the number of lists increase, the throughput shall continue increasing. When
	 we have more lists, the possibility of contention drops, and so does the time of each operation.
	 The reasoning in the last part of this question is reasonable because as more threads work on
	 their sublists respectively, the throughput should resemble the throughput of a single list with few
	 threads. 
	 
