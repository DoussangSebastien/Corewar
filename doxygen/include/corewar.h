/**
 * @file corewar.h
 * @brief Corewar virtual machine main header
 * @details Contains all structures and function prototypes for the Corewar project
 *
 * @copyright EPITECH PROJECT, 2025
 */

#ifndef COREWAR_H_
#define COREWAR_H_

#include "op.h"
#include <stdbool.h>

/**
 * @def SUCCESS
 * @brief Program exit success code
 */
#define SUCCESS 0

/**
 * @def FAILURE
 * @brief Program exit failure code
 */
#define FAILURE 84

/**
 * @def DUMP_SIZE
 * @brief Number of bytes displayed per line in memory dump
 */
#define DUMP_SIZE 32

/**
 * @def DEFAULT_DYNA_SIZE
 * @brief Default size for dynamic arrays
 */
#define DEFAULT_DYNA_SIZE 8

/**
 * @struct instruction_t
 * @brief Represents a VM instruction
 */
typedef struct {
    int id;         /**< Instruction ID */
    int opcode;     /**< Opcode value */
} instruction_t;

/**
 * @struct champ_t
 * @brief Represents a champion (player) in the arena
 */
typedef struct {
    char name[PROG_NAME_LENGTH + 1];    /**< Champion name */
    char comment[COMMENT_LENGTH + 1];   /**< Champion comment */
    int id;                             /**< Champion ID */
    int size;                           /**< Champion program size */
    bool alive;                         /**< Alive status */
    bool dead;                          /**< Death status */
} champ_t;

/**
 * @struct process_t
 * @brief Represents a process executing in the VM
 */
typedef struct {
    int regs[REG_NUMBER];   /**< Process registers */
    int pc;                 /**< Program counter */
    int start;              /**< Starting address */
    int id;                /**< Process ID */
    int size;              /**< Process size */
    bool carry;            /**< Carry flag */
    char *body;            /**< Process executable code */
    int command_cycle;     /**< Cycles until next command */
} process_t;

/**
 * @struct dyna_champ_t
 * @brief Dynamic array for champions
 */
typedef struct {
    int len;        /**< Current number of elements */
    int size;       /**< Current allocated size */
    champ_t **champs; /**< Array of champion pointers */
} dyna_champ_t;

/**
 * @struct dyna_process_t
 * @brief Dynamic array for processes
 */
typedef struct {
    int len;            /**< Current number of elements */
    int size;           /**< Current allocated size */
    process_t **process; /**< Array of process pointers */
} dyna_process_t;

/**
 * @struct corewar_t
 * @brief Main VM state structure
 */
typedef struct {
    dyna_champ_t *champs;       /**< Champion array */
    dyna_process_t *process;    /**< Process array */
    unsigned char *arena;       /**< Memory arena */
    int cycle;                  /**< Current cycle count */
    int winner;                /**< ID of winning champion */
    int nbr_live;              /**< Number of live calls */
    int cycle_to_die;          /**< Cycles until next death check */
    int next_to_die;           /**< Next death cycle */
    int dump;                  /**< Dump cycle flag */
} corewar_t;

/* Core VM functions */
/**
 * @brief Main Corewar execution function
 * @param ac Argument count
 * @param av Argument vector
 * @return int SUCCESS or FAILURE
 */
int corewar(int const ac, char const *const av[]);

/**
 * @brief Frees a champion structure
 * @param champ Champion to free
 */
void destroy_champ(champ_t *champ);

/**
 * @brief Frees the entire VM state
 * @param corewar VM state to free
 */
void destroy_corewar(corewar_t *corewar);

/**
 * @brief Frees a process structure
 * @param process Process to free
 */
void destroy_process(process_t *process);

/**
 * @brief Dumps the arena memory to stdout
 * @param corewar VM state
 * @return int SUCCESS or FAILURE
 */
int dump(corewar_t *corewar);

/**
 * @brief Gets champion index by ID
 * @param id Champion ID to find
 * @param champs Champion array
 * @return int Index or -1 if not found
 */
int get_champ_index(int id, dyna_champ_t *champs);

/**
 * @brief Gets a value from arena memory
 * @param is_dir Whether to treat as direct value
 * @param i Size to read
 * @param pc Current program counter
 * @param arena Memory arena
 * @return int The read value
 */
int get_value(bool is_dir, int i, int pc, unsigned char *arena);

/**
 * @brief Gets a value from arena memory with modulo
 * @param is_dir Whether to treat as direct value
 * @param i Size to read
 * @param pc Current program counter
 * @param arena Memory arena
 * @return int The read value (mod MEM_SIZE)
 */
int get_value_mod(bool is_dir, int i, int pc, unsigned char *arena);

/**
 * @brief Parses command line arguments into VM state
 * @param ac Argument count
 * @param av Argument vector
 * @return corewar_t* Initialized VM state
 */
corewar_t *parser(int const ac, char const *const av[]);

/**
 * @brief Sorts champions by ID
 * @param champs Champion array
 * @param lr Left/right indices for sorting
 * @return int SUCCESS or FAILURE
 */
int sort_champs_by_id(process_t **champs, int lr[]);

/* Champion Dynamic Array functions */
/**
 * @brief Adds element to champion array
 * @param array Target array
 * @param element Element to add
 * @return int SUCCESS or FAILURE
 */
int add_elt_to_champ_array(dyna_champ_t *array, champ_t *element);

/**
 * @brief Frees champion array
 * @param array Array to free
 * @param free_array Whether to free the array itself
 */
void free_champ_array(dyna_champ_t *array, bool free_array);

/**
 * @brief Initializes champion array
 * @return dyna_champ_t* New array
 */
dyna_champ_t *init_champ_array(void);

/**
 * @brief Removes element from champion array
 * @param array Target array
 * @param index Index to remove
 * @return int SUCCESS or FAILURE
 */
int remove_elt_from_champ_array(dyna_champ_t *array, int index);

/* Process Dynamic Array functions */
/**
 * @brief Adds element to process array
 * @param array Target array
 * @param element Element to add
 * @return int SUCCESS or FAILURE
 */
int add_elt_to_process_array(dyna_process_t *array, process_t *element);

/**
 * @brief Frees process array
 * @param array Array to free
 * @param free_array Whether to free the array itself
 */
void free_process_array(dyna_process_t *array, bool free_array);

/**
 * @brief Initializes process array
 * @return dyna_process_t* New array
 */
dyna_process_t *init_process_array(void);

#endif /* COREWAR_H_ */
