#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "SortedList.h"
#include <pthread.h>
#include <string.h>

void SortedList_insert(SortedList_t *list, SortedListElement_t *element){
    SortedList_t *cur = list;
    if(cur==NULL || element ==NULL)
        return;
    while(cur->next!= list){
        if(strcmp(cur->next->key, element->key) <=0)
            break;
        else
            cur = cur->next;
    }
    if(opt_yield & INSERT_YIELD)
        pthread_yield();
    cur->next->prev = element;
    element->next = cur->next;
    element->prev = cur;
    cur->next = element;
}

int SortedList_delete(SortedListElement_t *element){
    if(element==NULL)
        return 1;
    if(element->prev && (element->prev->next != element))
        return 1;
    if(element->next && (element->next->prev != element))
        return 1;
    if(opt_yield & DELETE_YIELD)
        pthread_yield();
    element->next->prev=element->prev;
    element->prev->next=element->next;
    return 0;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key){
    if(list==NULL || key == NULL)
        return NULL;
    SortedListElement_t *cur=list->next;
    while(cur!=list){
        int cmp = strcmp(cur->key, key);
        if(cmp==0)
            return (SortedListElement_t*)cur; //found
        else if(cmp > 0){
            cur=cur->next;
            if(opt_yield & LOOKUP_YIELD)
                pthread_yield();
        }
        else
            return NULL;
    }
    return NULL;
}

int SortedList_length(SortedList_t *list){
    int length=0;
    if(list==NULL)
        return -1;
    SortedListElement_t *cur = list->next;
    while(cur!=list){
        if(cur->next && (cur->next->prev!=cur))
            return -1;
        if(cur->prev && (cur->prev->next !=cur))
            return -1;
        length ++;
        cur = cur->next;
    }
    if(opt_yield & LOOKUP_YIELD)
      pthread_yield();
    return length;
}


