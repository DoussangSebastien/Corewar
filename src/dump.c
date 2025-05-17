/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** dump
*/

#include "corewar.h"
#include <unistd.h>

static void get_hexa_buff(char buff[2], int i, unsigned char *arena)
{
    unsigned char temp_arena = arena[i];
    unsigned char temp = temp_arena / 16;

    if (temp < 10)
        temp += '0';
    else
        temp += 'a' - 10;
    buff[0] = temp;
    temp = temp_arena % 16;
    if (temp < 10)
        temp += '0';
    else
        temp += 'a' - 10;
    buff[1] = temp;
}

int dump(corewar_t *corewar)
{
    char buff[2] = "\0";

    if (!corewar)
        return FAILURE;
    for (int i = 0; i < MEM_SIZE; i++) {
        get_hexa_buff(buff, i, corewar->arena);
        write(1, buff, 2);
        if ((i + 1) % DUMP_SIZE > 0 || i == 0)
            write(1, " ", 1);
        if (((i + 1) % DUMP_SIZE == 0 && i != 0) || i == MEM_SIZE - 1)
            write(1, "\n", 1);
    }
    return SUCCESS;
}
