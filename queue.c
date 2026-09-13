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
    if(queue->front == MAX_SIZE){
        queue->front = (queue->front + 1)%MAX_SIZE;
        if(queue->front == queue->rear){
            fprintf(stderr , "the queue is full.\n");
            return false;
        }
        queue->data[queue->front] = data;
        return true;
    }

    queue->data[queue->front++] = data;
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

    int i=queue->rear;
    while(i <= queue->front || i < MAX_SIZE){
        printf("data = %d\n",queue->data[i]);
        if(i == MAX_SIZE){
            i = (i+1)%MAX_SIZE;
        }
        else{
            i++;
        }
    }

    deque(queue);
    deque(queue);

    int k = queue->rear;

    while(k <= queue->front || k < MAX_SIZE){
        printf("data = %d\n",queue->data[k]);
        if(k == MAX_SIZE){
            k = (k+1)%MAX_SIZE;
        }
        else{
            k++;
        }
    }

    printf("Queue after dequeing.\n");

    enque(queue , 23);
    enque(queue , 34);
    enque(queue , 50);

    int j = queue->rear;

    while(j <= queue->front || j < MAX_SIZE){
        printf("data = %d\n",queue->data[j]);
        if(j == MAX_SIZE){
            j = (j+1)%MAX_SIZE;
        }
        else{
            j++;
        }
    }
    

    return 0;
}