/*
Author : Aromal K
Date   : 16/06/2026
About Project:  APC is an Arbitrary Precision Calculator implemented in C, 
                designed to perform arithmetic operations on large integers 
                with precision beyond native data type constraints.
*/

#include<stdio.h>
#include<string.h>
#include "apc.h"

static void printGuide();
static void printArgsError(ArgumentStatus status, char *argv[]);

int main(int argc, char* argv[])
{
    /* Display the guide */
    if(argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printGuide();
        return SUCCESS;
    }

    //Check if the argument is valid or not
    ArgumentStatus result = validate_args(argc, argv);
    if(result != VALID_ARGS){
        printArgsError(result, argv);
        return 0;
    }

    Number num1   = {NULL, NULL, 0};
    Number num2   = {NULL, NULL, 0};
    Number result = {NULL, NULL, 0};

    /* Find operation to perform */
    OperationType operation = determineOperation(argv);

    return SUCCESS;
}


static void printGuide()
{
     printf("\n=========== ARBITRARY PRECISION CALCULATOR (APC) ===========\n");
     printf("=> Usage: ./a.out <num1> <opr> <num2>\n");
     printf("=> IMP: Only Integers allowed\n");
     printf("=> Supported Operations Below:\n");
     printf("- Addition       : +\n"
            "- Subtraction    : -\n"
            "- Multiplication : x (Use lower case 'x' character instead of *)\n"
            "- Division       : /\n"
            );
    printf("Example: ./a.out 1234 x 5678\n\n");
    return;
}




static void printArgsError(ArgumentStatus status, char *argv[])
{
    switch(status){
        case ARGS_COUNT_ERROR:      printf("ERROR: Invalid Number of Arguments. Type ./a.out --help for full guide\n"); break;
        case OPERATOR_INVALID:      printf("INVALID OPERATOR : '%s' is not recognized as a valid operator\n", argv[2]); break;
        case LEFT_OPERAND_INVALID:  printf("INVALID OPERAND: Expected a valid integer got '%s'\n", argv[1]);                 break;
        case RIGHT_OPERAND_INVALID: printf("INVALID OPERAND: Expected a valid integer got '%s'\n", argv[3]);                 break;
    }

    return;
}

