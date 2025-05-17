/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** bonus_corewar.c
*/

#include "bonus.h"
#include "corewar.h"
#include "my.h"
#include "op.h"
#include "opcode.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

static bool corewar_end(dyna_champ_t *champs)
{
    for (int i = 0; i < champs->len; i++)
        if (!champs->champs[i]->dead)
            return true;
    return false;
}

static void update_death_state(dyna_champ_t *champs, corewar_t *corewar)
{
    champ_t *champ = NULL;

    corewar->next_to_die -= 1;
    for (int i = 0; i < champs->len; i++) {
        champ = champs->champs[i];
        if (!champ->alive || corewar->cycle_to_die == 0)
            champ->dead = true;
        champ->alive = false;
    }
}

static void update_next_to_die(corewar_t *corewar)
{
    corewar->next_to_die += 1;
    if (corewar->next_to_die == corewar->cycle_to_die || corewar->cycle_to_die == 0) {
        update_death_state(corewar->champs, corewar);
        corewar->next_to_die = 0;
    }
}

static int execute_commands(corewar_t *corewar)
{
    char mnemo = 0;

    for (int i = 0; i < corewar->process->len; i++) {
        mnemo = corewar->arena[corewar->process->process[i]->pc];
        if (mnemo < 1 || mnemo > 16)
            continue;
        if (op_tab[mnemo - 1].nbr_cycles >
            corewar->process->process[i]->command_cycle) {
            corewar->process->process[i]->command_cycle += 1;
            continue;
        }
        corewar->process->process[i]->command_cycle = 0;
        if (opcode[mnemo - 1].func(corewar->process->process[i], corewar))
            return FAILURE;
    }
    return SUCCESS;
}

static void write_winner(corewar_t *corewar)
{
    char the_player[] = "The player ";
    char has_won[] = ") has won.\n";
    char tie[] = "It's a tie.\n";
    char *winner_name = NULL;
    int i = get_champ_index(corewar->winner, corewar->champs);
    char id[12] = "";

    if (i >= 0) {
        winner_name = corewar->champs->champs[i]->name;
        write(1, the_player, sizeof(the_player));
        my_itoa(corewar->champs->champs[i]->id, id);
        write(1, id, my_strlen(id));
        write(1, "(", 1);
        write(1, winner_name, my_strlen(winner_name));
        write(1, has_won, sizeof(has_won));
    } else
        write(1, tie, sizeof(tie));
}

int count_alive(corewar_t *corewar)
{
    int alive = 0;
    for (int i = 0; i < corewar->champs->len; i++) {
        if (!corewar->champs->champs[i]->dead)
            alive++;
    }
    return alive;
}

static int corewar_fight(corewar_t *corewar)
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    use_default_colors();
    if (sort_champs_by_id(corewar->process->process,
        (int[2]) {0, corewar->process->len - 1}))
        return FAILURE;
    for (; corewar_end(corewar->champs); corewar->cycle++) {
        if (execute_commands(corewar))
            return FAILURE;
        int ch = getch();
        if (ch == 'q')
            break;
        if (ch == 'p') {
            while ((ch = getch()) != 'p')
                usleep(10000);
        }
        clear();
        display_stats(corewar);
        display_champs(corewar);
        display_arena(corewar);
        update_next_to_die(corewar);
        usleep(50000);
    }
    endwin();
    write_winner(corewar);
    return SUCCESS;
}

int corewar(int const ac, char const *const av[])
{
    corewar_t *corewar = NULL;
    int ret_value = 0;

    if (!av)
        return FAILURE;
    corewar = parser(ac, av);
    if (!corewar)
        return FAILURE;
    ret_value = corewar_fight(corewar);
    destroy_corewar(corewar);
    return ret_value;
}
