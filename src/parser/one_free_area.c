/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** one_free_area
*/

#include "corewar.h"

int one_free_area(int total_size, corewar_t *corewar)
{
    int gap = 0;
    int curr_pc = 0;

    if (!corewar)
        return FAILURE;
    gap = (MEM_SIZE - total_size) / corewar->champs->len;
    curr_pc = gap / 2;
    for (int i = 0; i < corewar->process->len; i++) {
        corewar->process->process[i]->pc = curr_pc;
        curr_pc += corewar->process->process[i]->size;
        curr_pc += gap;
    }
    return SUCCESS;
}
