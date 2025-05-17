/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** display.c
*/

#include "corewar.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include "op.h"
#include "stdbool.h"

static void init_colors(void)
{
    start_color();
    // arena
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    // stat
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    // pc
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    // processes
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    init_pair(8, COLOR_BLUE, COLOR_BLACK);
    init_pair(9, COLOR_BLACK, COLOR_RED);
    init_pair(10, COLOR_BLACK, COLOR_GREEN);
    init_pair(11, COLOR_BLACK, COLOR_CYAN);
    init_pair(12, COLOR_BLACK, COLOR_YELLOW);
    init_pair(13, COLOR_BLACK, COLOR_BLUE);
}

static bool dead_process(process_t *process, corewar_t *corewar)
{
    for (int i = 0; i < corewar->champs->len; i++) {
        if (process->id == corewar->champs->champs[i]->id && corewar->champs->champs[i]->dead)
            return true;
    }
    return false;
}

static int get_color(corewar_t *corewar, int i)
{
    process_t *process = NULL; 
    int start = 0;
    int size = 0;
    int pc = 0;

    for (int j = 0; j < corewar->process->len; j++) {
        process = corewar->process->process[j];
        start = process->start;
        size = process->size;
        pc = process->pc;
        if (i == pc && i < start + size && !dead_process(process, corewar))
            return COLOR_PAIR(3);
        if ((i >= start && i < start + size))
            return COLOR_PAIR(4 + (process->id % 12));
    }
    return COLOR_PAIR(1);
}

void display_arena(corewar_t *corewar)
{
    int color = 0;

    if (!corewar)
        return;
    init_colors();
    for (int i = 0; i < MEM_SIZE; i++) {
        color = get_color(corewar, i);
        attron(color);
        printw("%02x", corewar->arena[i]);
        attroff(color);
    }
    printw("\n");
}

void display_stats(corewar_t *corewar)
{
    int alive = 0;
    int y = 0;

    if (!corewar)
        return;
    init_colors();
    attron(COLOR_PAIR(2));
    for (int i = 0; i < corewar->champs->len; i++) {
        if (!corewar->champs->champs[i]->dead)
            alive++;
    }
    mvprintw(y++, 0, "Cycle: %d | Cycle to die: %d | Processes: %d | Champs alive: %d/%d | Press 'q' to quit",
        corewar->cycle, corewar->cycle_to_die, corewar->process->len, alive, corewar->champs->len);
    attroff(COLOR_PAIR(2));
}

void display_champs(corewar_t *corewar)
{
    int color = 0;
    int base_y = 3;

    if (!corewar)
        return;
    init_colors();
    for (int i = 0; i < corewar->champs->len; i++) {
        int y = base_y + i;
        color = 4 + (corewar->champs->champs[i]->id % 12);
        attron(COLOR_PAIR(color));
        process_t *process = NULL;
        int mnemo = 0;
        for (int j = 0; j < corewar->process->len; j++) {
            if (corewar->process->process[j]->id == corewar->champs->champs[i]->id) {
                process = corewar->process->process[j];
                break;
            }
        }
        mnemo = process ? corewar->arena[process->pc] : 0;
        const char *opcode_str = (mnemo >= 1 && mnemo <= 16 && !corewar->champs->champs[i]->dead) ?
                                 op_tab[mnemo - 1].mnemonique : "None";
        mvprintw(y, 0,
            "name: %15s | comment: %15s | STATUS: %13s | opcode: %s",
            corewar->champs->champs[i]->name,
            corewar->champs->champs[i]->comment,
            (corewar->champs->champs[i]->dead) ? "dead" : "alive",
            opcode_str);
        attroff(COLOR_PAIR(color));
    }
    printw("\n");
}
