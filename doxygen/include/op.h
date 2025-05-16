/**
 * @file op.h
 * @brief Corewar operation definitions and VM constants
 * @details Contains all VM specifications, operation codes, and structures
 * 
 * @copyright EPITECH PROJECT, 2025
 * @remark Robot Factory version
 */

#ifndef _OP_H_
#define _OP_H_

/* Memory and addressing constants */
/**
 * @def MEM_SIZE
 * @brief Total size of the Corewar arena memory (6KB)
 */
#define MEM_SIZE (6 * 1024)

/**
 * @def IDX_MOD
 * @brief Index modulo for memory addressing
 * @details Used to wrap around the arena when using indirect addressing
 */
#define IDX_MOD 512

/**
 * @def MAX_ARGS_NUMBER
 * @brief Maximum number of arguments per operation
 */
#define MAX_ARGS_NUMBER 4

/* Syntax constants */
/**
 * @def COMMENT_CHAR
 * @brief Character that starts a comment
 */
#define COMMENT_CHAR '#'

/**
 * @def LABEL_CHAR
 * @brief Character that starts a label
 */
#define LABEL_CHAR ':'

/**
 * @def DIRECT_CHAR
 * @brief Prefix for direct values
 */
#define DIRECT_CHAR '%'

/**
 * @def SEPARATOR_CHAR
 * @brief Character separating arguments
 */
#define SEPARATOR_CHAR ','

/**
 * @def LABEL_CHARS
 * @brief Valid characters for label names
 */
#define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

/* Directive strings */
/**
 * @def NAME_CMD_STRING
 * @brief Champion name directive string
 */
#define NAME_CMD_STRING ".name"

/**
 * @def COMMENT_CMD_STRING
 * @brief Champion comment directive string
 */
#define COMMENT_CMD_STRING ".comment"

/* Register configuration */
/**
 * @def REG_NUMBER
 * @brief Number of available registers
 */
#define REG_NUMBER 16

/* Argument type system */
/**
 * @typedef args_type_t
 * @brief Type for argument type flags
 */
typedef char args_type_t;

/**
 * @def T_REG
 * @brief Flag for register argument type
 */
#define T_REG 1

/**
 * @def T_DIR
 * @brief Flag for direct argument type
 */
#define T_DIR 2

/**
 * @def T_IND
 * @brief Flag for indirect argument type
 */
#define T_IND 4

/**
 * @def T_LAB
 * @brief Flag for label argument type
 */
#define T_LAB 8

/**
 * @struct op_t
 * @brief Operation definition structure
 */
typedef struct op_s {
    char *mnemonique;      /**< Instruction mnemonic (e.g., "live") */
    char nbr_args;         /**< Number of arguments */
    args_type_t type[MAX_ARGS_NUMBER]; /**< Argument type flags */
    char code;             /**< Opcode byte value */
    int nbr_cycles;        /**< Cycles needed to execute */
    char *comment;         /**< Description of the instruction */
} op_t;

/* Size constants (in bytes) */
/**
 * @def IND_SIZE
 * @brief Size of indirect values
 */
#define IND_SIZE 2

/**
 * @def DIR_SIZE
 * @brief Size of direct values
 */
#define DIR_SIZE 4

/**
 * @def REG_SIZE
 * @brief Size of register values (same as direct)
 */
#define REG_SIZE DIR_SIZE

/* Operation table */
/**
 * @var op_tab
 * @brief Global table of all VM operations
 * @note Defined in corresponding source file
 */
extern const op_t op_tab[];

/* Champion header structure */
/**
 * @def PROG_NAME_LENGTH
 * @brief Maximum length of champion name
 */
#define PROG_NAME_LENGTH 128

/**
 * @def COMMENT_LENGTH
 * @brief Maximum length of champion comment
 */
#define COMMENT_LENGTH 2048

/**
 * @def COREWAR_EXEC_MAGIC
 * @brief Magic number identifying Corewar executables
 */
#define COREWAR_EXEC_MAGIC 0xea83f3

/**
 * @struct header_t
 * @brief Champion executable header structure
 */
typedef struct header_s {
    int magic;              /**< Magic number (COREWAR_EXEC_MAGIC) */
    char prog_name[PROG_NAME_LENGTH + 1]; /**< Champion name */
    int prog_size;          /**< Program size in bytes */
    char comment[COMMENT_LENGTH + 1]; /**< Champion comment */
} header_t;

/* Live cycle management */
/**
 * @def CYCLE_TO_DIE
 * @brief Initial number of cycles before death check
 */
#define CYCLE_TO_DIE 1536

/**
 * @def CYCLE_DELTA
 * @brief Cycle reduction amount after NBR_LIVE calls
 */
#define CYCLE_DELTA 5

/**
 * @def NBR_LIVE
 * @brief Number of live calls before cycle reduction
 */
#define NBR_LIVE 40

#endif /* _OP_H_ */
