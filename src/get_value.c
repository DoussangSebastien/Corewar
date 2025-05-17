/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** get_value
*/

#include <stdbool.h>
#include "my.h"
#include "op.h"

int get_value(bool is_dir, int i, int pc, unsigned char *arena)
{
    int value = 0;

    if (!arena)
        return 0;
    if (is_dir)
        return hex_to_uint(arena, i, MEM_SIZE);
    else {
        value = hex_to_ushort(arena, i, MEM_SIZE);
        while (value < 0)
            value += MEM_SIZE;
        return arena[(pc + value) % MEM_SIZE];
    }
}
