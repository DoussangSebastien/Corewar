/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** sort_free_areas
*/

#include "parser.h"

static void swap_free_areas(free_area_t *free_areas, int i, int j)
{
    free_area_t free_area = free_areas[i];

    free_areas[i] = free_areas[j];
    free_areas[j] = free_area;
}

static int partition_free_areas(free_area_t *free_areas, int lr[])
{
    int pivot = free_areas[lr[0]].size;
    int i = lr[0];
    int j = lr[1];

    while (i < j) {
        while (free_areas[i].size >= pivot && i < lr[1])
            i += 1;
        while (free_areas[j].size < pivot && j > lr[0])
            j -= 1;
        if (i < j)
            swap_free_areas(free_areas, i, j);
    }
    swap_free_areas(free_areas, lr[0], j);
    return j;
}

int sort_free_areas(free_area_t *free_areas, int lr[])
{
    int pivot = 0;

    if (!free_areas)
        return FAILURE;
    if (lr[0] < lr[1]) {
        pivot = partition_free_areas(free_areas, lr);
        if (sort_free_areas(free_areas, (int[]) {lr[0], pivot - 1}))
            return FAILURE;
        if (sort_free_areas(free_areas, (int[]) {pivot + 1, lr[1]}))
            return FAILURE;
    }
    return SUCCESS;
}
