/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** sti.c
*/

#include "corewar.h"
#include "my.h"
#include "op.h"
#include <stdbool.h>

static void write_int_to_arena(unsigned char *arena, int address, int value)
{
    if (address < 0)
        return;
    for (int i = 0; i < REG_SIZE; i++)
        arena[(address + i) % MEM_SIZE] = (value >> (8 * (REG_SIZE - 1 - i)));
}

static int get_sti_value(int param, int i, process_t *process,
    corewar_t *corewar)
{
    int reg = 0;

    if (param == T_REG) {
        reg = (int) corewar->arena[i] - 1;
        return reg >= 0 && reg < REG_NUMBER ? process->regs[reg] : 0;
    }
    if (param == T_DIR)
        return hex_to_ushort(corewar->arena, i, MEM_SIZE);
    return get_value_mod(false, i, process->pc, corewar->arena);
}

static void get_sti_params(int *params, int *temp_pc, process_t *process,
    corewar_t *corewar)
{
    unsigned char coding_byte = 0;
    int params_type[2] = {0, 0};

    coding_byte = corewar->arena[process->pc + 1];
    for (int i = 1; i < 3; i++)
        params_type[i - 1] = (coding_byte >> (6 - 2 * i)) & 0b11;
    params[0] = get_sti_value(params_type[0], *temp_pc, process, corewar);
    if (params_type[0] == T_REG)
        *temp_pc = (*temp_pc + 1) % MEM_SIZE;
    else
        *temp_pc = (*temp_pc + IND_SIZE) % MEM_SIZE;
    if (params_type[1] == T_REG) {
        params[1] = corewar->arena[*temp_pc] - 1;
        if (params[1] >= 0 && params[1] < REG_NUMBER)
            params[1] = process->regs[params[1]];
        *temp_pc = (*temp_pc + 1) % MEM_SIZE;
    } else {
        params[1] = hex_to_ushort(corewar->arena, *temp_pc, MEM_SIZE);
        *temp_pc = (*temp_pc + IND_SIZE) % MEM_SIZE;
    }
}

int store_i(process_t *process, corewar_t *corewar)
{
    unsigned char coding_byte = '\0';
    int params[2] = {0, 0};
    int temp_pc = 0;
    int reg = 0;

    if (!process || !corewar)
        return FAILURE;
    temp_pc = (process->pc + 3) % MEM_SIZE;
    coding_byte = corewar->arena[(process->pc + 1) % MEM_SIZE];
    reg = corewar->arena[(process->pc + 2) % MEM_SIZE] - 1;
    if (reg >= 0 && reg < REG_NUMBER) {
        get_sti_params(params, &temp_pc, process, corewar);
        write_int_to_arena(corewar->arena, process->pc +
            (params[0] + params[1]) % IDX_MOD, process->regs[reg]);
    }
    process->pc += 5 + (((coding_byte >> 4) & 0b11) == T_DIR) +
        (((coding_byte >> 2) & 0b11) == T_DIR);
    process->pc %= MEM_SIZE;
    return SUCCESS;
}
