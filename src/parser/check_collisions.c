/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** check_collisions
*/

#include "corewar.h"
#include "op.h"
#include <stdbool.h>
#include <stddef.h>

static int set_champ_if_a_set(int i, dyna_process_t *process_set,
    dyna_process_t *process)
{
    if (process->process[i]->pc != -1)
        return add_elt_to_process_array(process_set, process->process[i]);
    return SUCCESS;
}

static bool check_collision(int x1, int x2, int size1, int size2)
{
    if (x1 < x2 + size2 && x2 < x1 + size1)
        return true;
    return false;
}

static int check_set_collision(int i, process_t *p1,
    dyna_process_t *process_set)
{
    process_t *p2 = NULL;

    for (int j = i + 1; j < process_set->len; j++) {
        p2 = process_set->process[j];
        if (check_collision(p1->pc, p2->pc,
            p1->size, p2->size))
            return FAILURE;
        if (check_collision((p1->pc + p1->size) % MEM_SIZE - p1->
            size, (p2->pc + p2->size) % MEM_SIZE - p2->size,
            p1->size, p2->size))
            return FAILURE;
    }
    return SUCCESS;
}

static int check_set_collisions(dyna_process_t *process_set)
{
    for (int i = 0; i < process_set->len - 1; i++)
        if (check_set_collision(i, process_set->process[i], process_set))
            return FAILURE;
    return SUCCESS;
}

int check_collisions(corewar_t *corewar)
{
    dyna_process_t *process_set = NULL;

    if (!corewar)
        return FAILURE;
    process_set = init_process_array();
    if (!process_set)
        return FAILURE;
    for (int i = 0; i < corewar->champs->len; i++)
        if (set_champ_if_a_set(i, process_set, corewar->process)) {
            free_process_array(process_set, false);
            return FAILURE;
        }
    if (check_set_collisions(process_set)) {
        free_process_array(process_set, false);
        return FAILURE;
    }
    free_process_array(process_set, false);
    return SUCCESS;
}
