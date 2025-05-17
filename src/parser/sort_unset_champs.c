/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** sort_unset_champs
*/

#include "corewar.h"

static void swap_unset_champs(process_t **unset_champs, int i, int j)
{
    process_t *unset_champ = unset_champs[i];

    unset_champs[i] = unset_champs[j];
    unset_champs[j] = unset_champ;
}

static int partition_unset_champs(process_t **unset_champs, int lr[])
{
    int pivot = unset_champs[lr[0]]->size;
    int i = lr[0];
    int j = lr[1];

    while (i < j) {
        while (unset_champs[i]->size >= pivot && i < lr[1])
            i += 1;
        while (unset_champs[j]->size < pivot && j > lr[0])
            j -= 1;
        if (i < j)
            swap_unset_champs(unset_champs, i, j);
    }
    swap_unset_champs(unset_champs, lr[0], j);
    return j;
}

int sort_unset_champs(process_t **unset_champs, int lr[])
{
    int pivot = 0;

    if (!unset_champs)
        return FAILURE;
    if (lr[0] < lr[1]) {
        pivot = partition_unset_champs(unset_champs, lr);
        if (sort_unset_champs(unset_champs, (int[]) {lr[0], pivot - 1}))
            return FAILURE;
        if (sort_unset_champs(unset_champs, (int[]) {pivot + 1, lr[1]}))
            return FAILURE;
    }
    return SUCCESS;
}
