/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** get_default_corewar
*/

#include "corewar.h"
#include "op.h"
#include <stddef.h>
#include <stdlib.h>

static int set_default_arrays(corewar_t *corewar)
{
    corewar->arena = malloc(sizeof(unsigned char) * MEM_SIZE);
    corewar->champs = init_champ_array();
    corewar->process = init_process_array();
    if (!corewar->arena || !corewar->champs)
        return FAILURE;
    for (size_t i = 0; i < MEM_SIZE; i++)
        corewar->arena[i] = '\0';
    return SUCCESS;
}

corewar_t *get_default_corewar(void)
{
    corewar_t *corewar = malloc(sizeof(corewar_t));

    if (!corewar)
        return NULL;
    corewar->champs = NULL;
    corewar->process = NULL;
    corewar->arena = NULL;
    corewar->cycle = 0;
    corewar->winner = -1;
    corewar->nbr_live = 0;
    corewar->cycle_to_die = CYCLE_TO_DIE;
    corewar->next_to_die = 0;
    corewar->dump = -1;
    if (set_default_arrays(corewar)) {
        destroy_corewar(corewar);
        return NULL;
    }
    return corewar;
}
