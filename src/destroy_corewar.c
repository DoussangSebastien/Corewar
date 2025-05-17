/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** destroy_corewar
*/

#include "corewar.h"
#include <stdbool.h>
#include <stdlib.h>

void destroy_corewar(corewar_t *corewar)
{
    if (!corewar)
        return;
    if (corewar->champs)
        free_champ_array(corewar->champs, true);
    if (corewar->process)
        free_process_array(corewar->process, true);
    if (corewar->arena)
        free(corewar->arena);
    free(corewar);
}
