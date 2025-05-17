/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** parse_file
*/

#include "corewar.h"
#include "op.h"
#include "parser.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static process_t *set_default_process(new_champ_t *new)
{
    process_t *p = malloc(sizeof(process_t));

    if (!p)
        return NULL;
    p->id = new->n;
    p->size = 0;
    p->regs[0] = new->n;
    for (int reg = 1; reg < REG_NUMBER; reg++)
        p->regs[reg] = 0;
    p->pc = new->a;
    p->start = p->pc;
    p->carry = false;
    p->body = NULL;
    p->command_cycle = 0;
    return p;
}

static champ_t *set_default_champ(new_champ_t *new)
{
    champ_t *champ = malloc(sizeof(champ_t));

    if (!champ)
        return NULL;
    champ->id = new->n;
    champ->size = 0;
    champ->alive = false;
    champ->dead = false;
    return champ;
}

static int check_magic_number(FILE *file)
{
    unsigned char buffer[4] = {'\0'};
    int magic = 0;

    if (fread(buffer, sizeof(buffer), 1, file) <= 0)
        return FAILURE;
    for (int i = 0; i < 4; i++)
        magic += buffer[i] << (8 * (3 - i));
    if (magic == COREWAR_EXEC_MAGIC)
        return SUCCESS;
    return FAILURE;
}

static int get_champ_name(champ_t *champ, FILE *file)
{
    if (fread(champ->name, sizeof(champ->name) - 1, 1, file) <= 0)
        return FAILURE;
    if (fseek(file, 4, SEEK_CUR) != SUCCESS)
        return FAILURE;
    return SUCCESS;
}

static int get_size(champ_t *champ, process_t *process, FILE *file)
{
    unsigned char buffer[4] = {'\0'};

    if (fread(buffer, sizeof(buffer), 1, file) <= 0)
        return FAILURE;
    for (int i = 0; i < 4; i++) {
        champ->size += buffer[i] << (8 * (3 - i));
        process->size += buffer[i] << (8 * (3 - i));
    }
    return SUCCESS;
}

static int get_champ_comment(champ_t *champ, FILE *file)
{
    if (fread(champ->comment, sizeof(champ->comment) - 1, 1, file) <= 0)
        return FAILURE;
    if (fseek(file, 4, SEEK_CUR) != SUCCESS)
        return FAILURE;
    return SUCCESS;
}

static int write_body_in_process(process_t *process, FILE *file)
{
    process->body = malloc(sizeof(char) * (process->size + 1));
    if (!process->body)
        return FAILURE;
    fread(process->body, process->size, 1, file);
    process->body[process->size] = '\0';
    return SUCCESS;
}

static int read_file_info(process_t *p, champ_t *champ, FILE *file)
{
    if (check_magic_number(file))
        return FAILURE;
    if (get_champ_name(champ, file))
        return FAILURE;
    if (get_size(champ, p, file))
        return FAILURE;
    if (get_champ_comment(champ, file))
        return FAILURE;
    if (write_body_in_process(p, file))
        return FAILURE;
    return SUCCESS;
}

static int add_to_dyna_arrays(FILE *file, corewar_t *corewar,
    process_t *p, champ_t *champ)
{
    fclose(file);
    if (add_elt_to_champ_array(corewar->champs, champ)) {
        destroy_champ(champ);
        return FAILURE;
    }
    if (add_elt_to_process_array(corewar->process, p)) {
        destroy_process(p);
        return FAILURE;
    }
    return SUCCESS;
}

int parse_file(char const *filepath, new_champ_t *new, corewar_t *corewar)
{
    FILE *file = NULL;
    process_t *p = NULL;
    champ_t *champ = NULL;

    if (!filepath || !new)
        return FAILURE;
    file = fopen(filepath, "rb");
    if (!file)
        return FAILURE;
    p = set_default_process(new);
    champ = set_default_champ(new);
    if (!p || !champ || read_file_info(p, champ, file)) {
        destroy_process(p);
        fclose(file);
        return FAILURE;
    }
    return add_to_dyna_arrays(file, corewar, p, champ);
}
