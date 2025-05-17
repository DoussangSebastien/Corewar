/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** hex_to_uint
*/

unsigned hex_to_uint(unsigned char *str, int index, int len)
{
    unsigned res = 0;

    if (!str)
        return -1;
    for (int i = 0; i < 4; i++)
        res = (res << 8) + (str[(index + i) % len] >= 0 ?
        str[(index + i) % len] : str[(index + i) % len] + 256);
    return res;
}
