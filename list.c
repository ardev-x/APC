/* List operations for the doubly linked list */

#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int insertFirst(Number *num, int data)
{
    /* Create a new node */
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("ERROR: Memory allocation failed!\n");
        return FAILURE;
    }

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = num->head;

    /* Update head and tail if the list is empty */
    if (num->head == NULL)
    {
        num->head = newNode;
        num->tail = newNode;
        return SUCCESS;
    }

    /* Link the new node at the beginning */
    num->head->prev = newNode;
    num->head = newNode;

    return SUCCESS;
}

int insertLast(Number *num, int data)
{
    /* Create a new node */
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("ERROR: Memory allocation failed!\n");
        return FAILURE;
    }

    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    /* Update head and tail if the list is empty */
    if (num->head == NULL)
    {
        num->head = newNode;
        num->tail = newNode;
        return SUCCESS;
    }

    /* Link the new node at the end */
    num->tail->next = newNode;
    newNode->prev = num->tail;
    num->tail = newNode;

    return SUCCESS;
}

void printList(Number *num)
{
    Node *temp = num->head;

    if (num->head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    /* Print each node */
    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int deleteFirst(Number *num)
{
    /* Check whether the list is empty */
    if (num->head == NULL)
    {
        return FAILURE;
    }

    Node *temp;

    /* Delete the only node present */
    if (num->head->next == NULL)
    {
        temp = num->head;
        num->head = NULL;
        num->tail = NULL;
        free(temp);
        return SUCCESS;
    }

    /* Delete the first node */
    temp = num->head;
    num->head = num->head->next;
    num->head->prev = NULL;
    free(temp);

    return SUCCESS;
}

int deleteList(Number *num)
{
    /* Check whether the list is empty */
    if (num->head == NULL)
    {
        return FAILURE;
    }

    Node *temp;

    /* Delete all nodes */
    while (num->head != NULL)
    {
        temp = num->head;
        num->head = num->head->next;
        free(temp);
    }

    num->tail = NULL;

    return SUCCESS;
}

size_t getNodeCount(Number *num)
{
    if (num->head == NULL)
    {
        return 0;
    }

    Node *temp = num->head;
    size_t count = 0;

    /* Count the number of nodes */
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}