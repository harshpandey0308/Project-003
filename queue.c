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
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

bool enque(QUEUE *queue , int data){
    if(queue->front == queue->rear){
        queue->front++;
        queue->data[queue->rear] = data;
        return true;
    }

    for(size_t i=queue->front ; i>0 ; i--){
        if(queue->front >= MAX_SIZE){
            printf("the queue is full.\n");
            return false;
        }
        queue->data[i] = queue->data[i-1];
    }
    queue->front++;
    queue->data[queue->rear] = data;
    return true;

}

bool deque(QUEUE *queue){
     if(queue->front == queue->rear){
        perror("queue is empty");
        return false;
     }
     ++(queue->rear);
     return true;
}

int main(){
    QUEUE *queue;
    
    queue = init_queue();

    enque(queue , 4);
    enque(queue , 3);
    enque(queue , 5);
    enque(queue , 12);

    for(int i=queue->rear ; i<queue->front ; i++){
        printf("data = %d\n",queue->data[i]);
    }

    deque(queue);
    deque(queue);

    for(int i=queue->rear ; i<queue->front ; i++){
        printf("data = %d\n",queue->data[i]);
    }

    return 0;
}