/* Convert the command-line argument into a linked list */

#include <string.h>
#include "apc.h"

void create_list_from_string(Number *num, char *argv)
{
    size_t len = strlen(argv);
    unsigned int hit_non_zero = 0;    /* Flag to detect first non-zero digit */
    int start = 0;

    /* Skip the sign if present */
    if (argv[0] == '+' || argv[0] == '-')
    {
        start = 1;
    }

    /* Convert each digit into a node */
    for (size_t i = start; i < len; i++)
    {
        int digit = argv[i] - '0';

        /* Ignore leading zeros */
        if (digit == 0 && !hit_non_zero)
        {
            continue;
        }

        if (insertLast(num, digit) == SUCCESS)
        {
            num->length++;
        }

        hit_non_zero = 1;
    }

    /* Store a single zero if the number is zero */
    if (!hit_non_zero)
    {
        insertLast(num, 0);
        num->length++;
    }
}