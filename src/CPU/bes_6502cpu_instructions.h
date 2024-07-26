#ifndef BES_6502CPU_INSTRUCTIONS_h
#define BES_6502CPU_INSTRUCTIONS_h

#include "bes_types.h"

typedef struct s_bes6502CPU bes6502CPU_t;
typedef struct s_besCPUInstruction besCPUInstruction_t; 

struct s_besCPUInstruction {
    const char* name;
    besBYTE_t (*operate)(bes6502CPU_t*);
    besBYTE_t (*addressMode)(bes6502CPU_t*);
    uint8_t cycles;
};

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

#endif