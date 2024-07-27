#include "core/CPU/bes_6502cpu.h"

/* BES 6502 CPU funcs */

bes6502CPU_t bes6502CPU_create()
{
    bes6502CPU_t _cpu = {
        .bus = NULL,
        .A = 0x00,
        .X = 0x00,
        .Y = 0x00,
        .SP = 0x00,
        .PC = 0x0000,
        .PS = 0x00,

        .fetchedData = 0x00,
        .addressAbsolute = 0x0000,
        .addressRelative = 0x0000,
        .opcode = 0x00,
        .cycles = 0,
        .instructionTable = {
            {"BRK", &bes6502CPU_BRK, &bes6502CPU_IMM, 7},
            {"ORA", &bes6502CPU_ORA, &bes6502CPU_IZX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 3},
            {"ORA", &bes6502CPU_ORA, &bes6502CPU_ZP0, 3},
            {"ASL", &bes6502CPU_ASL, &bes6502CPU_ZP0, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"PHP", &bes6502CPU_PHP, &bes6502CPU_IMP, 3},
            {"ORA", &bes6502CPU_ORA, &bes6502CPU_IMM, 2},
            {"ASL", &bes6502CPU_ASL, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"ORA", &bes6502CPU_ORA, &bes6502CPU_ABS, 4},
            {"ASL", &bes6502CPU_ASL, &bes6502CPU_ABS, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"BPL", &bes6502CPU_BPL, &bes6502CPU_REL, 2},
            {"ORA", &bes6502CPU_ORA, &bes6502CPU_IZY, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"ORA", &bes6502CPU_ORA, &bes6502CPU_ZPX, 4},
            {"ASL", &bes6502CPU_ASL, &bes6502CPU_ZPX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"CLC", &bes6502CPU_CLC, &bes6502CPU_IMP, 2},
            {"ORA", &bes6502CPU_ORA, &bes6502CPU_ABY, 4},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"ORA", &bes6502CPU_ORA, &bes6502CPU_ABX, 4},
            {"ASL", &bes6502CPU_ASL, &bes6502CPU_ABX, 7},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"JSR", &bes6502CPU_JSR, &bes6502CPU_ABS, 6},
            {"AND", &bes6502CPU_AND, &bes6502CPU_IZX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"BIT", &bes6502CPU_BIT, &bes6502CPU_ZP0, 3},
            {"AND", &bes6502CPU_AND, &bes6502CPU_ZP0, 3},
            {"ROL", &bes6502CPU_ROL, &bes6502CPU_ZP0, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"PLP", &bes6502CPU_PLP, &bes6502CPU_IMP, 4},
            {"AND", &bes6502CPU_AND, &bes6502CPU_IMM, 2},
            {"ROL", &bes6502CPU_ROL, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"BIT", &bes6502CPU_BIT, &bes6502CPU_ABS, 4},
            {"AND", &bes6502CPU_AND, &bes6502CPU_ABS, 4},
            {"ROL", &bes6502CPU_ROL, &bes6502CPU_ABS, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"BMI", &bes6502CPU_BMI, &bes6502CPU_REL, 2},
            {"AND", &bes6502CPU_AND, &bes6502CPU_IZY, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"AND", &bes6502CPU_AND, &bes6502CPU_ZPX, 4},
            {"ROL", &bes6502CPU_ROL, &bes6502CPU_ZPX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"SEC", &bes6502CPU_SEC, &bes6502CPU_IMP, 2},
            {"AND", &bes6502CPU_AND, &bes6502CPU_ABY, 4},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"AND", &bes6502CPU_AND, &bes6502CPU_ABX, 4},
            {"ROL", &bes6502CPU_ROL, &bes6502CPU_ABX, 7},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"RTI", &bes6502CPU_RTI, &bes6502CPU_IMP, 6},
            {"EOR", &bes6502CPU_EOR, &bes6502CPU_IZX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 3},
            {"EOR", &bes6502CPU_EOR, &bes6502CPU_ZP0, 3},
            {"LSR", &bes6502CPU_LSR, &bes6502CPU_ZP0, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"PHA", &bes6502CPU_PHA, &bes6502CPU_IMP, 3},
            {"EOR", &bes6502CPU_EOR, &bes6502CPU_IMM, 2},
            {"LSR", &bes6502CPU_LSR, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"JMP", &bes6502CPU_JMP, &bes6502CPU_ABS, 3},
            {"EOR", &bes6502CPU_EOR, &bes6502CPU_ABS, 4},
            {"LSR", &bes6502CPU_LSR, &bes6502CPU_ABS, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"BVC", &bes6502CPU_BVC, &bes6502CPU_REL, 2},
            {"EOR", &bes6502CPU_EOR, &bes6502CPU_IZY, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"EOR", &bes6502CPU_EOR, &bes6502CPU_ZPX, 4},
            {"LSR", &bes6502CPU_LSR, &bes6502CPU_ZPX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"CLI", &bes6502CPU_CLI, &bes6502CPU_IMP, 2},
            {"EOR", &bes6502CPU_EOR, &bes6502CPU_ABY, 4},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"EOR", &bes6502CPU_EOR, &bes6502CPU_ABX, 4},
            {"LSR", &bes6502CPU_LSR, &bes6502CPU_ABX, 7},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"RTS", &bes6502CPU_RTS, &bes6502CPU_IMP, 6},
            {"ADC", &bes6502CPU_ADC, &bes6502CPU_IZX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 3},
            {"ADC", &bes6502CPU_ADC, &bes6502CPU_ZP0, 3},
            {"ROR", &bes6502CPU_ROR, &bes6502CPU_ZP0, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"PLA", &bes6502CPU_PLA, &bes6502CPU_IMP, 4},
            {"ADC", &bes6502CPU_ADC, &bes6502CPU_IMM, 2},
            {"ROR", &bes6502CPU_ROR, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"JMP", &bes6502CPU_JMP, &bes6502CPU_IND, 5},
            {"ADC", &bes6502CPU_ADC, &bes6502CPU_ABS, 4},
            {"ROR", &bes6502CPU_ROR, &bes6502CPU_ABS, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"BVS", &bes6502CPU_BVS, &bes6502CPU_REL, 2},
            {"ADC", &bes6502CPU_ADC, &bes6502CPU_IZY, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"ADC", &bes6502CPU_ADC, &bes6502CPU_ZPX, 4},
            {"ROR", &bes6502CPU_ROR, &bes6502CPU_ZPX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"SEI", &bes6502CPU_SEI, &bes6502CPU_IMP, 2},
            {"ADC", &bes6502CPU_ADC, &bes6502CPU_ABY, 4},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"ADC", &bes6502CPU_ADC, &bes6502CPU_ABX, 4},
            {"ROR", &bes6502CPU_ROR, &bes6502CPU_ABX, 7},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"STA", &bes6502CPU_STA, &bes6502CPU_IZX, 6},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"STY", &bes6502CPU_STY, &bes6502CPU_ZP0, 3},
            {"STA", &bes6502CPU_STA, &bes6502CPU_ZP0, 3},
            {"STX", &bes6502CPU_STX, &bes6502CPU_ZP0, 3},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 3},
            {"DEY", &bes6502CPU_DEY, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"TXA", &bes6502CPU_TXA, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"STY", &bes6502CPU_STY, &bes6502CPU_ABS, 4},
            {"STA", &bes6502CPU_STA, &bes6502CPU_ABS, 4},
            {"STX", &bes6502CPU_STX, &bes6502CPU_ABS, 4},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 4},
            {"BCC", &bes6502CPU_BCC, &bes6502CPU_REL, 2},
            {"STA", &bes6502CPU_STA, &bes6502CPU_IZY, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"STY", &bes6502CPU_STY, &bes6502CPU_ZPX, 4},
            {"STA", &bes6502CPU_STA, &bes6502CPU_ZPX, 4},
            {"STX", &bes6502CPU_STX, &bes6502CPU_ZPY, 4},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 4},
            {"TYA", &bes6502CPU_TYA, &bes6502CPU_IMP, 2},
            {"STA", &bes6502CPU_STA, &bes6502CPU_ABY, 5},
            {"TXS", &bes6502CPU_TXS, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 5},
            {"STA", &bes6502CPU_STA, &bes6502CPU_ABX, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"LDY", &bes6502CPU_LDY, &bes6502CPU_IMM, 2},
            {"LDA", &bes6502CPU_LDA, &bes6502CPU_IZX, 6},
            {"LDX", &bes6502CPU_LDX, &bes6502CPU_IMM, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"LDY", &bes6502CPU_LDY, &bes6502CPU_ZP0, 3},
            {"LDA", &bes6502CPU_LDA, &bes6502CPU_ZP0, 3},
            {"LDX", &bes6502CPU_LDX, &bes6502CPU_ZP0, 3},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 3},
            {"TAY", &bes6502CPU_TAY, &bes6502CPU_IMP, 2},
            {"LDA", &bes6502CPU_LDA, &bes6502CPU_IMM, 2},
            {"TAX", &bes6502CPU_TAX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"LDY", &bes6502CPU_LDY, &bes6502CPU_ABS, 4},
            {"LDA", &bes6502CPU_LDA, &bes6502CPU_ABS, 4},
            {"LDX", &bes6502CPU_LDX, &bes6502CPU_ABS, 4},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 4},
            {"BCS", &bes6502CPU_BCS, &bes6502CPU_REL, 2},
            {"LDA", &bes6502CPU_LDA, &bes6502CPU_IZY, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"LDY", &bes6502CPU_LDY, &bes6502CPU_ZPX, 4},
            {"LDA", &bes6502CPU_LDA, &bes6502CPU_ZPX, 4},
            {"LDX", &bes6502CPU_LDX, &bes6502CPU_ZPY, 4},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 4},
            {"CLV", &bes6502CPU_CLV, &bes6502CPU_IMP, 2},
            {"LDA", &bes6502CPU_LDA, &bes6502CPU_ABY, 4},
            {"TSX", &bes6502CPU_TSX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 4},
            {"LDY", &bes6502CPU_LDY, &bes6502CPU_ABX, 4},
            {"LDA", &bes6502CPU_LDA, &bes6502CPU_ABX, 4},
            {"LDX", &bes6502CPU_LDX, &bes6502CPU_ABY, 4},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 4},
            {"CPY", &bes6502CPU_CPY, &bes6502CPU_IMM, 2},
            {"CMP", &bes6502CPU_CMP, &bes6502CPU_IZX, 6},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"CPY", &bes6502CPU_CPY, &bes6502CPU_ZP0, 3},
            {"CMP", &bes6502CPU_CMP, &bes6502CPU_ZP0, 3},
            {"DEC", &bes6502CPU_DEC, &bes6502CPU_ZP0, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"INY", &bes6502CPU_INY, &bes6502CPU_IMP, 2},
            {"CMP", &bes6502CPU_CMP, &bes6502CPU_IMM, 2},
            {"DEX", &bes6502CPU_DEX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"CPY", &bes6502CPU_CPY, &bes6502CPU_ABS, 4},
            {"CMP", &bes6502CPU_CMP, &bes6502CPU_ABS, 4},
            {"DEC", &bes6502CPU_DEC, &bes6502CPU_ABS, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"BNE", &bes6502CPU_BNE, &bes6502CPU_REL, 2},
            {"CMP", &bes6502CPU_CMP, &bes6502CPU_IZY, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"CMP", &bes6502CPU_CMP, &bes6502CPU_ZPX, 4},
            {"DEC", &bes6502CPU_DEC, &bes6502CPU_ZPX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"CLD", &bes6502CPU_CLD, &bes6502CPU_IMP, 2},
            {"CMP", &bes6502CPU_CMP, &bes6502CPU_ABY, 4},
            {"NOP", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"CMP", &bes6502CPU_CMP, &bes6502CPU_ABX, 4},
            {"DEC", &bes6502CPU_DEC, &bes6502CPU_ABX, 7},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"CPX", &bes6502CPU_CPX, &bes6502CPU_IMM, 2},
            {"SBC", &bes6502CPU_SBC, &bes6502CPU_IZX, 6},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"CPX", &bes6502CPU_CPX, &bes6502CPU_ZP0, 3},
            {"SBC", &bes6502CPU_SBC, &bes6502CPU_ZP0, 3},
            {"INC", &bes6502CPU_INC, &bes6502CPU_ZP0, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 5},
            {"INX", &bes6502CPU_INX, &bes6502CPU_IMP, 2},
            {"SBC", &bes6502CPU_SBC, &bes6502CPU_IMM, 2},
            {"NOP", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_SBC, &bes6502CPU_IMP, 2},
            {"CPX", &bes6502CPU_CPX, &bes6502CPU_ABS, 4},
            {"SBC", &bes6502CPU_SBC, &bes6502CPU_ABS, 4},
            {"INC", &bes6502CPU_INC, &bes6502CPU_ABS, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"BEQ", &bes6502CPU_BEQ, &bes6502CPU_REL, 2},
            {"SBC", &bes6502CPU_SBC, &bes6502CPU_IZY, 5},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 8},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"SBC", &bes6502CPU_SBC, &bes6502CPU_ZPX, 4},
            {"INC", &bes6502CPU_INC, &bes6502CPU_ZPX, 6},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 6},
            {"SED", &bes6502CPU_SED, &bes6502CPU_IMP, 2},
            {"SBC", &bes6502CPU_SBC, &bes6502CPU_ABY, 4},
            {"NOP", &bes6502CPU_NOP, &bes6502CPU_IMP, 2},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
            {"???", &bes6502CPU_NOP, &bes6502CPU_IMP, 4},
            {"SBC", &bes6502CPU_SBC, &bes6502CPU_ABX, 4},
            {"INC", &bes6502CPU_INC, &bes6502CPU_ABX, 7},
            {"???", &bes6502CPU_XXX, &bes6502CPU_IMP, 7},
        }};

    return _cpu;
}

uint8_t bes6502CPU_connectBus(bes6502CPU_t *__handle, besBus_t *__bus)
{
    if (__bus)
    {
        __handle->bus = __bus;

        return BES_U8SUCCESS;
    }

    return BES_U8FAILURE;
}

besBYTE_t bes6502CPU_read(bes6502CPU_t *__handle, besWORD_t __address)
{
    return besBus_read(__handle->bus, __address, 0);
}

uint8_t bes6502CPU_write(bes6502CPU_t *__handle, besWORD_t __address, besBYTE_t __data)
{
    return besBus_write(__handle->bus, __address, __data);
}

void bes6502CPU_clock(bes6502CPU_t *__handle)
{
    if (__handle->cycles == 0)
    {
        __handle->opcode = bes6502CPU_read(__handle, __handle->PC);
        __handle->PC++;

        __handle->cycles = __handle->instructionTable[__handle->opcode].cycles;
        uint8_t additionalCycle1 = (*__handle->instructionTable[__handle->opcode].addressMode)(__handle);
        uint8_t additionalCycle2 = (*__handle->instructionTable[__handle->opcode].operate)(__handle);

        __handle->cycles += (additionalCycle1 & additionalCycle2);
    }

    __handle->cycles--;
}

void bes6502CPU_reset(bes6502CPU_t *__handle)
{
    __handle->A = 0x00;
    __handle->X = 0x00;
    __handle->Y = 0x00;
    __handle->SP = 0xFD;
    __handle->PS = 0x00;

    __handle->addressAbsolute = BES_RESET_VECTOR_LOCATION;
    besBYTE_t low = bes6502CPU_read(__handle, __handle->addressAbsolute + 0);
    besBYTE_t high = bes6502CPU_read(__handle, __handle->addressAbsolute + 1);

    __handle->PC = (high << 8) | low;

    __handle->addressAbsolute = 0x0000;
    __handle->addressRelative = 0x0000;

    __handle->fetchedData = 0x00;

    __handle->cycles = 8;
}

void bes6502CPU_irq(bes6502CPU_t *__handle)
{
    if (!bes6502CPU_getFlag(__handle, BES_6502_PSF_I))
    {
        bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, (__handle->PC >> 8) & 0xFF);
        __handle->SP--;
        bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, __handle->PC & 0xFF);
        __handle->SP--;

        bes6502CPU_setFlag(__handle, BES_6502_PSF_B, 0);
        bes6502CPU_setFlag(__handle, BES_6502_PSF_U, 1);
        bes6502CPU_setFlag(__handle, BES_6502_PSF_I, 1);
        bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, __handle->PS);
        __handle->SP--;

        __handle->addressAbsolute = 0xFFFE;
        besBYTE_t low = bes6502CPU_read(__handle, __handle->addressAbsolute + 0);
        besBYTE_t high = bes6502CPU_read(__handle, __handle->addressAbsolute + 1);
        __handle->PC = (high << 8) | low;

        __handle->cycles = 7;
    }
}

void bes6502CPU_nmi(bes6502CPU_t *__handle)
{
    bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, (__handle->PC >> 8) & 0xFF);
    __handle->SP--;
    bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, __handle->PC & 0xFF);
    __handle->SP--;

    bes6502CPU_setFlag(__handle, BES_6502_PSF_B, 0);
    bes6502CPU_setFlag(__handle, BES_6502_PSF_U, 1);
    bes6502CPU_setFlag(__handle, BES_6502_PSF_I, 1);
    bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, __handle->PS);
    __handle->SP--;

    __handle->addressAbsolute = 0xFFFA;
    besBYTE_t low = bes6502CPU_read(__handle, __handle->addressAbsolute + 0);
    besBYTE_t high = bes6502CPU_read(__handle, __handle->addressAbsolute + 1);
    __handle->PC = (high << 8) | low;

    __handle->cycles = 8;
}

void bes6502CPU_fetch(bes6502CPU_t *__handle)
{
    if (!(__handle->instructionTable[__handle->opcode].addressMode == &bes6502CPU_IMP))
        __handle->fetchedData = bes6502CPU_read(__handle, __handle->addressAbsolute);
}

/* BES BUS funcs */

besBus_t besBus_create(bes6502CPU_t *__cpu)
{
    besBus_t _bus = {.cpu = __cpu, .ram = {0x00}};
    bes6502CPU_connectBus(_bus.cpu, &_bus);

    return _bus;
}

uint8_t besBus_write(besBus_t *__handle, besWORD_t __address, besBYTE_t __data)
{
    if (__address >= 0x0000 && __address <= 0xFFFF)
    {
        __handle->ram[__address] = __data;

        return BES_U8SUCCESS;
    }

    return BES_U8FAILURE;
}

besBYTE_t besBus_read(besBus_t *__handle, besWORD_t __address, bool __readOnly)
{
    if (__address >= 0x0000 && __address <= 0xFFFF)
        return __handle->ram[__address];

    return BES_U8FAILURE;
}