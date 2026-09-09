#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include<stdint.h>
#include<stdbool.h>
#define MAX 100

typedef struct CONTACT{
    uint32_t id;
    char name[30];
    char phone[20];
    struct CONTACT *next;
}CONTACT;

typedef struct Contact_list{
    CONTACT table[MAX];
    uint32_t count;
}Contact_list;

CONTACT *create();

void Add_contact(CONTACT **head , uint32_t id , char *name , char *phone);

bool Delete_contact(CONTACT **head , uint32_t id);

bool Search_contact(CONTACT *head , const char *name);

int count(CONTACT *head);

void Display_all_contact(CONTACT *head);

bool reverse(CONTACT **head);

void destroy_list(CONTACT **head);

#endif