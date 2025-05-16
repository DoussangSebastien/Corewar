/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** My Lib Header File
*/

#ifndef MY_H_
    #define MY_H_

/**
 * @brief Converts a hexadecimal string to an unsigned integer.
 * 
 * @param str The hexadecimal string to convert.
 * @param index The starting index in the string.
 * @param len The length of the substring to convert.
 * @return unsigned The converted unsigned integer.
 */
unsigned hex_to_uint(unsigned char *str, int index, int len);

/**
 * @brief Converts a hexadecimal string to an unsigned short.
 * 
 * @param str The hexadecimal string to convert.
 * @param index The starting index in the string.
 * @param len The length of the substring to convert.
 * @return unsigned short The converted unsigned short.
 */
unsigned short hex_to_ushort(unsigned char *str, int index, int len);

/**
 * @brief Converts a string to an integer (similar to atoi).
 * 
 * @param str The string to convert.
 * @return int The converted integer.
 */
int my_atoi(char const *str);

/**
 * @brief Checks if a character is a digit.
 * 
 * @param c The character to check.
 * @return int 1 if the character is a digit, 0 otherwise.
 */
int my_is_digit(char const c);

/**
 * @brief Converts an integer to a string.
 * 
 * @param nb The integer to convert.
 * @param buffer The buffer where the resulting string will be stored.
 */
void my_itoa(int nb, char *buffer);

/**
 * @brief Reverses a string in place.
 * 
 * @param str The string to reverse.
 * @return char* A pointer to the reversed string.
 */
char *my_revstr(char *str);

/**
 * @brief Checks if a string consists only of digits.
 * 
 * @param str The string to check.
 * @return int 1 if the string is numeric, 0 otherwise.
 */
int my_str_isnum(char const *str);

/**
 * @brief Compares two strings.
 * 
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return int 0 if the strings are equal, a negative value if s1 < s2, 
 *         or a positive value if s1 > s2.
 */
int my_strcmp(char const *s1, char const *s2);

/**
 * @brief Duplicates a string (allocates memory).
 * 
 * @param src The string to duplicate.
 * @return char* A pointer to the newly allocated string copy.
 */
char *my_strdup(char const *src);

/**
 * @brief Computes the length of a string.
 * 
 * @param str The string to measure.
 * @return int The length of the string.
 */
int my_strlen(char const *str);

#endif /* MY_H_ */
