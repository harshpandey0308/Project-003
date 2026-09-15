#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"queue.h"

QUEUE *init_queue(){
    QUEUE *queue = malloc(sizeof(QUEUE));
    if(queue == NULL){
        perror("Allocation failed.\n");
        exit(-1);
    }
    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

bool enque(QUEUE *queue , int data){
    if(queue->size == MAX_SIZE){
        printf("Queue is full.\n");
        return false;
    }

    queue->data[queue->front] = data;
    queue->front = (queue->front + 1)%MAX_SIZE;
    queue->size++;
    return true;

}

bool deque(QUEUE *queue){
    if(queue->size == 0){
    perror("queue is empty");
    return false;
    }

    queue->rear = (queue->rear + 1)%MAX_SIZE;

    --queue->size;

    return true;
}

void print(QUEUE *queue){
    if(queue->size == 0){
        printf("Queue is empty.\n");
        return;
    }

    size_t index = queue->rear;

    for(size_t i=0 ; i<queue->size ; i++){
       printf("data = %d.\n",queue->data[index]);
       index = (index+1)%MAX_SIZE;
    }
}

int main(){
    QUEUE *queue;
    
    queue = init_queue();

    enque(queue , 4);
    enque(queue , 3);
    enque(queue , 5);
    enque(queue , 12);

    deque(queue);
    deque(queue);

    enque(queue , 23);
    enque(queue , 34);
    enque(queue , 50);

    print(queue);

    return 0;
}