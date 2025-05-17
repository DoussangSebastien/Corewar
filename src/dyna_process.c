/*
** EPITECH PROJECT, 2025
** src
** File description:
** dyna_process.c
*/

#include "corewar.h"
#include <stddef.h>
#include <stdlib.h>

static void free_p_array(process_t **process, int len)
{
    for (int i = 0; i < len; i++)
        destroy_process(process[i]);
}

void free_process_array(dyna_process_t *array, bool free_array)
{
    if (!array)
        return;
    if (array->process) {
        if (free_array)
            free_p_array(array->process, array->len);
        free(array->process);
    }
    free(array);
}

static int realloc_dyna_process(dyna_process_t *array)
{
    process_t **temp = malloc(sizeof(process_t *) * array->size * 2);

    if (!temp)
        return FAILURE;
    for (int i = 0; i < array->len; i++)
        temp[i] = array->process[i];
    free(array->process);
    array->process = temp;
    return SUCCESS;
}

int add_elt_to_process_array(dyna_process_t *array, process_t *element)
{
    if (!array || !element)
        return FAILURE;
    if (array->len == array->size) {
        if (realloc_dyna_process(array))
            return FAILURE;
        array->size *= 2;
    }
    array->process[array->len] = element;
    array->len += 1;
    return SUCCESS;
}

dyna_process_t *init_process_array(void)
{
    dyna_process_t *arr = malloc(sizeof(dyna_process_t));

    if (!arr)
        return NULL;
    arr->process = malloc(sizeof(process_t *) * DEFAULT_DYNA_SIZE);
    if (!(arr->process)) {
        free(arr);
        return NULL;
    }
    arr->size = DEFAULT_DYNA_SIZE;
    arr->len = 0;
    return arr;
}
