#ifndef REVERSE_LL_H
#define REVERSE_LL_H

typedef struct NODE{
    int data;
    struct NODE *next;
}NODE;

int reverse();

NODE *create_node();

#endif