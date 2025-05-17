/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** add.c
*/

#include "corewar.h"
#include "op.h"

int add(process_t *process, corewar_t *corewar)
{
    int r1 = 0;
    int r2 = 0;
    int r3 = 0;

    if (!process || !corewar)
        return FAILURE;
    process->carry = !process->carry;
    r1 = (int) corewar->arena[(process->pc + 1 + T_REG) % MEM_SIZE] - 1;
    r2 = (int) corewar->arena[(process->pc + 1 + T_REG * 2) % MEM_SIZE] - 1;
    if (r1 >= 0 && r1 < REG_NUMBER && r2 >= 0 && r2 < REG_NUMBER) {
        r1 = process->regs[r1];
        r2 = process->regs[r2];
        r3 = (int) corewar->arena[(process->pc + 1 + T_REG * 3) %
            MEM_SIZE] - 1;
        if (r3 >= 0 && r3 < REG_NUMBER)
            process->regs[r3] = r1 + r2;
    }
    process->pc += 5;
    process->pc %= MEM_SIZE;
    return SUCCESS;
}
