/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** my_int_to_str
*/

#include "my.h"

void my_itoa(int nb, char *buffer)
{
    int i = 0;
    int is_neg = 0;

    if (!buffer)
        return;
    if (nb < 0) {
        nb *= -1;
        is_neg = 1;
    }
    do {
        buffer[i] = (nb % 10) + '0';
        nb /= 10;
        i += 1;
    } while (nb > 0);
    if (is_neg == 1)
        buffer[i] = '-';
    my_revstr(buffer);
}
