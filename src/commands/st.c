/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** st.c
*/

#include "corewar.h"
#include "my.h"
#include "op.h"

static void write_int_to_arena(unsigned char *arena, int address, int value)
{
    for (int i = 0; i < REG_SIZE; i++)
        arena[(address + i) % MEM_SIZE] = (value >> (8 * (REG_SIZE - 1 - i)));
}

static void get_st_args(unsigned char *first_arg, unsigned short *second_arg,
    process_t *process, corewar_t *corewar)
{
    unsigned char coding_byte = '\0';

    coding_byte = corewar->arena[(process->pc + 1) % MEM_SIZE];
    *first_arg = corewar->arena[(process->pc + 2) % MEM_SIZE];
    if (*first_arg >= REG_NUMBER)
        return;
    if (((coding_byte >> 4) & 0b11) == 0b11) {
        *second_arg = hex_to_ushort(corewar->arena, (process->pc + 3) %
            MEM_SIZE, MEM_SIZE);
        write_int_to_arena(corewar->arena, process->pc + *second_arg % IDX_MOD,
            *first_arg);
    } else {
        *second_arg = (process->pc + 2 + T_REG) % MEM_SIZE;
        if (*second_arg < REG_NUMBER)
            process->regs[*second_arg] = process->regs[*first_arg];
    }
}

int store(process_t *process, corewar_t *corewar)
{
    unsigned char coding_byte = '\0';
    unsigned char first_arg = '\0';
    unsigned short second_arg = '\0';

    if (!process || !corewar)
        return FAILURE;
    coding_byte = corewar->arena[(process->pc + 1) % MEM_SIZE];
    get_st_args(&first_arg, &second_arg, process, corewar);
    process->pc += 5 + (coding_byte >> 6 == T_DIR) * 2;
    process->pc %= MEM_SIZE;
    return SUCCESS;
}
