/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** multiple_free_areas
*/

#include "corewar.h"
#include "parser.h"
#include <limits.h>
#include <stdio.h>

static int add_unset_champ(int i, dyna_process_t *unset_champs,
    corewar_t *corewar)
{
    if (corewar->process->process[i]->pc == -1)
        if (add_elt_to_process_array(unset_champs,
            corewar->process->process[i]))
            return FAILURE;
    return SUCCESS;
}

static int set_unset_champs(dyna_process_t *unset_champs, corewar_t *corewar)
{
    for (int i = 0; i < corewar->process->len; i++)
        if (add_unset_champ(i, unset_champs, corewar)) {
            free_process_array(unset_champs, false);
            return FAILURE;
        }
    return SUCCESS;
}

static int next_champ_index(int min_value, corewar_t *corewar)
{
    int min = INT_MAX;
    int min_index = 0;
    int curr_pc = 0;

    for (int i = 1; i < corewar->process->len; i++) {
        curr_pc = corewar->process->process[i]->pc;
        if (curr_pc >= min_value && curr_pc < min) {
            min = curr_pc;
            min_index = i;
        }
    }
    return min_index;
}

static void set_multiple_free_areas(free_area_t free_areas[],
    int nb_free_areas, corewar_t *corewar)
{
    int next_champ = -1;
    process_t *champ = NULL;

    for (int i = 0; i < nb_free_areas; i++) {
        next_champ = next_champ_index(next_champ, corewar);
        if (next_champ == -1)
            break;
        champ = corewar->process->process[next_champ];
        free_areas[i].start = champ->pc + champ->size;
        next_champ = champ->pc + champ->size;
        champ = corewar->process->process[next_champ_index(next_champ,
            corewar)];
        free_areas[i].size = champ->pc - free_areas[i].start;
        if (free_areas[i].size < 0)
            free_areas[i].size += MEM_SIZE;
    }
}

static int sort_areas_champs(free_area_t *free_areas, int nb_free_areas,
    dyna_process_t *unset_champs)
{
    if (sort_free_areas(free_areas, (int[2]) {0, nb_free_areas - 1}) ||
        sort_unset_champs(unset_champs->process,
            (int[2]) {0, unset_champs->len - 1})) {
        free_process_array(unset_champs, false);
        return FAILURE;
    }
    return SUCCESS;
}

static int set_champs_pc_on_free_area(free_area_t free_area)
{
    int total_size = get_total_size(free_area.champs);
    int gap = 0;
    int curr_pc = 0;

    if (total_size < 0)
        return FAILURE;
    if (free_area.champs->len == 0)
        return SUCCESS;
    gap = (free_area.size - total_size) / free_area.champs->len;
    curr_pc = free_area.start + gap / 2;
    for (int i = 0; i < free_area.champs->len; i++) {
        free_area.champs->process[i]->pc = curr_pc % MEM_SIZE;
        curr_pc += free_area.champs->process[i]->size;
        curr_pc += gap;
    }
    return SUCCESS;
}

static int set_free_areas_champs(free_area_t *free_areas, int nb_free_areas,
    dyna_process_t *unset_champs)
{
    for (int i = 0; i < unset_champs->len; i++) {
        if (free_areas[0].size < unset_champs->process[0]->size)
            return FAILURE;
        if (add_elt_to_process_array(free_areas[0].champs,
            unset_champs->process[i]))
            return FAILURE;
        free_areas[0].size -= unset_champs->process[i]->size;
        if (sort_free_areas(free_areas, (int[2]) {0, nb_free_areas - 1}))
            return FAILURE;
    }
    for (int i = 0; i < nb_free_areas; i++)
        if (set_champs_pc_on_free_area(free_areas[i]))
            return FAILURE;
    return SUCCESS;
}

int multiple_free_areas(free_area_t *free_areas, int nb_free_areas,
    corewar_t *corewar)
{
    dyna_process_t *unset_champs = NULL;
    int ret_value = 0;

    if (!free_areas || !corewar)
        return FAILURE;
    unset_champs = init_process_array();
    if (!unset_champs)
        return FAILURE;
    set_multiple_free_areas(free_areas, nb_free_areas, corewar);
    if (sort_areas_champs(free_areas, nb_free_areas, unset_champs))
        return FAILURE;
    if (set_unset_champs(unset_champs, corewar))
        return FAILURE;
    ret_value = set_free_areas_champs(free_areas, nb_free_areas, unset_champs);
    free_free_areas(free_areas, nb_free_areas);
    free_process_array(unset_champs, false);
    return ret_value;
}
