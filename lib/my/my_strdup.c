/*
** EPITECH PROJECT, 2024
** task01 day08
** File description:
** my_strdup
*/

#include "my.h"
#include <stddef.h>
#include <stdlib.h>

char *my_strdup(char const *src)
{
    char *str = NULL;
    int src_len = 0;

    if (!src)
        return NULL;
    src_len = my_strlen(src);
    if (src_len == -1)
        return NULL;
    str = malloc(sizeof(char) * (src_len + 1));
    if (!str)
        return NULL;
    for (int i = 0; i < src_len; i++)
        str[i] = src[i];
    str[src_len] = '\0';
    return str;
}
