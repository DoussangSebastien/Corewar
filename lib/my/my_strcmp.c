/*
** EPITECH PROJECT, 2024
** task06 day06
** File description:
** my_strcmp
*/

int my_strcmp(char const *s1, char const *s2)
{
    if (!s1 || !s2)
        return 0;
    for (int i = 0;; i++) {
        if (!s1[i] && !s2[i])
            return 0;
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    }
}
