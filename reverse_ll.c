#include<stdio.h>
#include<stdlib.h>
#include"reverse_ll.h"

NODE *head = NULL;


int reverse(){
    NODE *current = head;
    NODE *prev = NULL;
    NODE *next = NULL;

    if(current == NULL){
        return -1;
    }
    else if(current->next == NULL){
        return 0;
    }

    while(current != NULL){
        if(current->next == NULL){
            head = current;
        }
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return 1;
}

NODE *create_node(){
    NODE *new = malloc(sizeof(NODE));
    if(new == NULL){
        printf("allocation failed.\n");
        return NULL;
    }
    new->next = NULL;

    return new;
}

int main(){
    NODE *p1 = create_node();
    if(p1 == NULL){
        exit(EXIT_FAILURE);
    }
    p1->data = 4;
    head = p1;

    NODE *p2 = create_node();
    if(p2 == NULL){
        exit(EXIT_FAILURE);
    }
    p2->data = 5;
    p1->next = p2;

    NODE *temp1 = head;
    while(temp1 != NULL){
        printf("value -> %d.\n",temp1->data);
        temp1 = temp1->next;
    }

    int flag = reverse();

    if(flag == -1){
        printf("the list is empty.\n");
        return 0;
    }
    else if(flag == 0){
        printf("the list contain only one element which cannot be reversed.\n");
        return 0;
    }
    else{
        NODE *temp = head;
        while(temp != NULL){
            printf("value -> %d.\n",temp->data);
            temp = temp->next;
        }
    }

    

    return 0;
}