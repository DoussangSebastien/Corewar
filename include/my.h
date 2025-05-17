/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** My Lib Header File
*/

#ifndef MY_H_
    #define MY_H_

unsigned hex_to_uint(unsigned char *str, int index, int len);
unsigned short hex_to_ushort(unsigned char *str, int index, int len);
int my_atoi(char const *str);
int my_is_digit(char const c);
void my_itoa(int nb, char *buffer);
char *my_revstr(char *str);
int my_str_isnum(char const *str);
int my_strcmp(char const *s1, char const *s2);
char *my_strdup(char const *src);
int my_strlen(char const *str);

#endif /* MY_H_ */
