#ifndef APC_H
#define APC_H

typedef struct Node{
    int data;
    struct  Node *next;
    struct  Node *prev;
}Node;

typedef struct Number{
    Node *head;
    Node *tail;
    size_t length
}Number;

typedef enum{
    VALID_ARGS,
    ARGS_COUNT_ERROR,
    OPERATOR_INVALID,
    LEFT_OPERAND_INVALID,
    RIGHT_OPERAND_INVALID,
}ArgumentStatus;

/* Funtion Prototype for List Operations */
int insertFirst(Number *num, int data);
int insertLast(Number *num, int data);
int deleteFirst(Number *num);
int deleteList(Number *num);
void printList(Number *num);

#endif