/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** opcode.c
*/

#include "opcode.h"
#include <stddef.h>

opcode_t const opcode[] = {{1, live}, {2, load}, {3, store}, {4, add},
    {5, sub}, {6, and_command}, {7, or_command}, {8, xor_command}, {9, zjump},
    {10, ldi}, {11, store_i}, {12, my_fork}, {13, lload}, {14, lldi},
    {15, lfork}, {16, aff}, {0, NULL}};
