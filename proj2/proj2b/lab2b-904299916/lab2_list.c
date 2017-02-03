#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>
#include "SortedList.h"

int val=0;
int threadNum = 1;
int iterNum = 1;
int opt_yield=0;
int sync=0;
char s;
int* lock;
pthread_mutex_t* mutex;
SortedListElement_t* head;
SortedListElement_t *elementList;
long long mutex_wait_time=0;
struct timespec m_start;
struct timespec m_end;
int list=0;

int hash(const char* key){
    int total=0;
    int c;
    for(c=0; c < sizeof(key); c++)
        total += key[c];
    return total % list;
}

void* thread_func(void *arg){
    int idx=0;
    int *ofs = (int*) arg;
    int test;
    int del;
    if(sync){
        int i;
        for(i=0; i<iterNum; i++){
            idx=hash(elementList[*ofs + i].key);
                switch(s){
                    case 's': //spin lock
                        while (__sync_lock_test_and_set(&lock[idx], 1));
                        SortedList_insert(&head[idx], &elementList[*ofs + i]);
                        __sync_lock_release(&lock[idx]);
                        break;
                    case 'm': //mutex
                        clock_gettime(CLOCK_MONOTONIC, &m_start);
                        
                        pthread_mutex_lock(&mutex[idx]);
                        
                        clock_gettime(CLOCK_MONOTONIC, &m_end);
                        
                        mutex_wait_time += (m_end.tv_sec - m_start.tv_sec)*1000000000;
                        mutex_wait_time += m_end.tv_nsec;
                        mutex_wait_time -= m_start.tv_nsec;
                        
                        SortedList_insert(&head[idx], &elementList[*ofs + i]);
                        pthread_mutex_unlock(&mutex[idx]);
                        break;
                    default:
                        break;
                }
        }
    }
    else{
        int p;
        for(p=0; p<iterNum; p++){
            idx=hash(elementList[*ofs + p].key);
            SortedList_insert(&head[idx], &elementList[*ofs + p]);
        }
    }
    
    int length=0;
    int v;
    if(sync){
        switch(s){
                case 's':
                    for(v=0; v<list; v++){
                        while (__sync_lock_test_and_set(&lock[v], 1));
                        test = SortedList_length(&head[v]);
                        if(test<0){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        length += test;
                        __sync_lock_release(&lock[v]);
                    }
                    break;
                case 'm':
                    for(v=0; v<list; v++){
                        clock_gettime(CLOCK_MONOTONIC, &m_start);
                
                        pthread_mutex_lock(&mutex[v]);
                
                        clock_gettime(CLOCK_MONOTONIC, &m_end);
                
                        mutex_wait_time += (m_end.tv_sec - m_start.tv_sec)*1000000000;
                        mutex_wait_time += m_end.tv_nsec;
                        mutex_wait_time -= m_start.tv_nsec;
                
                        test = SortedList_length(&head[v]);
                        if(test<0){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        length += test;
                        pthread_mutex_unlock(&mutex[v]);
                    }
                    break;
                default:
                    break;
        }
    }
    else{
        int s;
        for(s=0; s<list; s++){
            test=SortedList_length(&head[s]);
            if(test<0){
                fprintf(stderr, "Corruped list. \n");
                exit(1);
            }
            length+=test;
        }
    }
    SortedListElement_t *check;
    if(sync){
        int q;
        for(q=0; q<iterNum; q++){
            idx=hash(elementList[*ofs + q].key);
            switch(s){
                    case 's':
                        while (__sync_lock_test_and_set(&lock[idx], 1));
                        check = SortedList_lookup(&head[idx], elementList[*ofs + q].key);
                        if(check==NULL){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        del=SortedList_delete(check);
                        if(del==1){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        __sync_lock_release(&lock[idx]);
                        break;
                    case 'm':
                        clock_gettime(CLOCK_MONOTONIC, &m_start);
                    
                        pthread_mutex_lock(&mutex[idx]);
                    
                        clock_gettime(CLOCK_MONOTONIC, &m_end);
                    
                        mutex_wait_time += (m_end.tv_sec - m_start.tv_sec)*1000000000;
                        mutex_wait_time += m_end.tv_nsec;
                        mutex_wait_time -= m_start.tv_nsec;
                    
                        check = SortedList_lookup(&head[idx], elementList[*ofs + q].key);
                        if(check==NULL){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        del=SortedList_delete(check);
                        if(del==1){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        pthread_mutex_unlock(&mutex[idx]);
                        break;
                    default:
                        break;
            }
        }
    }
    else{
        int y;
        for(y=0; y<iterNum; y++){
            idx=hash(elementList[*ofs + y].key);
            check=SortedList_lookup(&head[idx], elementList[*ofs + y].key);
            if(check==NULL){
                fprintf(stderr, "Corrupted list. \n");
                exit(1);
            }
            del=SortedList_delete(check);
            if(del==1){
                fprintf(stderr, "Corrupted list. \n");
                exit(1);
            }
        }
    }
    return NULL;
}

int main(int argc, char* argv[]){
    static struct option longOptions[]={
        {"threads", required_argument, NULL, 't'},
        {"iterations", required_argument, NULL, 'i'},
        {"yield", required_argument, NULL, 'y'},
        {"sync", required_argument, NULL, 's'},
        {"lists", required_argument, NULL, 'l'}
    };
    int x;
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
                for(x=0; x<strlen(optarg); x++){
                    if(optarg[x]=='i')
                        opt_yield |= INSERT_YIELD;
                    else if(optarg[x]=='d')
                        opt_yield |= DELETE_YIELD;
                    else if(optarg[x]=='l')
                        opt_yield |= LOOKUP_YIELD;
                }
                break;
            case 's':
                sync=1;
                s = *optarg;
                break;
            case 'l':
                list= atoi(optarg);
                break;
            default:
                break;
        }
    }
    
    int elementNum=threadNum*iterNum;
    elementList=(SortedListElement_t*) malloc(sizeof(SortedListElement_t)*elementNum);
    pthread_t *pid;
    pid=(pthread_t*)malloc(sizeof(pthread_t)*threadNum);
    head = (SortedListElement_t*) malloc(sizeof(SortedListElement_t)*list);
    
    int k;
    for(k=0; k<list; k++){
        head[k].key=NULL;
        head[k].prev=&head[k];
        head[k].next=&head[k];
    }
    
    int a;
    int b;
    for(a=0; a<elementNum; a++){
        char *randkey = (char*)malloc(sizeof(char) *4);
        for(b=0; b<3; b++)
            randkey[b]=rand()%26 + 65;
        randkey[3] = '\0';
        elementList[a].key=randkey;
    }
    
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    if(s=='m'){
        mutex=(pthread_mutex_t*) malloc(sizeof(pthread_mutex_t)*list);
        for(k=0; k<list;k++){
            pthread_mutex_init(&mutex[k], NULL);
        }
    }
    
    if(s=='s'){
        lock=(int*) malloc(sizeof(int)*list);
        for(k=0; k<list; k++){
            lock[k]=0;
        }
    }
    
    int *elementOffset = (int*)malloc(sizeof(int)*threadNum);
    int h;
    for(h=0; h < threadNum; h++){
        elementOffset[h] = iterNum*h;
        if(pthread_create(&pid[h], NULL, thread_func, &elementOffset[h])){
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
    
    free(elementList);
    free(pid);
    
    for(k=0; k<list; k++){
        if(SortedList_length(&head[k])!=0){
            fprintf(stderr, "Corrupted list. \n");
            exit(1);
        }
    }
    
    long long lock_op = 3*iterNum*threadNum;
    int average_waitforlock = mutex_wait_time/lock_op;
    
    printf("list-");
    bool yield=false;
    if(opt_yield & INSERT_YIELD){
        yield=true;
        printf("i");
    }
    if(opt_yield & DELETE_YIELD){
        yield=true;
        printf("d");
    }
    if(opt_yield & LOOKUP_YIELD){
        yield=true;
        printf("l");
    }
    if(!yield)
        printf("none");
    
    if(sync){
        if (s=='s')
            printf("-s");
        if (s=='m')
            printf("-m");
    }
    else
        printf("-none");
    
    long long total_time = (end_time.tv_sec - start_time.tv_sec)*1000000000;
    total_time += end_time.tv_nsec;
    total_time -= start_time.tv_nsec;
    
    long long operationNum = threadNum*iterNum*3;
    int average_op_time = total_time/operationNum;
    
    if(sync && s=='m')
        printf(",%d,%d,%d,%lld,%lld,%d,%d\n",threadNum, iterNum, list, operationNum, total_time, average_op_time, average_waitforlock);
    else
        printf(",%d,%d,%d,%lld,%lld,%d\n",threadNum, iterNum, list, operationNum, total_time, average_op_time);
    exit(0);
    return 0;
}


