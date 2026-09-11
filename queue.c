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
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

bool enque(QUEUE *queue , int data){
    if(queue->front == -1){
        queue->front++;
        queue->data[queue->front] = data;
        queue->rear = queue->front;
        return true;
    }
    
    for(size_t i=queue->rear ; i>=0 ; i--){
        if(queue->rear < MAX_SIZE){
            queue->data[i+1] = queue->data[i];
            queue->rear++;
        }
        else{
            printf("QUEUE is full.\n");
            return false;
        }
    }

    queue->data[queue->front] = data;
    return true;

}

int main(){
    QUEUE *queue;
    
    queue = init_queue();

    enque(queue , 4);
    enque(queue , 3);
    enque(queue , 5);
    enque(queue , 12);

    for(int i=0 ; i<=queue->rear ; i++){
        printf("data = %d\n",queue->data[i]);
    }

    return 0;
}