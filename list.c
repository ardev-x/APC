/* This File includes list related operations like insert first, last delete and print list*/

#include<stdio.h>
#include<stdlib.h>
#include "apc.h"

int insertFirst(Number *num, int data)
{
    //Create a new node
    Node *newNode = malloc(sizeof(Node));
    if(newNode == NULL)
    {
        printf("ERROR: Memory allocation failed!\n");
        return FAILURE;
    }

    newNode -> data = data;
    newNode -> prev = NULL;
    newNode -> next = num -> head;

    //If list is empty need to update tail
    if(num -> head == NULL)
    {
        num -> head = newNode;
        num -> tail = newNode;
        //num -> length++;
        return SUCCESS;
    }

    //If list not empty set current node prev as new node
    num -> head -> prev = newNode;
    num -> head = newNode;
    //num -> length++;
    return SUCCESS;
}

int insertLast(Number *num, int data)
{
    //Create a new node
    Node * newNode = malloc(sizeof(Node));
    if(newNode == NULL)
    {
        printf("ERROR: Memory allocation failed!\n");
        return FAILURE;
    }
    newNode -> data = data;
    newNode -> next = NULL;
    newNode -> prev = NULL;
    
    //If no element is present store address in head
    if(num -> head == NULL)
    {
       num -> head = newNode;
       num -> tail = newNode;
       return SUCCESS;
    }
    
    num -> tail -> next = newNode;
    newNode -> prev = num -> tail;
    num -> tail = newNode;
    return SUCCESS;
}

void printList(Number *num)
{
    Node *temp = num -> head;
    if(num -> head == NULL){
        printf("List is Empty\n");
        return;
    }
    while(temp != NULL)
    {
        printf("%d", temp -> data);
        temp = temp -> next;
    }
    printf("\n");
}

int deleteFirst(Number *num)
{
    //Check list is empty or not
    if(num -> head == NULL)
    {
        return FAILURE;
    }
    
    Node *temp;
    
    if(num -> head -> next == NULL)
    {
        temp = num -> head;
        num -> head = NULL;
        num -> tail = NULL;
        free(temp);
        return SUCCESS;
    }
    
    temp = num -> head;
    num -> head = num -> head -> next;
    num -> head -> prev = NULL;
    free(temp);
    return SUCCESS;
}

int deleteList(Number *num)
{
    //Check list is empty or not
    if(num -> head == NULL)
    {
        return FAILURE;
    }
    
    Node *temp;

    while(num -> head != NULL)
    {
        temp = num -> head;
        num -> head = num -> head -> next;
        free(temp);
    }
    num -> tail = NULL;
    
    return SUCCESS;    
}

size_t getNodeCount(Number *num)
{
    if(num -> head == NULL)
    {
        return 0;
    }

    Node *temp = num -> head;
    size_t count = 0;
    while(temp != NULL)
    {
        count++;
        temp = temp -> next;
    }

    return count;
}