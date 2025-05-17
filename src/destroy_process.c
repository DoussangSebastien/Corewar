/*
** EPITECH PROJECT, 2025
** src
** File description:
** destroy_process.c
*/

#include "corewar.h"
#include <stdlib.h>

void destroy_process(process_t *process)
{
    if (!process)
        return;
    if (process->body)
        free(process->body);
    free(process);
}
