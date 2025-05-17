/*
** EPITECH PROJECT, 2025
** DynamicArrayWorkshop
** File description:
** init_array
*/

#include "corewar.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static void free_champs_array(champ_t **champs, int len)
{
    for (int i = 0; i < len; i++)
        destroy_champ(champs[i]);
}

void free_champ_array(dyna_champ_t *array, bool free_array)
{
    if (!array)
        return;
    if (array->champs) {
        if (free_array)
            free_champs_array(array->champs, array->len);
        free(array->champs);
    }
    free(array);
}

int remove_elt_from_champ_array(dyna_champ_t *array, int index)
{
    if (!array || index < 0 || index >= array->len)
        return FAILURE;
    for (; index < array->len - 1; index++)
        array->champs[index] = array->champs[index + 1];
    array->len -= 1;
    return SUCCESS;
}

static int realloc_dyna_champ(dyna_champ_t *array)
{
    champ_t **temp = malloc(sizeof(champ_t *) * array->size * 2);

    if (!temp)
        return FAILURE;
    for (int i = 0; i < array->len; i++)
        temp[i] = array->champs[i];
    free(array->champs);
    array->champs = temp;
    return SUCCESS;
}

int add_elt_to_champ_array(dyna_champ_t *array, champ_t *element)
{
    if (!array || !element)
        return FAILURE;
    if (array->len == array->size) {
        if (realloc_dyna_champ(array))
            return FAILURE;
        array->size *= 2;
    }
    array->champs[array->len] = element;
    array->len += 1;
    return SUCCESS;
}

dyna_champ_t *init_champ_array(void)
{
    dyna_champ_t *arr = malloc(sizeof(dyna_champ_t));

    if (!arr)
        return NULL;
    arr->champs = malloc(sizeof(champ_t *) * DEFAULT_DYNA_SIZE);
    if (!(arr->champs)) {
        free(arr);
        return NULL;
    }
    arr->size = DEFAULT_DYNA_SIZE;
    arr->len = 0;
    return arr;
}
