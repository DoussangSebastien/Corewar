/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** fork.c
*/

#include "corewar.h"
#include "my.h"
#include "op.h"
#include <stddef.h>
#include <stdlib.h>

process_t *dup_process(process_t *process, short param)
{
    process_t *new = NULL;

    if (!process)
        return NULL;
    new = malloc(sizeof(process_t));
    if (!new)
        return NULL;
    new->body = my_strdup(process->body);
    if (!new->body)
        return NULL;
    new->carry = process->carry;
    new->id = process->id;
    new->size = process->size;
    for (int reg = 0; reg < REG_NUMBER; reg++)
        new->regs[reg] = process->regs[reg];
    new->pc = process->pc + param;
    new->start = new->pc;
    new->command_cycle = 0;
    return new;
}

int my_fork(process_t *process, corewar_t *corewar)
{
    process_t *new_process = NULL;
    short param = 0;

    if (!process || !corewar)
        return FAILURE;
    param = (short)((corewar->arena[(process->pc + 1) % MEM_SIZE] << 8) |
        corewar->arena[(process->pc + 2) % MEM_SIZE]);
    new_process = dup_process(process, param % IDX_MOD);
    if (!new_process)
        return FAILURE;
    add_elt_to_process_array(corewar->process, new_process);
    if (sort_champs_by_id(corewar->process->process,
        (int[2]) {0, corewar->process->len - 1}))
        return FAILURE;
    process->pc += 3;
    process->pc %= MEM_SIZE;
    return SUCCESS;
}
