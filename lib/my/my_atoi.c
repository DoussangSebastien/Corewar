/*
** EPITECH PROJECT, 2024
** LIBMY
** File description:
** my_atoi
*/

#include "my.h"
#include <stdbool.h>
#include <stddef.h>

int my_atoi(char const *str)
{
    int res = 0;
    bool is_neg = false;
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 0;
    if (str[0] == '-') {
        is_neg = true;
        i = 1;
    }
    for (; my_is_digit(str[i]); i++)
        res = res * 10 + (int) str[i] - 48;
    if (is_neg)
        res *= -1;
    return res;
}
