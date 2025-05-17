/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** get_champ_id
*/

#include "corewar.h"

int get_champ_index(int id, dyna_champ_t *champs)
{
    if (!champs)
        return -1;
    for (int i = 0; i < champs->len; i++)
        if (champs->champs[i]->id == id)
            return i;
    return -1;
}
