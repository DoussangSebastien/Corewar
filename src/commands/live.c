/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** live
*/

#include "corewar.h"
#include "my.h"
#include "op.h"
#include "opcode.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static void set_champ_alive(int prog_number, corewar_t *corewar)
{
    int id = 0;
    char *name = NULL;
    char the_player[] = "The player ";
    char is_alive[] = ") is alive.\n";
    char id_buff[12] = "";

    for (int i = 0; i < corewar->champs->len; i++)
        if (corewar->champs->champs[i]->id == prog_number) {
            corewar->champs->champs[i]->alive = true;
            id = corewar->champs->champs[i]->id;
            corewar->winner = id;
            name = corewar->champs->champs[i]->name;
            write(1, the_player, sizeof(the_player));
            my_itoa(id, id_buff);
            write(1, id_buff, my_strlen(id_buff));
            write(1, "(", 1);
            write(1, name, my_strlen(name));
            write(1, is_alive, sizeof(is_alive));
        }
}

int live(process_t *process, corewar_t *corewar)
{
    int prog_number = 0;

    if (!process || !corewar)
        return FAILURE;
    prog_number = hex_to_uint(corewar->arena, (process->pc + 1 % MEM_SIZE),
        MEM_SIZE);
    set_champ_alive(prog_number, corewar);
    corewar->nbr_live += 1;
    if (corewar->nbr_live == NBR_LIVE) {
        corewar->nbr_live = 0;
        corewar->cycle_to_die = (corewar->cycle_to_die - CYCLE_DELTA >= 0) ?
            corewar->cycle_to_die - CYCLE_DELTA : 0;
    }
    process->pc += LIVE_SIZE;
    process->pc %= MEM_SIZE;
    return SUCCESS;
}
