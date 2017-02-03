Jennifer Lin
CS111 Project 2A

Description of included files:

Ques 2.1.1: This is because when there are more iterations, each thread will access the same variable more times, which
increases the changes of a race condition happening which leads to failure. When it's the case of a single thread however,
there won't be a failure because only on thread is using the resources, thus a race condition will not happen.

Ques 2.1.2: The --yield runs slower because of context switches. It calls pthread_yield() and spends more time with privileges instructions
that change thread states between running and ready. It is not possible to get valid per-operation timings with yield because it is not
possible to remove all context switches.

Ques 2.1.3:

Ques 2.1.4: 

Ques 2.1.5:

Ques 2.1.6:
