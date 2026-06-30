#ifndef APC_H
#define APC_H
#include <stddef.h>

#define VALID 1
#define INVALID -1
#define SUCCESS 0
#define FAILURE -2

typedef struct Node{
    int data;
    struct  Node *next;
    struct  Node *prev;
}Node;

typedef struct Number{
    Node *head;
    Node *tail;
    size_t length;
}Number;

typedef enum{
    VALID_ARGS,
    ARGS_COUNT_ERROR,
    OPERATOR_INVALID,
    LEFT_OPERAND_INVALID,
    RIGHT_OPERAND_INVALID,
}ArgumentStatus;

typedef enum{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
}OperationType;

/* Funtion Prototype for List Operations */
int insertFirst(Number *num, int data);
int insertLast(Number *num, int data);
int deleteFirst(Number *num);
int deleteList(Number *num);
void printList(Number *num);
size_t getNodeCount(Number *num);

//Check for Argument is valid or invalid
ArgumentStatus validate_args(const int argc, const char *argv[]);
OperationType determineOperation(const char *argv[]);

#endif