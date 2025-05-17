/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** parser
*/

#ifndef PARSER_H_
    #define PARSER_H_

    #include "corewar.h"

typedef struct {
    int start;
    int size;
    dyna_process_t *champs;
} free_area_t;

typedef struct {
    int ac;
    int a;
    int n;
} new_champ_t;

int check_collisions(corewar_t *corewar);
void free_free_areas(free_area_t *free_areas, int nb_free_areas);
corewar_t *get_default_corewar(void);
int get_total_size(dyna_process_t *process);
int multiple_free_areas(free_area_t *free_areas, int nb_free_areas,
    corewar_t *corewar);
int one_free_area(int total_size, corewar_t *corewar);
int parse_file(char const *filepath, new_champ_t *new, corewar_t *corewar);
int set_champs_pc(corewar_t *corewar);
int sort_free_areas(free_area_t *free_areas, int lr[]);
int sort_unset_champs(process_t **unset_champs, int lr[]);
int write_champs_in_arena(corewar_t *corewar);

#endif /* PARSER_H_ */
