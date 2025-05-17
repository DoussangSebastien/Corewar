/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** or
*/

#include "corewar.h"
#include "op.h"
#include <stdbool.h>

static int get_or_value(int param, int i, process_t *process,
    corewar_t *corewar)
{
    int reg = 0;

    if (param == T_REG) {
        reg = (int) corewar->arena[i] - 1;
        return reg >= 0 && reg < REG_NUMBER ? process->regs[reg] : 0;
    } else
        return get_value(param == T_DIR, i, process->pc, corewar->arena);
}

static void get_or_params(int *params, int *temp_pc, process_t *process,
    corewar_t *corewar)
{
    unsigned char coding_byte = 0;
    int params_type[2] = {0, 0};

    coding_byte = corewar->arena[(process->pc + 1) % MEM_SIZE];
    for (int i = 0; i < 2; i++) {
        params_type[i] = (coding_byte >> (6 - 2 * i)) & 0b11;
        params[i] = get_or_value(params_type[i], *temp_pc, process, corewar);
        if (params_type[i] == T_REG)
            *temp_pc = (*temp_pc + 1) % MEM_SIZE;
        if (params_type[i] == T_IND)
            *temp_pc = (*temp_pc + IND_SIZE) % MEM_SIZE;
        if (params_type[i] == T_DIR)
            *temp_pc = (*temp_pc + DIR_SIZE) % MEM_SIZE;
    }
}

int or_command(process_t *process, corewar_t *corewar)
{
    int params[2] = {0, 0};
    int temp_pc = 0;
    int reg = 0;

    if (!process || !corewar)
        return FAILURE;
    temp_pc = (process->pc + 2) % MEM_SIZE;
    get_or_params(params, &temp_pc, process, corewar);
    reg = corewar->arena[temp_pc] - 1;
    if (reg >= 0 && reg < REG_NUMBER)
        process->regs[reg] = params[0] | params[1];
    process->carry = !process->carry;
    process->pc = temp_pc + 1;
    process->pc %= MEM_SIZE;
    return SUCCESS;
}
