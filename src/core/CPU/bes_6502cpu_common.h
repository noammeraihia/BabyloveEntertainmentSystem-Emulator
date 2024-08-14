#ifndef BES_6502CPU_COMMON_h
#define BES_6502CPU_COMMON_h

#define BES_STACK_BASE_LOCATION 0x0100
#define BES_RESET_VECTOR_LOCATION 0xFFFC

#define BES_6502CPU_MAX_ADDR_MEM 64 * 1024
#define BES_6502CPU_INSTRUCTIONS_TABLE_COUNT 256

#include "bes_types.h"

typedef struct s_besCPUInstruction besCPUInstruction_t;
typedef struct s_bes6502CPU bes6502CPU_t;
typedef struct s_besBus besBus_t;
typedef enum e_bes6502PSFlags bes6502PSFlags_t;

enum e_bes6502PSFlags
{
    BES_6502_PSF_C = (1 << 0), // carry bit
    BES_6502_PSF_Z = (1 << 1), // zero
    BES_6502_PSF_I = (1 << 2), // disable Interrupts
    BES_6502_PSF_D = (1 << 3), // decimal Mode (unused in this implementation)
    BES_6502_PSF_B = (1 << 4), // break
    BES_6502_PSF_U = (1 << 5), // unused
    BES_6502_PSF_V = (1 << 6), // overflow
    BES_6502_PSF_N = (1 << 7)  // negative
};

besBYTE_t bes6502CPU_getFlag(bes6502CPU_t *__handle, bes6502PSFlags_t __flag);
void bes6502CPU_setFlag(bes6502CPU_t *__handle, bes6502PSFlags_t __flag, besWORD_t __value);

struct s_besBus
{
    besBYTE_t ram[BES_6502CPU_MAX_ADDR_MEM];
};

struct s_besCPUInstruction
{
    const char *name;
    besBYTE_t (*operate)(bes6502CPU_t *);
    besBYTE_t (*addressMode)(bes6502CPU_t *);
    uint8_t cycles;
};

struct s_bes6502CPU
{
    besBus_t bus;

    besBYTE_t A, X, Y, SP; // accumulator, index X reg, index Y reg, stack pointer reg
    besWORD_t PC;          // program counter reg

    besBYTE_t PS; // program status

    // helps for the simulation, the 'c' suffix stands for 'current'

    besBYTE_t fetchedData;
    besWORD_t addressAbsolute;
    besWORD_t addressRelative;
    besBYTE_t opcode;
    uint8_t cycles;

    besCPUInstruction_t instructionTable[BES_6502CPU_INSTRUCTIONS_TABLE_COUNT];
};

#endif