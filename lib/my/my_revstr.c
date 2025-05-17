/*
** EPITECH PROJECT, 2024
** task03 day06
** File description:
** my_revstr
*/

#include <stddef.h>

char *my_revstr(char *str)
{
    int len = 0;
    char temp = '\0';

    if (!str)
        return NULL;
    for (int i = 0; str[i]; i++)
        len++;
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}
