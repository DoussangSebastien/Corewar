/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** lfork.c
*/

#include "corewar.h"
#include "op.h"
#include "opcode.h"
#include <stddef.h>

int lfork(process_t *process, corewar_t *corewar)
{
    process_t *new_process = NULL;
    short param = 0;

    if (!process || !corewar)
        return FAILURE;
    param = (short)((corewar->arena[(process->pc + 1) % MEM_SIZE] << 8) |
        corewar->arena[(process->pc + 2) % MEM_SIZE]);
    new_process = dup_process(process, param);
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
