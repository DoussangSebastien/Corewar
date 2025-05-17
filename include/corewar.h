/*
** EPITECH PROJECT, 2025
** corewar.h
** File description:
** Epitech corewar.h
*/

#ifndef COREWAR_H_
    #define COREWAR_H_

    #include "op.h"
    #include <stdbool.h>

    #define SUCCESS 0
    #define FAILURE 84

    #define DUMP_SIZE 32

    #define DEFAULT_DYNA_SIZE 8

typedef struct {
    int id;
    int opcode;
} instruction_t;

typedef struct {
    char name[PROG_NAME_LENGTH + 1];
    char comment[COMMENT_LENGTH + 1];
    int id;
    int size;
    bool alive;
    bool dead;
} champ_t;

typedef struct {
    int regs[REG_NUMBER];
    int pc;
    int start;
    int id;
    int size;
    bool carry;
    char *body;
    int command_cycle;
} process_t;

typedef struct {
    int len;
    int size;
    champ_t **champs;
} dyna_champ_t;

typedef struct {
    int len;
    int size;
    process_t **process;
} dyna_process_t;

typedef struct {
    dyna_champ_t *champs;
    dyna_process_t *process;
    unsigned char *arena;
    int cycle;
    int winner;
    int nbr_live;
    int cycle_to_die;
    int next_to_die;
    int dump;
} corewar_t;

int corewar(int const ac, char const *const av[]);
void destroy_champ(champ_t *champ);
void destroy_corewar(corewar_t *corewar);
void destroy_process(process_t *process);
int dump(corewar_t *corewar);
int get_champ_index(int id, dyna_champ_t *champs);
int get_value(bool is_dir, int i, int pc, unsigned char *arena);
int get_value_mod(bool is_dir, int i, int pc, unsigned char *arena);
corewar_t *parser(int const ac, char const *const av[]);
int sort_champs_by_id(process_t **champs, int lr[]);

// Champions Dynamic Array
int add_elt_to_champ_array(dyna_champ_t *array, champ_t *element);
void free_champ_array(dyna_champ_t *array, bool free_array);
dyna_champ_t *init_champ_array(void);
int remove_elt_from_champ_array(dyna_champ_t *array, int index);

// Process Dynamic Array
int add_elt_to_process_array(dyna_process_t *array, process_t *element);
void free_process_array(dyna_process_t *array, bool free_array);
dyna_process_t *init_process_array(void);

#endif
