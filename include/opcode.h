/*
** EPITECH PROJECT, 2025
** opcode.h
** File description:
** Epitech opcode.h
*/

#ifndef OPCODE_H_
    #define OPCODE_H_

    #include "corewar.h"

    #define LIVE_SIZE 5

typedef struct {
    int const opcode;
    int (*func)(process_t *, corewar_t *);
} opcode_t;

extern const opcode_t opcode[];

int add(process_t *process, corewar_t *corewar);
int aff(process_t *process, corewar_t *corewar);
int and_command(process_t *process, corewar_t *corewar);
int my_fork(process_t *process, corewar_t *corewar);
int lfork(process_t *process, corewar_t *corewar);
int ldi(process_t *process, corewar_t *corewar);
int lldi(process_t *process, corewar_t *corewar);
int live(process_t *process, corewar_t *corewar);
int lload(process_t *process, corewar_t *corewar);
int load(process_t *process, corewar_t *corewar);
int or_command(process_t *process, corewar_t *corewar);
int store(process_t *process, corewar_t *corewar);
int store_i(process_t *process, corewar_t *corewar);
int sub(process_t *process, corewar_t *corewar);
int xor_command(process_t *process, corewar_t *corewar);
int zjump(process_t *process, corewar_t *corewar);

process_t *dup_process(process_t *process, short param);

#endif
