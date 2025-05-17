/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** set_champs_pc
*/

#include "corewar.h"
#include "op.h"
#include "parser.h"
#include <limits.h>
#include <stddef.h>

int get_total_size(dyna_process_t *process)
{
    int sum = 0;

    if (!process)
        return -1;
    for (int i = 0; i < process->len; i++)
        sum += process->process[i]->size;
    return sum;
}

static int get_unset_champs_nbr(corewar_t *corewar)
{
    int unset_champs = 0;

    for (int i = 0; i < corewar->process->len; i++)
        if (corewar->process->process[i]->pc == -1)
            unset_champs += 1;
    return unset_champs;
}

void free_free_areas(free_area_t *free_areas, int nb_free_areas)
{
    if (!free_areas)
        return;
    for (int i = 0; i < nb_free_areas && free_areas[i].champs; i++)
        free_process_array(free_areas[i].champs, false);
}

static int divide_by_free_areas(int total_size, corewar_t *corewar)
{
    int nb_free_areas = corewar->champs->len - get_unset_champs_nbr(corewar);
    free_area_t free_areas[nb_free_areas];

    if (nb_free_areas == 0)
        return one_free_area(total_size, corewar);
    for (int i = 0; i < nb_free_areas; i++) {
        free_areas[i].start = -1;
        free_areas[i].size = -1;
        free_areas[i].champs = NULL;
    }
    for (int i = 0; i < nb_free_areas; i++) {
        free_areas[i].champs = init_process_array();
        if (!free_areas[i].champs) {
            free_free_areas(free_areas, nb_free_areas);
            return FAILURE;
        }
    }
    return multiple_free_areas(free_areas, nb_free_areas, corewar);
}

int set_champs_pc(corewar_t *corewar)
{
    int total_size = 0;

    if (!corewar)
        return FAILURE;
    if (check_collisions(corewar))
        return FAILURE;
    total_size = get_total_size(corewar->process);
    if (total_size > MEM_SIZE || total_size < 0)
        return FAILURE;
    return divide_by_free_areas(total_size, corewar);
}
