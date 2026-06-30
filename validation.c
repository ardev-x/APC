/* The file validate user inputs taken from command line */
#include "apc.h"
#include<string.h>
#include<ctype.h>

static int isNumberValid(const char *str);

ArgumentStatus validate_args(int argc, char *argv[])
{
    /* Check argument count is 4 or not */
    if(argc != 4)
    {
        return ARGS_COUNT_ERROR;
    }

    const char *num1 = argv[1];
    const char *operator = argv[2];
    const char *num2 = argv[3];

   //Check if the operator is either '+', '-', 'x', '/'
   if(strlen(operator) > 1)
    {
        return OPERATOR_INVALID;
    }
    else
    {
        switch(*operator)
        {
            case '+':
            case '-':
            case 'x':
            case '/': break;
            default: return OPERATOR_INVALID;  
        }
    }

    /* Check if input number is valid or not */
    if(isNumberValid(num1) == INVALID)
    {
        return LEFT_OPERAND_INVALID;
    }

    if(isNumberValid(num2) == INVALID)
    {
        return RIGHT_OPERAND_INVALID;
    }

    return VALID_ARGS;
}

/* Helper function to check digits or not */
static int isNumberValid(const char *str){

    if(strlen(str) == 1 && !isdigit(str[0])){
        return INVALID;
    }
    /* First character can be '+' '-' or digit No others are allowed*/
    if(str[0] != '+' && str[0] != '-' && !isdigit(str[0])){
        return INVALID;
    }

    for(int i = 1; str[i] != '\0'; i++){
        if(!isdigit(str[i])){
            return INVALID;
        }
    }
    return VALID;
}