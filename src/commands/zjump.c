/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** zjump.c
*/

#include "corewar.h"

int zjump(process_t *process, corewar_t *corewar)
{
    short jump = 0;

    if (!process || !corewar)
        return FAILURE;
    jump = (short) ((corewar->arena[(process->pc + 1) % MEM_SIZE] << 8) |
        corewar->arena[(process->pc + 2) % MEM_SIZE]);
    if (process->carry) {
        process->pc = (process->pc + (jump % IDX_MOD)) % MEM_SIZE;
        while (process->pc < 0)
            process->pc += MEM_SIZE;
    } else
        process->pc = (process->pc + 3) % MEM_SIZE;
    return SUCCESS;
}
