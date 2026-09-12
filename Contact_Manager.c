#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include<inttypes.h>
#include"Contact_Manager.h"

CONTACT *create(){
    CONTACT *new = malloc(sizeof(CONTACT));
    if(new == NULL){
        printf("allocation failed.\n");
        return NULL;
    }
    new->id = 0;
    new->next = NULL;

    return new;
}

void Add_contact(CONTACT **head , uint32_t id , char *name , char *phone){
    CONTACT *c1 = create();
    if(c1 == NULL){
        printf("Invalid address.\n");
        return;
    }
    c1->id = id;
    strcpy(c1->name , name);
    strcpy(c1->phone , phone);

    if(*head == NULL){
        *head = c1;
        return;
    }
    CONTACT *temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = c1;

}

bool Delete_contact(CONTACT **head , uint32_t id){
    CONTACT *prev = NULL;
    CONTACT *current = *head;
    CONTACT *next = NULL;

    if(current == NULL){
        return 0;
    }

    while(current != NULL){
        if(current == *head && current->id == id){
            prev = current;
            current = prev->next;
            free(prev);
            prev = NULL;
            *head = current;
            return 1;
        }

        else if(current->id == id){
            CONTACT *temp;
            temp = current;
            prev->next = temp->next;
            current = temp->next;
            free(temp);
            temp = NULL;
            return 1;
        }
        else{
            prev = current;
            current = current->next;
        }
    }

    return 0;

}

void Display_all_contact(CONTACT *head){
    if(head == NULL){
        printf("the list is empty.\n");
        return;
    }
    CONTACT *temp1 = head;
    printf("\n================= CONTACT LIST ====================\n");
    printf("\n %s %10s %10s.\n","ID" , "NAME" , "PHONE");
    while(temp1 != NULL){
        printf("%"PRIu32 , temp1->id);
        printf("%10s %10s.\n",temp1->name , temp1->phone);
        temp1 = temp1->next;
    }
}

bool Search_contact(CONTACT *head , const char *name){
    if(head == NULL){
        printf("The contact is empty.\n");
        return 0;
    }

    CONTACT *temp = head;
    while(temp != NULL){
        if(strcmp(temp->name , name) == 0){
            printf("ID = ");
            printf("%" PRIu32 , temp->id);
            printf("\nPhone = %s , Name = %s.\n",temp->phone , temp->name);
            return 1;
        }
        temp = temp->next;
    }
    printf("NO '%s' is in contact.\n",name);
    return 0;
}

int count(CONTACT *head){
    CONTACT *temp = head;
    int count_ = 0;
    while(temp != NULL){
        count_++;
        temp = temp->next;
    }
    
    return count_;
}

bool reverse(CONTACT **head){
    CONTACT *current = *head;
    CONTACT *prev = NULL;
    CONTACT *next = NULL;

    if(*head == NULL){
        printf("contact is empty.\n");
        return 0;
    }

    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;

    return 1;
}

void destroy_list(CONTACT **head){
    CONTACT *current = *head;

    while(current != NULL){
        CONTACT *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;

    printf("LIST DESTROYED");
}

int main(){

    CONTACT *head = NULL;

    Add_contact(&head  , 1 , "Harsh" , "842966");
    Add_contact(&head , 2 , "Pranav" , "935443");
    Add_contact(&head , 3 , "S.P. Pandey" , "735516");
    Add_contact(&head , 4 , "Mummy" , "898257");

    Display_all_contact(head);

    Search_contact(head , "Mummy");

    int total = count(head);

    printf("The total contacts in contact list : %d.\n",total);

    Delete_contact(&head , 3);

    Display_all_contact(head);

    reverse(&head);

    Delete_contact(&head , 1);

    Display_all_contact(head);

    destroy_list(&head);

    return 0;
}