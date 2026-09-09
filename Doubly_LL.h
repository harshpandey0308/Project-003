#ifndef DOUBLY_LL_H
#define DOUBLY_LL_H

#include<stdbool.h>

typedef struct NODE{
    int data;
    struct NODE *prev;
    struct NODE *next;
}NODE;

NODE *create();

bool insert(NODE **head , int data , int index);

bool delete(NODE **head , int data);

void reverse(NODE *head);

void Display_list(NODE *head);

void clean_memory(NODE **head);


#endif