/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** sort_champs_by_id
*/

#include "corewar.h"

static void swap_champs(process_t **champs, int i, int j)
{
    process_t *unset_champ = champs[i];

    champs[i] = champs[j];
    champs[j] = unset_champ;
}

static int partition_champs(process_t **champs, int lr[])
{
    int pivot = champs[lr[0]]->id;
    int i = lr[0];
    int j = lr[1];

    while (i < j) {
        while (champs[i]->id < pivot && i < lr[1])
            i += 1;
        while (champs[j]->id >= pivot && j > lr[0])
            j -= 1;
        if (i < j)
            swap_champs(champs, i, j);
    }
    swap_champs(champs, lr[0], j);
    return j;
}

int sort_champs_by_id(process_t **champs, int lr[])
{
    int pivot = 0;

    if (!champs)
        return FAILURE;
    if (lr[0] < lr[1]) {
        pivot = partition_champs(champs, lr);
        if (sort_champs_by_id(champs, (int[]) {lr[0], pivot - 1}))
            return FAILURE;
        if (sort_champs_by_id(champs, (int[]) {pivot + 1, lr[1]}))
            return FAILURE;
    }
    return SUCCESS;
}
