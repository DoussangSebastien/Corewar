/**
 * @file opcode.h
 * @brief Corewar opcode definitions and function prototypes.
 * 
 * Defines the opcode structure and function prototypes for Corewar virtual machine instructions.
 */

#ifndef OPCODE_H_
#define OPCODE_H_

#include "corewar.h"

/**
 * @def LIVE_SIZE
 * @brief Size (in bytes) of the `live` instruction in the Corewar arena.
 */
#define LIVE_SIZE 5

/**
 * @struct opcode_t
 * @brief Associates an opcode with its corresponding execution function.
 * 
 * @var opcode_t::opcode
 *   The numeric opcode (e.g., 0x01 for `live`).
 * @var opcode_t::func
 *   Function pointer to the instruction's implementation.
 */
typedef struct {
    int const opcode;                   /**< Opcode numeric value. */
    int (*func)(process_t *, corewar_t *); /**< Instruction execution function. */
} opcode_t;

/**
 * @var opcode
 * @brief Global array mapping opcodes to their functions.
 * @note Defined in the corresponding source file.
 */
extern const opcode_t opcode[];

/* Instruction Functions */
/**
 * @brief `add` instruction: Adds two registers and stores the result in a third.
 */
int add(process_t *process, corewar_t *corewar);

/**
 * @brief `aff` instruction: Displays a character from a register.
 */
int aff(process_t *process, corewar_t *corewar);

/**
 * @brief `and` instruction: Bitwise AND operation (reg/ind/dir -> reg).
 */
int and_command(process_t *process, corewar_t *corewar);

/**
 * @brief `fork` instruction: Creates a new process at PC + offset.
 */
int my_fork(process_t *process, corewar_t *corewar);

/**
 * @brief `lfork` instruction: Long fork (like `fork` but with 16-bit offset).
 */
int lfork(process_t *process, corewar_t *corewar);

/**
 * @brief `ldi` instruction: Loads a value from indirect addressing into a register.
 */
int ldi(process_t *process, corewar_t *corewar);

/**
 * @brief `lldi` instruction: Long `ldi` (no IDX_MOD restriction).
 */
int lldi(process_t *process, corewar_t *corewar);

/**
 * @brief `live` instruction: Marks a champion as alive.
 */
int live(process_t *process, corewar_t *corewar);

/**
 * @brief `lld` instruction: Long load (direct/indirect -> register).
 */
int lload(process_t *process, corewar_t *corewar);

/**
 * @brief `ld` instruction: Loads a value into a register.
 */
int load(process_t *process, corewar_t *corewar);

/**
 * @brief `or` instruction: Bitwise OR operation (reg/ind/dir -> reg).
 */
int or_command(process_t *process, corewar_t *corewar);

/**
 * @brief `st` instruction: Stores a register value into memory (register/indirect).
 */
int store(process_t *process, corewar_t *corewar);

/**
 * @brief `sti` instruction: Stores a register value with indirect addressing.
 */
int store_i(process_t *process, corewar_t *corewar);

/**
 * @brief `sub` instruction: Subtracts two registers and stores the result.
 */
int sub(process_t *process, corewar_t *corewar);

/**
 * @brief `xor` instruction: Bitwise XOR operation (reg/ind/dir -> reg).
 */
int xor_command(process_t *process, corewar_t *corewar);

/**
 * @brief `zjmp` instruction: Conditional jump (if carry flag is set).
 */
int zjump(process_t *process, corewar_t *corewar);

/**
 * @brief Duplicates a process (used by `fork`/`lfork`).
 * @param process The process to duplicate.
 * @param param Additional parameter (e.g., fork offset).
 * @return process_t* The new process copy.
 */
process_t *dup_process(process_t *process, short param);

#endif /* OPCODE_H_ */
