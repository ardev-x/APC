/*
Author : Aromal K
Date   : 16/06/2026

Project:
    Arbitrary Precision Calculator (APC)

Description:
    APC is an Arbitrary Precision Calculator implemented in C
    to perform arithmetic operations on integers of any length
    using a doubly linked list.
*/

#include <stdio.h>
#include <string.h>
#include "apc.h"

/* Display the user guide */
static void printGuide(void);

/* Display argument validation errors */
static void printArgsError(ArgumentStatus status, char *argv[]);

int main(int argc, char *argv[])
{
    /* Display the help menu */
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printGuide();
        return SUCCESS;
    }

    /* Validate the command-line arguments */
    ArgumentStatus res = validate_args(argc, argv);
    if (res != VALID_ARGS)
    {
        printArgsError(res, argv);
        return FAILURE;
    }

    /* Initialize the input and result numbers */
    Number num1   = {NULL, NULL, 0};
    Number num2   = {NULL, NULL, 0};
    Number result = {NULL, NULL, 0};

    /* Determine the required operation */
    OperationType operation = determineOperation(argv);

    /* Convert the input strings into linked lists */
    create_list_from_string(&num1, argv[1]);
    create_list_from_string(&num2, argv[3]);

    /* Determine the sign of the result */
    ResultSign sign = determineResultSign(argv, operation, &num1, &num2);

    if (sign == NEGATIVE)
    {
        printf("-");
    }

    /* Perform the requested operation */
    switch (operation)
    {
        case ADDITION:
            add(&num1, &num2, &result);
            break;

        case SUBTRACTION:
            subtract(&num1, &num2, &result);
            break;

        case MULTIPLICATION:
            multiply(&num1, &num2, &result);
            break;

        case DIVISION:
            divide(&num1, &num2, &result);
            break;

        default:
            printf("ERROR: Invalid Operation\n");
            return FAILURE;
    }

    /* Division by zero returns an empty result */
    if (result.head == NULL)
    {
        return FAILURE;
    }

    /* Remove leading zeros and display the result */
    removeLeadingZeros(&result);
    printList(&result);

    //Free the list
    deleteList(&num1);
    deleteList(&num2);
    deleteList(&result);

    return SUCCESS;
}

static void printGuide(void)
{
    printf("\n=========== ARBITRARY PRECISION CALCULATOR (APC) ===========\n");
    printf("Usage: ./a.out <num1> <operator> <num2>\n\n");

    printf("Supported Operations:\n");
    printf("  +  Addition\n");
    printf("  -  Subtraction\n");
    printf("  x  Multiplication (use lowercase 'x')\n");
    printf("  /  Division\n\n");

    printf("Note: Only integer operands are supported.\n\n");

    printf("Example:\n");
    printf("  ./a.out 1234 x 5678\n\n");
}

static void printArgsError(ArgumentStatus status, char *argv[])
{
    switch (status)
    {
        case ARGS_COUNT_ERROR:
            printf("ERROR: Invalid number of arguments. Type './a.out --help' for usage.\n");
            break;

        case OPERATOR_INVALID:
            printf("ERROR: '%s' is not a valid operator.\n", argv[2]);
            break;

        case LEFT_OPERAND_INVALID:
            printf("ERROR: Invalid left operand '%s'.\n", argv[1]);
            break;

        case RIGHT_OPERAND_INVALID:
            printf("ERROR: Invalid right operand '%s'.\n", argv[3]);
            break;

        default:
            break;
    }
}