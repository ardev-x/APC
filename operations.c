/* This file contains numbers related operations */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "apc.h"

/* Compare the magnitude of two numbers */
static MagnitudeComparison compare_magnitude(Number *num1, Number *num2);

/* Determine the arithmetic operation to perform */
OperationType determineOperation(char *argv[])
{
    const char *num1 = argv[1];
    const char *operator = argv[2];
    const char *num2 = argv[3];

    if (strcmp(operator, "x") == 0)
    {
        return MULTIPLICATION;
    }
    else if (strcmp(operator, "/") == 0)
    {
        return DIVISION;
    }
    else
    {
        /* '+' may result in addition or subtraction depending on the signs */
        if (strcmp(operator, "+") == 0)
        {
            if (*num1 == '-')
            {
                if (*num2 == '-')
                {
                    return ADDITION;
                }

                return SUBTRACTION;
            }
            else
            {
                if (*num2 == '+' || isdigit(*num2))
                {
                    return ADDITION;
                }

                return SUBTRACTION;
            }
        }

        /* '-' may result in subtraction or addition depending on the signs */
        else
        {
            if (*num1 == '-')
            {
                if (*num2 == '-')
                {
                    return SUBTRACTION;
                }

                return ADDITION;
            }
            else
            {
                if (*num2 == '+' || isdigit(*num2))
                {
                    return SUBTRACTION;
                }

                return ADDITION;
            }
        }
    }
}

/* Determine the sign of the final result */
ResultSign determineResultSign(char *argv[],
                               OperationType operation,
                               Number *num1,
                               Number *num2)
{
    switch (operation)
    {
        case ADDITION:
        {
            /* Same-sign addition */
            if (*argv[1] == '-')
            {
                return NEGATIVE;
            }

            return POSITIVE;
        }

        case SUBTRACTION:
        {
            /* Compare magnitudes to determine the result sign */
            MagnitudeComparison res = compare_magnitude(num1, num2);

            if (res == FIRST_LARGER)
            {
                if (*argv[1] == '-')
                {
                    return NEGATIVE;
                }

                return POSITIVE;
            }
            else if (res == SECOND_LARGER)
            {
                if (*argv[3] == '-' && *argv[2] == '-')
                {
                    return POSITIVE;
                }
                else if (*argv[3] == '-' || *argv[2] == '-')
                {
                    return NEGATIVE;
                }

                return POSITIVE;
            }

            return ZERO;
        }

        case MULTIPLICATION:
        case DIVISION:
        {
            /* Result is positive if both operands have the same sign */
            if (*argv[1] == '-')
            {
                if (*argv[3] == '-')
                {
                    return POSITIVE;
                }

                return NEGATIVE;
            }

            if (*argv[3] == '+' || isdigit(*argv[3]))
            {
                return POSITIVE;
            }

            return NEGATIVE;
        }

        default:
            return ZERO;
    }
}

/* Compare the magnitude of two numbers */
static MagnitudeComparison compare_magnitude(Number *num1, Number *num2)
{
    /* Compare the number of digits */
    if (num1->length > num2->length)
    {
        return FIRST_LARGER;
    }
    else if (num2->length > num1->length)
    {
        return SECOND_LARGER;
    }

    /* Compare digit by digit */
    Node *temp1 = num1->head;
    Node *temp2 = num2->head;

    while (temp1 != NULL)
    {
        if (temp1->data > temp2->data)
        {
            return FIRST_LARGER;
        }
        else if (temp2->data > temp1->data)
        {
            return SECOND_LARGER;
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return BOTH_EQUAL;
}

/* Remove leading zeros from the result */
void removeLeadingZeros(Number *num)
{
    if (num->head == NULL)
    {
        return;
    }

    /* Keep a single zero if the number becomes zero */
    while (num->head->data == 0 && num->head != num->tail)
    {
        deleteFirst(num);
    }
}

/* Add two numbers */
void add(Number *num1, Number *num2, Number *result)
{
    Node *temp1 = num1->tail;
    Node *temp2 = num2->tail;

    result->head = NULL;
    result->tail = NULL;

    unsigned int carry = 0;

    /* Traverse both numbers from least significant digit */
    while (temp1 != NULL || temp2 != NULL)
    {
        /* Use 0 if a number has no more digits */
        int val1 = (temp1 != NULL) ? temp1->data : 0;
        int val2 = (temp2 != NULL) ? temp2->data : 0;

        int sum = val1 + val2 + carry;

        carry = sum / 10;
        int digit_to_store = sum % 10;

        /* Store the result digit */
        insertFirst(result, digit_to_store);

        /* Move to the previous digit */
        if (temp1 != NULL)
        {
            temp1 = temp1->prev;
        }

        if (temp2 != NULL)
        {
            temp2 = temp2->prev;
        }
    }

    /* Insert the final carry if present */
    if (carry)
    {
        insertFirst(result, carry);
    }
}

/* Subtract two large numbers */
void subtract(Number *num1, Number *num2, Number *result)
{
    MagnitudeComparison res = compare_magnitude(num1, num2);
    Node *temp1, *temp2;

    result->head = NULL;
    result->tail = NULL;

    /* Always subtract the smaller number from the larger number */
    if (res == FIRST_LARGER)
    {
        temp1 = num1->tail;
        temp2 = num2->tail;
    }
    else if (res == SECOND_LARGER)
    {
        temp1 = num2->tail;
        temp2 = num1->tail;
    }
    else
    {
        /* Both numbers are equal */
        insertFirst(result, 0);
        return;
    }

    unsigned int borrow = 0;

    /* Traverse both numbers from least significant digit */
    while (temp1 != NULL || temp2 != NULL)
    {
        int val1 = (temp1 != NULL) ? temp1->data : 0;
        int val2 = (temp2 != NULL) ? temp2->data : 0;

        int diff = val1 - val2 - borrow;
        int digit_to_store;

        /* Borrow from the next digit if required */
        if (diff < 0)
        {
            digit_to_store = diff + 10;
            borrow = 1;
        }
        else
        {
            digit_to_store = diff;
            borrow = 0;
        }

        /* Store the result digit */
        insertFirst(result, digit_to_store);

        /* Move to the previous digit */
        if (temp1 != NULL)
        {
            temp1 = temp1->prev;
        }

        if (temp2 != NULL)
        {
            temp2 = temp2->prev;
        }
    }
}

/* Multiply two large numbers */
void multiply(Number *num1, Number *num2, Number *result)
{
    Node *temp2 = num2->tail;

    /* Temporary numbers used during multiplication */
    Number partial_sum = {NULL, NULL, 0};
    Number temp_sum    = {NULL, NULL, 0};

    size_t add_zero_index = 0;
    unsigned int carry;

    /* Multiply each digit of the second number */
    while (temp2 != NULL)
    {
        Node *temp1 = num1->tail;
        int val2 = temp2->data;
        carry = 0;

        /* Generate one partial product */
        while (temp1 != NULL)
        {
            int res = (temp1->data * val2) + carry;

            carry = res / 10;
            int digit_to_store = res % 10;

            insertFirst(&partial_sum, digit_to_store);

            temp1 = temp1->prev;
        }

        /* Insert the final carry if present */
        if (carry)
        {
            insertFirst(&partial_sum, carry);
        }

        /* Append trailing zeros according to the digit position */
        for (size_t i = 0; i < add_zero_index; i++)
        {
            insertLast(&partial_sum, 0);
        }

        /* Add the partial product to the accumulated result */
        add(&partial_sum, &temp_sum, result);

        /* Clear temporary lists for the next iteration */
        deleteList(&partial_sum);
        deleteList(&temp_sum);

        /* Store the current result for the next addition */
        temp_sum.head = result->head;
        temp_sum.tail = result->tail;

        add_zero_index++;
        temp2 = temp2->prev;
    }
}

/* Divide two large numbers using the long division method */
void divide(Number *num1, Number *num2, Number *result)
{
    /* Handle zero dividend */
    if (num1->head->data == 0)
    {
        insertFirst(result, 0);
        return;
    }

    /* Check for division by zero */
    if (num2->head->data == 0)
    {
        printf("ERROR: Division by zero is not possible.\n");
        return;
    }

    Node *num1_head = num1->head;

    /* Temporary numbers used during division */
    Number dividend    = {NULL, NULL, 0};
    Number divisor     = {num2->head, num2->tail, num2->length};
    Number quotient    = {NULL, NULL, 0};
    Number temp_result = {NULL, NULL, 0};

    /* Bring down one digit at a time */
    while (num1_head != NULL)
    {
        insertLast(&dividend, num1_head->data);
        removeLeadingZeros(&dividend);
        dividend.length = getNodeCount(&dividend);

        /* Check whether the dividend is smaller than the divisor */
        MagnitudeComparison div_cmp = compare_magnitude(&dividend, &divisor);

        if (div_cmp == SECOND_LARGER)
        {
            /* Append 0 if the quotient has already started */
            if (quotient.head != NULL)
            {
                insertLast(&quotient, 0);
            }

            num1_head = num1_head->next;
            continue;
        }

        size_t count = 0;

        /* Repeatedly subtract the divisor from the dividend */
        while (div_cmp == FIRST_LARGER || div_cmp == BOTH_EQUAL)
        {
            subtract(&dividend, &divisor, &temp_result);
            count++;

            /* Update the dividend with the remainder */
            deleteList(&dividend);
            dividend.head = temp_result.head;
            dividend.tail = temp_result.tail;

            removeLeadingZeros(&dividend);

            temp_result.head = NULL;
            temp_result.tail = NULL;

            dividend.length = getNodeCount(&dividend);
            div_cmp = compare_magnitude(&dividend, &divisor);
        }

        /* Store one quotient digit */
        insertLast(&quotient, count);

        num1_head = num1_head->next;
    }

    /* Quotient is zero if no digit was produced */
    if (quotient.head == NULL)
    {
        insertLast(&quotient, 0);
    }

    result->head = quotient.head;
    result->tail = quotient.tail;
}