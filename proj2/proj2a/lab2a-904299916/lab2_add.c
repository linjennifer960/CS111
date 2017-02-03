#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <pthread.h>

long long counter = 0;
int val=0;
int threadNum = 1;
int iterNum = 1;
char* msg;
int opt_yield=0;
int sync=0;
char s;
int lock=0;
pthread_mutex_t mutex;
long long temp=0;
long long sum=0;

void add(long long *pointer, long long value){
    long long sum = *pointer + value;
    if(opt_yield)
        sched_yield();
    *pointer = sum;
}

void meow(void){
    int i;
    for(i=0; i<iterNum; i++){
        pthread_mutex_lock(&mutex);
        add(&counter, 1);
        pthread_mutex_unlock(&mutex);
    }
    for(i=0; i<iterNum; i++){
        pthread_mutex_lock(&mutex);
        add(&counter, -1);
        pthread_mutex_unlock(&mutex);
    }
}

void spin(void){
    int j;
    for(j=0; j<iterNum; j++){
        while (__sync_lock_test_and_set(&lock, 1));
        add(&counter, 1);
        __sync_lock_release(&lock);
    }
    for(j=0; j<iterNum; j++){
        while (__sync_lock_test_and_set(&lock, 1));
        add(&counter, -1);
        __sync_lock_release(&lock);
    }
}

void compare(void){
    int k;
    for(k=0; k<iterNum; k++){
        do{
            temp = counter;
            sum = temp + 1;
            if(opt_yield)
                pthread_yield();
        }while(__sync_val_compare_and_swap(&counter, temp, sum) != temp);
    }
    for(k=0; k<iterNum; k++){
        do{
            temp = counter;
            sum = temp - 1;
            if(opt_yield)
                pthread_yield();
        }while(__sync_val_compare_and_swap(&counter, temp, sum) != temp);
    }
}

void* thread_func(void *arg){
    if(sync){ //sync option
        switch(s){
                case 'm': //mutex
                    meow();
                    break;
                case 's': //spin lock
                    spin();
                    break;
                case 'c': //compare and swap
                    compare();
                    break;
                default:
                    break;
        }
    }
    else{
        int l;
        for(l=0; l<iterNum; l++){
            add(&counter, 1);
        }
        for(l=0; l<iterNum; l++){
            add(&counter, -1);
        }
    }
    return NULL;
}
         
int main(int argc, char* argv[]){
    static struct option longOptions[]={
        {"threads", required_argument, NULL, 't'},
        {"iterations", required_argument, NULL, 'i'},
        {"yield", no_argument, NULL, 'y'},
        {"sync", required_argument, NULL, 's'}
    };
    while(1){
        val = getopt_long(argc, argv, "", longOptions, NULL);
        if(val == -1)
            break;
        switch(val){
            case 't':
                threadNum = atoi(optarg);
                break;
                
            case 'i':
                iterNum = atoi(optarg);
                break;
            
            case 'y':
                opt_yield=1;
                break;
                
            case 's':
                sync=1;
                s = *optarg;
                break;
        
            default:
                break;
        }
    }

    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
	
    if(sync && s=='m')
        pthread_mutex_init(&mutex, NULL);
    
    pthread_t* pid;
    pid = (pthread_t*) malloc(sizeof(pthread_t)*threadNum);
    
    int h;
    for(h=0; h < threadNum; h++){
        if(pthread_create(&pid[h], NULL, thread_func, NULL)){
            fprintf(stderr, "Error when creating threads. \n");
            exit(1);
        }
    }
    for(h=0; h < threadNum; h++){
        if(pthread_join(pid[h], NULL)){
            fprintf(stderr, "Error when joining threads. \n");
            exit(1);
        }
    }
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    
    free(pid);
    
    if(sync){
        switch(s){
            case 'm':
                if(opt_yield)
                    msg="add-yield-m";
                else
                    msg="add-m";
                break;
            case 's':
                if(opt_yield)
                    msg="add-yield-s";
                else
                    msg="add-s";
                break;
            case 'c':
                if(opt_yield)
                    msg="add-yield-c";
                else
                    msg="add-c";
                break;
            default:
                break;
        }
    }
    else{
        if(opt_yield)
            msg="add-yield-none";
        else
            msg="add-none";
    }
    
    long long total_time = (end_time.tv_sec - start_time.tv_sec)*1000000000;
    total_time += end_time.tv_nsec;
    total_time -= start_time.tv_nsec;
    
    long long operationNum = threadNum*iterNum*2;
    int average_op_time = total_time/operationNum;
    
    printf("%s,%d,%d,%lld,%lld,%d,%lld\n", msg, threadNum, iterNum, operationNum, total_time, average_op_time, counter);
    if(counter != 0){
        fprintf(stderr, "Counter should be 0. \n");
    }
    exit(0);
    return 0;
}


