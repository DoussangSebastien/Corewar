/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** ld
*/

#include "corewar.h"
#include "op.h"
#include <stdbool.h>

int load(process_t *process, corewar_t *corewar)
{
    unsigned char coding_byte = 0;
    bool is_dir = false;
    int reg = 0;

    if (!process || !corewar)
        return FAILURE;
    coding_byte = corewar->arena[(process->pc + 1) % MEM_SIZE];
    is_dir = coding_byte >> 6 == T_DIR;
    reg = corewar->arena[(process->pc + 4 + is_dir * 2) % MEM_SIZE] - 1;
    if (reg >= 0 && reg < REG_NUMBER)
        process->regs[reg] = get_value_mod(is_dir, (process->pc + 2) %
            MEM_SIZE, process->pc, corewar->arena);
    process->pc += 5 + is_dir * 2;
    process->pc %= MEM_SIZE;
    process->carry = !process->carry;
    return SUCCESS;
}
