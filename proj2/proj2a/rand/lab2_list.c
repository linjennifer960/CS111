#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>
#include "SortedList.h"

int threadNum = 1;
int iterNum = 1;
int opt_yield=0;
int sync=0;
char s;
int lock=0;
pthread_mutex_t mutex;
int i;
SortedListElement_t head;
SortedListElement_t *elementList;

void* thread_func(void *arg){
    int *ofs = (int*) arg;
    int test;
    int del;
    if(sync){
        for(i=0; i<iterNum; i++){
                switch(s){
                    case 's': //spin lock
                        while (__sync_lock_test_and_set(&lock, 1));
                        SortedList_insert(&head, &elementList[*ofs + i]);
                        __sync_lock_release(&lock);
                        break;
                    case 'm': //mutex
                        pthread_mutex_lock(&mutex);
                        SortedList_insert(&head, &elementList[*ofs + i]);
                        pthread_mutex_unlock(&mutex);
                        break;
                    default:
                        break;
                }
        }
    }
    else{
        int p;
        for(p=0; p<iterNum; p++)
            SortedList_insert(&head, &elementList[*ofs + p]);
    }
    
    if(sync){
        switch(s){
                case 's':
                    while (__sync_lock_test_and_set(&lock, 1));
                    test = SortedList_length(&head);
                    if(test<0){
                        fprintf(stderr, "Corrupted list. \n");
                        exit(1);
                    }
                    __sync_lock_release(&lock);
                    break;
                case 'm':
                    pthread_mutex_lock(&mutex);
                    test = SortedList_length(&head);
                    if(test<0){
                        fprintf(stderr, "Corrupted list. \n");
                        exit(1);
                    }
                    pthread_mutex_unlock(&mutex);
                    break;
                default:
                    break;
        }
    }
    else{
        test=SortedList_length(&head);
        if(test<0){
            fprintf(stderr, "Corruped list. \n");
            exit(1);
        }
    }
    SortedListElement_t *check;
    if(sync){
        int q;
        for(q=0; q<iterNum; q++){
            switch(s){
                    case 's':
                        while (__sync_lock_test_and_set(&lock, 1));
                        check = SortedList_lookup(&head, elementList[*ofs + q].key);
                        if(check==NULL){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        del=SortedList_delete(check);
                        if(del==1){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        __sync_lock_release(&lock);
                        break;
                    case 'm':
                        pthread_mutex_lock(&mutex);
                        check = SortedList_lookup(&head, elementList[*ofs + q].key);
                        if(check==NULL){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        del=SortedList_delete(check);
                        if(del==1){
                            fprintf(stderr, "Corrupted list. \n");
                            exit(1);
                        }
                        pthread_mutex_unlock(&mutex);
                        break;
                    default:
                        break;
            }
        }
    }
    else{
        int y;
        for(y=0; y<iterNum; y++){
            check=SortedList_lookup(&head, elementList[*ofs + y].key);
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
        {0,0,0,0}
    };
    int val=0;
    while(1){
        int x;
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
            default:
                break;
        }
    }
    
    int elementNum=threadNum*iterNum;
    elementList=(SortedListElement_t*) malloc(sizeof(SortedListElement_t)*elementNum);
    pthread_t *pid=(pthread_t*)malloc(sizeof(pthread_t)*threadNum);
    
    
    head.key=NULL;
    head.prev=&head;
    head.next=&head;
    
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
    
    if(s=='m')
        pthread_mutex_init(&mutex, NULL);
    
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
    
    free(pid);
    
    if(SortedList_length(&head)!=0){
        fprintf(stderr, "Corrupted list. \n");
        exit(1);
    }
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
        if(s=='m')
            printf("-m");
    }
    else
        printf("-none");
    
    long long total_time = (end_time.tv_sec - start_time.tv_sec)*1000000000;
    total_time += end_time.tv_nsec;
    total_time -= start_time.tv_nsec;
    
    long long operationNum = threadNum*iterNum*3;
    int average_op_time = total_time/operationNum;
    
    printf(",%d,%d,1,%lld,%lld,%d\n",threadNum, iterNum, operationNum, total_time, average_op_time);
    exit(0);
    return 0;
}


