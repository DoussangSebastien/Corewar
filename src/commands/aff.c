/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** aff
*/

#include "corewar.h"
#include "op.h"
#include <unistd.h>

int aff(process_t *process, corewar_t *corewar)
{
    if (!process || !corewar)
        return FAILURE;
    write(1, &corewar->arena[(process->pc + 2) % IDX_MOD], 1);
    process->pc += 3;
    process->pc %= MEM_SIZE;
    return SUCCESS;
}
