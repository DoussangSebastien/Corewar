/*
** EPITECH PROJECT, 2024
** task13 day06
** File description:
** my_str_isnum
*/

int my_str_isnum(char const *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i]; i++)
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
    return 1;
}
