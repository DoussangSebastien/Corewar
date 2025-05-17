/*
** EPITECH PROJECT, 2024
** day07
** File description:
** my_strlen
*/

int my_strlen(char const *str)
{
    int res = 0;

    if (!str)
        return -1;
    for (; str[res]; res++);
    return res;
}
