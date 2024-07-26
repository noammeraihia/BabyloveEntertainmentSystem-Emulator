#ifndef BES_6502CPU_h
#define BES_6502CPU_h

#include <stdio.h>
#include <stdlib.h>

#include "bes_types.h"

#define BES_CPU_MAX_ADDR_MEM 64 * 1024
#define BES_CPU_INSTRUCTIONS_TABLE_COUNT 256

typedef struct s_bes6502CPU bes6502CPU_t;
typedef struct s_besBus besBus_t;
typedef struct s_besCPUInstruction besCPUInstruction_t; 

struct s_besCPUInstruction {
    const char* name;
    besBYTE_t (*operate)(bes6502CPU_t*) = NULL;
    besBYTE_t (*addressMode)(bes6502CPU_t*) = NULL;
};

struct s_bes6502CPU {
    besBus_t* bus;

    besBYTE_t A = 0x00, X = 0x00, Y=0x00, SP = 0x00;      // accumulator, index X reg, index Y reg, stack pointer reg
    besWORD_t PC = 0x0000;               // program counter reg

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

        besBYTE_t PS = 0x00;           // program status
    };

    // helps for the simulation, the 'c' suffix stands for 'current'

    besBYTE_t cFetchedData = 0x00;
    besWORD_t cAddressAbsolute = 0x0000;
    besWORD_t cAddressRelative = 0x0000;
    besBYTE_t cOpCode = 0x00;
    uint8_t cCycles = 0;

    besCPUInstruction_t instructionTable[COUNT];
};

bes6502CPU_t bes6502CPU_create();

uint8_t bes6502CPU_connectBus(bes6502CPU_t* __handle, besBus_t* __bus);
besBYTE_t bes6502CPU_read(bes6502CPU_t* __handle, besWORD_t __address);
uint8_t bes6502CPU_write(bes6502CPU_t* __handle, besWORD_t __address, besBYTE_t __data);

// addressing modes

besBYTE_t bes6502CPU_IMP(bes6502CPU_t* __handle);  besBYTE_t bes6502CPU_IMM(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_ZP0(bes6502CPU_t* __handle);  besBYTE_t bes6502CPU_ZPX(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_ZPY(bes6502CPU_t* __handle);  besBYTE_t bes6502CPU_REL(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_ABS(bes6502CPU_t* __handle);  besBYTE_t bes6502CPU_ABX(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_ABY(bes6502CPU_t* __handle);  besBYTE_t bes6502CPU_IND(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_IZX(bes6502CPU_t* __handle);  besBYTE_t bes6502CPU_IZY(bes6502CPU_t* __handle);

// legal opcodes

besBYTE_t bes6502CPU_ADC(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_AND(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_ASL(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_BCC(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_BCS(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_BEQ(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_BIT(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_BMI(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_BNE(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_BPL(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_BRK(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_BVC(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_BVS(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_CLC(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_CLD(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_CLI(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_CLV(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_CMP(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_CPX(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_CPY(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_DEC(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_DEX(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_DEY(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_EOR(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_INC(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_INX(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_INY(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_JMP(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_JSR(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_LDA(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_LDX(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_LDY(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_LSR(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_NOP(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_ORA(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_PHA(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_PHP(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_PLA(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_PLP(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_ROL(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_ROR(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_RTI(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_RTS(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_SBC(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_SEC(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_SED(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_SEI(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_STA(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_STX(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_STY(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_TAX(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_TAY(bes6502CPU_t* __handle);
besBYTE_t bes6502CPU_TSX(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_TXA(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_TXS(bes6502CPU_t* __handle);	besBYTE_t bes6502CPU_TYA(bes6502CPU_t* __handle);

// illegal opcodes

besBYTE_t bes6502CPU_XXX(bes6502CPU_t* __handle);

// other CPU funcs

void bes6502CPU_clock(bes6502CPU_t* __handle);
void bes6502CPU_reset(bes6502CPU_t* __handle);
void bes6502CPU_irq(bes6502CPU_t* __handle);
void bes6502CPU_nmi(bes6502CPU_t* __handle);

void bes6502CPU_fetch(bes6502CPU_t* __handle);

struct s_besBus {
    bes6502CPU_t* cpu;
    besBYTE_t ram[BES_CPU_MAX_ADDR_MEM];
};

besBus_t besBus_create(bes6502CPU_t* __cpu);

uint8_t besBus_write(besBus_t* __handle, besWORD_t __address, besBYTE_t __data);
besBYTE_t besBus_read(besBus_t* __handle, besWORD_t __address, bool __readOnly);

#endif BES_6502CPU_h