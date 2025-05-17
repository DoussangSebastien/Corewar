/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** parser
*/

#include "corewar.h"
#include "my.h"
#include "parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int check_champs_prog_numbers(int new, dyna_champ_t *champs)
{
    for (int i = 0; i < champs->len; i++)
        if (new == champs->champs[i]->id)
            return FAILURE;
    return SUCCESS;
}

static bool check_prog_number(int prog_num, dyna_champ_t *champs)
{
    for (int i = 0; i < champs->len; i++)
        if (prog_num == champs->champs[i]->id)
            return true;
    return false;
}

static int get_next_prog_number(dyna_champ_t *champs)
{
    int n = 1;

    for (; check_prog_number(n, champs); n++);
    return n;
}

static int check_dump(int const ac, char const *const av[], int *i,
    corewar_t *corewar)
{
    if (!my_strcmp(av[*i], "-dump")) {
        if (*i + 1 >= ac || !my_str_isnum(av[*i + 1]))
            return FAILURE;
        corewar->dump = my_atoi(av[*i + 1]);
        *i += 2;
    }
    return SUCCESS;
}

static int parse_champs_flags(new_champ_t *new, char const *const av[], int *i,
    corewar_t *corewar)
{
    if (!my_strcmp(av[*i], "-n")) {
        if (*i + 1 >= new->ac || new->n != -1 || !my_str_isnum(av[*i + 1]))
            return FAILURE;
        new->n = my_atoi(av[*i + 1]);
        if (new->n <= 0 || check_champs_prog_numbers(new->n, corewar->champs))
            return FAILURE;
        *i += 2;
    }
    if (!my_strcmp(av[*i], "-a")) {
        if (*i + 1 >= new->ac || new->a != -1 || !my_str_isnum(av[*i + 1]))
            return FAILURE;
        new->a = (my_atoi(av[*i + 1])) % MEM_SIZE;
        *i += 2;
    }
    return SUCCESS;
}

static int parse_arguments(int const ac, char const *const av[],
    corewar_t *corewar)
{
    new_champ_t new = {ac, 0, 0};
    int i = 1;

    if (check_dump(ac, av, &i, corewar))
        return FAILURE;
    for (; i < ac; i++) {
        new.a = -1;
        new.n = -1;
        if (parse_champs_flags(&new, av, &i, corewar))
            return FAILURE;
        if (parse_champs_flags(&new, av, &i, corewar))
            return FAILURE;
        if (i >= ac)
            return FAILURE;
        if (new.n == -1)
            new.n = get_next_prog_number(corewar->champs);
        if (parse_file(av[i], &new, corewar))
            return FAILURE;
    }
    return SUCCESS;
}

corewar_t *parser(int const ac, char const *const av[])
{
    corewar_t *corewar = NULL;

    if (!av)
        return NULL;
    corewar = get_default_corewar();
    if (!corewar)
        return NULL;
    if (parse_arguments(ac, av, corewar) || corewar->champs->len < 2) {
        destroy_corewar(corewar);
        return NULL;
    }
    if (set_champs_pc(corewar) || write_champs_in_arena(corewar)) {
        destroy_corewar(corewar);
        return NULL;
    }
    for (int i = 0; i < corewar->process->len; i++)
        corewar->process->process[i]->start = corewar->process->process[i]->pc;
    return corewar;
}
