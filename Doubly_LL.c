#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Doubly_LL.h"

NODE *create(){
    NODE *new = malloc(sizeof(NODE));
    if(new == NULL){
        printf("Allocation failed.\n");
        return NULL;
    }
    new->next = NULL;
    new->prev = NULL;

    return new;
}

bool insert(NODE **head , int data , int index){
    NODE *new = create();
    if(new == NULL){
        printf("Node creation failed.\n");
        return false;
    }

    new->data = data;
    
    if(*head == NULL && index == 1){
        *head = new;
        return true;
    }

    else if(index == 1){
        (*head)->prev = new;
        new->next = *head;
        *head = new;
        return true;
    }
    else{
        NODE *temp = *head;
        for(int i=1 ; i<index ; i++){
            temp = temp->next;
            if(temp == NULL){
                printf("index is invalid.\n");
                free(new);
                return false;
            }
        }
        NODE *temp1 = temp->prev;
        temp->prev = new;
        new->next = temp;
        new->prev = temp1;
        temp1->next = new;
        return true;
    }
}

void Display_list(NODE *head){
    NODE *temp = head;
    while(temp != NULL){
        printf("%d.\n",temp->data);
        temp = temp->next;
    }
}

void clean_memory(NODE **head){
    NODE *temp = *head;

    while(temp != NULL){
        NODE *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    printf("Memory cleaned.\n");
}

bool delete(NODE **head , int data){
    
    if(*head == NULL){
        printf("the list is empty , cannot delete.\n");
        return false;
    }

    NODE *temp = *head;
    while(temp != NULL){
        if(temp == *head && temp->data == data){
            if(temp->next == NULL){
                free(temp);
                temp = NULL;
                *head = NULL;
                return true;
            }
            NODE *temp1 = temp->next;
            temp1->prev = temp->prev;
            *head = temp1;
            free(temp);
            temp = NULL;
            return true;
        }
        else if(temp->next != NULL && temp->data == data){

            NODE *temp1 = temp;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp1);
            temp1 = NULL;
            return true;
        }
        else if(temp->next == NULL && temp->data == data){
            NODE *temp1 = temp;
            temp->prev->next = temp->next;
            free(temp1);
            temp1 = NULL;
            return true;
        }
        else{
            temp = temp->next;
        }

    }
    printf("the data is not in the list.\n");

    return false;
}

int main(){
    NODE *head = NULL;

    insert(&head , 8 , 1);
    insert(&head , 9 , 1);
    insert(&head , 10 , 1);
    insert(&head , 34 , 2);
    insert(&head , 23 , 3);
    insert(&head , 12 , 5);

    

    delete(&head , 8);
    
    delete(&head , 23);

    printf("The list is :\n");
    Display_list(head);

    printf("\n Backward traversal: \n");
    NODE *temp = head;

    if(head == NULL){
        return 0;
    }

    while(temp->next != NULL){
        temp = temp->next;
    }

    NODE *temp1 = temp;
    while(temp1 != NULL){
        printf("%d.\n",temp1->data);
        temp1 = temp1->prev;
    }

    clean_memory(&head);

    return 0;

}

