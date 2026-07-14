#ifndef APC_H
#define APC_H

/* Standard Header Files */
#include <stddef.h>

/* Status Macros */
#define VALID       1
#define INVALID    -1
#define SUCCESS     0
#define FAILURE    -2


/*========== Data Structures ==========*/

/* Node of the doubly linked list */
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

/* Structure to represent a large number */
typedef struct Number
{
    Node *head;
    Node *tail;
    size_t length;
} Number;

/*========== Enumerations ==========*/

/* Argument validation status */
typedef enum
{
    VALID_ARGS,
    ARGS_COUNT_ERROR,
    OPERATOR_INVALID,
    LEFT_OPERAND_INVALID,
    RIGHT_OPERAND_INVALID
} ArgumentStatus;

/* Supported arithmetic operations */
typedef enum
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
} OperationType;

/* Result sign */
typedef enum
{
    POSITIVE,
    NEGATIVE,
    ZERO
} ResultSign;

/* Magnitude comparison result */
typedef enum
{
    FIRST_LARGER = 0,
    SECOND_LARGER,
    BOTH_EQUAL
} MagnitudeComparison;


/*========== List Operations ==========*/

int insertFirst(Number *num, int data);
int insertLast(Number *num, int data);
int deleteFirst(Number *num);
int deleteList(Number *num);
void printList(Number *num);
size_t getNodeCount(Number *num);


/*========== Parser Functions ==========*/

ArgumentStatus validate_args(int argc, char *argv[]);
OperationType determineOperation(char *argv[]);
void create_list_from_string(Number *num, char *argv);


/*========== Utility Functions ==========*/

ResultSign determineResultSign(char *argv[],
                               OperationType operation,
                               Number *num1,
                               Number *num2);
void removeLeadingZeros(Number *num);

/*========== Arithmetic Operations ==========*/

void add(Number *num1, Number *num2, Number *result);
void subtract(Number *num1, Number *num2, Number *result);
void multiply(Number *num1, Number *num2, Number *result);
void divide(Number *num1, Number *num2, Number *result);

#endif