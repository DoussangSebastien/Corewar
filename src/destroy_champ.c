/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** destroy_champ
*/

#include "corewar.h"
#include <stdlib.h>

void destroy_champ(champ_t *champ)
{
    if (!champ)
        return;
    free(champ);
}
