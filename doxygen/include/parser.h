/**
 * @file parser.h
 * @brief Corewar binary parser and memory allocation
 * @details Handles champion loading, memory placement, and collision detection
 *
 * @copyright EPITECH PROJECT, 2025
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "corewar.h"

/**
 * @struct free_area_t
 * @brief Represents a free memory area in the arena
 */
typedef struct {
    int start;              /**< Starting address of the free area */
    int size;               /**< Size of the free area in bytes */
    dyna_process_t *champs; /**< Champions that could fit in this area */
} free_area_t;

/**
 * @struct new_champ_t
 * @brief Temporary storage for new champion parameters during parsing
 */
typedef struct {
    int ac;                 /**< Argument count */
    int a;                  /**< Address argument value */
    int n;                  /**< Number argument value */
} new_champ_t;

/* Memory management functions */
/**
 * @brief Checks for memory collisions between champions
 * @param corewar The corewar virtual machine state
 * @return SUCCESS if no collisions, FAILURE otherwise
 */
int check_collisions(corewar_t *corewar);

/**
 * @brief Frees allocated free_area_t structures
 * @param free_areas Array of free areas to free
 * @param nb_free_areas Number of free areas in the array
 */
void free_free_areas(free_area_t *free_areas, int nb_free_areas);

/**
 * @brief Creates a default initialized corewar state
 * @return corewar_t* Newly allocated corewar state
 */
corewar_t *get_default_corewar(void);

/**
 * @brief Calculates total size of all processes
 * @param process The process array
 * @return int Total size in bytes
 */
int get_total_size(dyna_process_t *process);

/**
 * @brief Handles memory allocation when multiple free areas exist
 * @param free_areas Array of free memory areas
 * @param nb_free_areas Number of free areas
 * @param corewar The corewar virtual machine state
 * @return SUCCESS on success, FAILURE on error
 */
int multiple_free_areas(free_area_t *free_areas, int nb_free_areas,
    corewar_t *corewar);

/**
 * @brief Handles memory allocation when one free area exists
 * @param total_size Total size needed for all champions
 * @param corewar The corewar virtual machine state
 * @return SUCCESS on success, FAILURE on error
 */
int one_free_area(int total_size, corewar_t *corewar);

/* Champion loading functions */
/**
 * @brief Parses a champion file and loads it into memory
 * @param filepath Path to the champion file
 * @param new Champion parameters structure
 * @param corewar The corewar virtual machine state
 * @return SUCCESS on success, FAILURE on error
 */
int parse_file(char const *filepath, new_champ_t *new, corewar_t *corewar);

/**
 * @brief Sets the program counter for all champions
 * @param corewar The corewar virtual machine state
 * @return SUCCESS on success, FAILURE on error
 */
int set_champs_pc(corewar_t *corewar);

/* Sorting functions */
/**
 * @brief Sorts free memory areas by size
 * @param free_areas Array of free areas to sort
 * @param lr Left/right indices for the sort algorithm
 * @return SUCCESS on success, FAILURE on error
 */
int sort_free_areas(free_area_t *free_areas, int lr[]);

/**
 * @brief Sorts champions without assigned positions
 * @param unset_champs Array of champions to sort
 * @param lr Left/right indices for the sort algorithm
 * @return SUCCESS on success, FAILURE on error
 */
int sort_unset_champs(process_t **unset_champs, int lr[]);

/* Arena operations */
/**
 * @brief Writes champion programs into the arena memory
 * @param corewar The corewar virtual machine state
 * @return SUCCESS on success, FAILURE on error
 */
int write_champs_in_arena(corewar_t *corewar);

#endif /* PARSER_H_ */
