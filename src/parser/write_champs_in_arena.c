/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** write_champs_in_arena
*/

#include "corewar.h"

static void write_champ_in_arena(process_t *champ, unsigned char *arena)
{
    for (int i = 0; i < champ->size; i++)
        arena[(champ->pc + i) % MEM_SIZE] = champ->body[i];
}

int write_champs_in_arena(corewar_t *corewar)
{
    if (!corewar)
        return FAILURE;
    for (int i = 0; i < corewar->process->len; i++)
        write_champ_in_arena(corewar->process->process[i], corewar->arena);
    return SUCCESS;
}
