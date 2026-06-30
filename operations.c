/* This file contains numbers related operations */
#include<stdio.h>
#include<string.h>
#include "apc.h"

/*This function return which operation to be performed*/
OperationType determineOperation(const char *argv[])
{
    const char *num1 = argv[1];
    const char *operator = argv[2];
    const char *num2 = argv[3];

    if(strcmp(operator, "x") == 0)
    {
        return MULTIPLICATION;
    }
    else if(strcmp(operator, "/") == 0)
    {
        return DIVISION;
    }
    else
    {
       if(strcmp(operator, "+") == 0)
       {
         if(*num1 == '-')
         {
            if(*num2 == '-')
            {
                return ADDITION;
            }
            else
            {
                return SUBTRACTION;
            }
         }
         else
         {
            if(*num2 == '+' || isdigit(*num2))
            {
                return ADDITION;
            }
            else
            {
                return SUBTRACTION;
            }
         }
       }

       else
       {
         if(*num1 == '-')
         {
            if(*num2 == '-')
            {
                return SUBTRACTION;
            }
            else
            {
                return ADDITION;
            }
         }
         else
         {
            if(*num2 == '+' || isdigit(*num2))
            {
                return SUBTRACTION;
            }
            else
            {
                return ADDITION;
            }
         }      
       }
    }
}

