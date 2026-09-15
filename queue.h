#ifndef QUEUE_H
#define QUEUE_H

#include<stddef.h>
#include<stdbool.h>

#define MAX_SIZE 5

typedef struct QUEUE{
    int data[MAX_SIZE];
    size_t size;
    size_t front;
    size_t rear;
}QUEUE;

QUEUE *init_queue();

bool enque(QUEUE *q , int data);

bool deque(QUEUE *q);

void print(QUEUE *q);

#endif