/* Validate the command-line arguments */

#include <string.h>
#include <ctype.h>
#include "apc.h"

/* Helper function to validate a number */
static int isNumberValid(const char *str);

ArgumentStatus validate_args(const int argc, char *argv[])
{
    /* Check whether the argument count is valid */
    if (argc != 4)
    {
        return ARGS_COUNT_ERROR;
    }

    const char *num1 = argv[1];
    const char *operator = argv[2];
    const char *num2 = argv[3];

    /* Validate the operator */
    if (strlen(operator) > 1)
    {
        return OPERATOR_INVALID;
    }

    switch (*operator)
    {
        case '+':
        case '-':
        case 'x':
        case '/':
            break;

        default:
            return OPERATOR_INVALID;
    }

    /* Validate the left operand */
    if (isNumberValid(num1) == INVALID)
    {
        return LEFT_OPERAND_INVALID;
    }

    /* Validate the right operand */
    if (isNumberValid(num2) == INVALID)
    {
        return RIGHT_OPERAND_INVALID;
    }

    return VALID_ARGS;
}

/* Check whether the given string is a valid number */
static int isNumberValid(const char *str)
{
    /* Single character should be a digit */
    if (strlen(str) == 1 && !isdigit(str[0]))
    {
        return INVALID;
    }

    /* First character can be '+', '-' or a digit */
    if (str[0] != '+' && str[0] != '-' && !isdigit(str[0]))
    {
        return INVALID;
    }

    /* Remaining characters must be digits */
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return INVALID;
        }
    }

    return VALID;
}