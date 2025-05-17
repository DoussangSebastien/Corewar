/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** ldi
*/

#include "corewar.h"
#include "my.h"
#include "op.h"
#include <stdbool.h>

static int get_lldi_value(int param, int i, process_t *process,
    corewar_t *corewar)
{
    int reg = 0;

    if (param == T_REG) {
        reg = (int) corewar->arena[i] - 1;
        return reg >= 0 && reg < REG_NUMBER ? process->regs[reg] : 0;
    } else
        return get_value(param == T_DIR, i, process->pc, corewar->arena);
}

static void get_lldi_params(unsigned short *params, int *temp_pc,
    process_t *process, corewar_t *corewar)
{
    unsigned char coding_byte = 0;
    int params_type[2] = {0, 0};

    coding_byte = corewar->arena[process->pc + 1];
    for (int i = 0; i < 2; i++)
        params_type[i] = (coding_byte >> (6 - 2 * i)) & 0b11;
    params[0] = get_lldi_value(params_type[0], *temp_pc, process, corewar);
    if (params_type[0] == T_REG)
        *temp_pc = (*temp_pc + 1) % MEM_SIZE;
    else
        *temp_pc += IND_SIZE;
    if (params_type[1] == T_REG) {
        params[1] = corewar->arena[*temp_pc];
        if (params[1] < REG_NUMBER)
            params[1] = process->regs[params[1]];
        *temp_pc = (*temp_pc + 1) % MEM_SIZE;
    } else {
        params[1] = hex_to_ushort(corewar->arena, *temp_pc, MEM_SIZE);
        *temp_pc = (*temp_pc + IND_SIZE) % MEM_SIZE;
    }
}

int lldi(process_t *process, corewar_t *corewar)
{
    unsigned short params[2] = {0, 0};
    int s = 0;
    int temp_pc = 0;
    int reg = 0;

    if (!corewar || !process)
        return FAILURE;
    temp_pc = (process->pc + 2) % MEM_SIZE;
    get_lldi_params(params, &temp_pc, process, corewar);
    s = params[0] + params[1];
    reg = corewar->arena[temp_pc] - 1;
    if (reg >= 0 && reg < REG_NUMBER)
        process->regs[reg] = corewar->arena[(process->pc + s) % MEM_SIZE];
    process->pc = temp_pc + 1;
    process->pc %= MEM_SIZE;
    process->carry = !process->carry;
    return SUCCESS;
}
