#ifndef BES_6502CPU_COMMON_h
#define BES_6502CPU_COMMON_h

#define BES_STACK_BASE_LOCATION 0x0100
#define BES_RESET_VECTOR_LOCATION 0xFFFC

#define BES_6502CPU_MAX_ADDR_MEM 64 * 1024
#define BES_6502CPU_INSTRUCTIONS_TABLE_COUNT 256


typedef struct s_besCPUInstruction besCPUInstruction_t;
typedef struct s_bes6502CPU bes6502CPU_t;
typedef struct s_besBus besBus_t;

struct s_besCPUInstruction {
    const char* name;
    besBYTE_t (*operate)(bes6502CPU_t*);
    besBYTE_t (*addressMode)(bes6502CPU_t*);
    uint8_t cycles;
};

struct s_bes6502CPU {
    besBus_t* bus;

    besBYTE_t A, X, Y, SP;      // accumulator, index X reg, index Y reg, stack pointer reg
    besWORD_t PC;               // program counter reg

    union {
        struct {
            besBYTE_t C : 1;        // carry bit
            besBYTE_t Z : 1;        // zero
            besBYTE_t I : 1;        // disable interrupts
            besBYTE_t D : 1;        // decimal mode
            besBYTE_t B : 1;        // break
            besBYTE_t u : 1;        // (unused bit)
            besBYTE_t V : 1;        // overflow
            besBYTE_t N : 1;        // negative

        } PSif;                 // program status individual flags

        besBYTE_t PS;           // program status
    };

    // helps for the simulation, the 'c' suffix stands for 'current'

    besBYTE_t fetchedData;
    besWORD_t addressAbsolute;
    besWORD_t addressRelative;
    besBYTE_t opcode;
    uint8_t cycles;

    besCPUInstruction_t instructionTable[BES_6502CPU_INSTRUCTIONS_TABLE_COUNT];
};

struct s_besBus {
    bes6502CPU_t* cpu;
    besBYTE_t ram[BES_6502CPU_MAX_ADDR_MEM];
};


#endif