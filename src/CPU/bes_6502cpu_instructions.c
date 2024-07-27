#include "CPU/bes_6502cpu_instructions.h"

besBYTE_t bes6502CPU_read(bes6502CPU_t* __handle, besWORD_t __address);
uint8_t bes6502CPU_write(bes6502CPU_t* __handle, besWORD_t __address, besBYTE_t __data);

void bes6502CPU_fetch(bes6502CPU_t* __handle);

besBYTE_t bes6502CPU_IMP(bes6502CPU_t* __handle)
{
    __handle->fetchedData = __handle->A;

    return 0x00;
}

besBYTE_t bes6502CPU_IMM(bes6502CPU_t* __handle)
{
    __handle->addressAbsolute = __handle->PC++;

    return 0x00;
}

besBYTE_t bes6502CPU_ZP0(bes6502CPU_t* __handle)
{
    __handle->addressAbsolute = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    __handle->addressAbsolute &= 0x00FF;

    return 0x00;
}

besBYTE_t bes6502CPU_ZPX(bes6502CPU_t* __handle)
{
    __handle->addressAbsolute = bes6502CPU_read(__handle, __handle->PC + __handle->X);
    __handle->PC++;
    __handle->addressAbsolute &= 0x00FF;

    return 0x00;
}

besBYTE_t bes6502CPU_ZPY(bes6502CPU_t* __handle)
{
    __handle->addressAbsolute = bes6502CPU_read(__handle, __handle->PC + __handle->Y);
    __handle->PC++;
    __handle->addressAbsolute &= 0x00FF;

    return 0x00;
}

besBYTE_t bes6502CPU_REL(bes6502CPU_t* __handle)
{
    __handle->addressRelative = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;

    if (__handle->addressRelative & 0x80)
        __handle->addressRelative |= 0xFF00;

    return 0x00; 
}

besBYTE_t bes6502CPU_ABS(bes6502CPU_t* __handle)
{
    besBYTE_t low = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    besBYTE_t high = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    __handle->addressAbsolute = (high << 8) | low;

    return 0x00;
}

besBYTE_t bes6502CPU_ABX(bes6502CPU_t* __handle)
{
    besBYTE_t low = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    besBYTE_t high = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    __handle->addressAbsolute = (high << 8) | low;
    __handle->addressAbsolute += __handle->X;

    if ((__handle->addressAbsolute & 0xFF00) != (high << 8))
        return 0x1;

    return 0x00;
}

besBYTE_t bes6502CPU_ABY(bes6502CPU_t* __handle)
{
    besBYTE_t low = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    besBYTE_t high = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    __handle->addressAbsolute = (high << 8) | low;
    __handle->addressAbsolute += __handle->Y;

    if ((__handle->addressAbsolute & 0xFF00) != (high << 8))
        return 0x1;

    return 0x00;
}

besBYTE_t bes6502CPU_IND(bes6502CPU_t* __handle)
{
    besBYTE_t ptrLow = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    besBYTE_t ptrHigh = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;

    besWORD_t ptr = (ptrHigh << 8) | ptrLow;

    if (ptrLow == 0x00FF)
        __handle->addressAbsolute = (bes6502CPU_read(__handle, ptr & 0xFF00) << 8) | bes6502CPU_read(__handle, ptr + 0);
    else
        __handle->addressAbsolute = (bes6502CPU_read(__handle, ptr + 1) << 8) | bes6502CPU_read(__handle, ptr + 0);

    return 0x00; 
}

besBYTE_t bes6502CPU_IZX(bes6502CPU_t* __handle)
{
    besBYTE_t t = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    besBYTE_t low = bes6502CPU_read(__handle, (besWORD_t)(t + __handle->X) & 0x00FF);
    besBYTE_t high = bes6502CPU_read(__handle, (besWORD_t)(t + __handle->X + 1) & 0x00FF);

    __handle->addressAbsolute = (high << 8) | low;

    return 0x00; 
}

besBYTE_t bes6502CPU_IZY(bes6502CPU_t* __handle)
{
    besBYTE_t t = bes6502CPU_read(__handle, __handle->PC);
    __handle->PC++;
    besBYTE_t low = bes6502CPU_read(__handle, (besWORD_t)t & 0x00FF);
    besBYTE_t high = bes6502CPU_read(__handle, (besWORD_t)(t + 1) & 0x00FF);

    __handle->addressAbsolute = (high << 8) | low;
    __handle->addressAbsolute += __handle->Y;

    if ((__handle->addressAbsolute & 0xFF) != (high << 8))
        return 0x1;

    return 0x00; 
}

// legal opcodes
besBYTE_t bes6502CPU_ADC(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    besWORD_t temp = (besWORD_t)__handle->A + (besWORD_t)__handle->fetchedData + (besWORD_t)__handle->PSif.C;
    __handle->PSif.C = (temp > 0xFF);
    __handle->PSif.Z = ((temp & 0xFF) == 0);
    __handle->PSif.N = (temp & 0x80);
    __handle->PSif.V = (~(((besWORD_t)__handle->A ^ (besWORD_t)__handle->fetchedData) & ((besWORD_t)__handle->A ^ temp)) & 0x0080);

    __handle->A = (temp & 0xFF);

    return 0x00; 
}

besBYTE_t bes6502CPU_AND(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    __handle->A = __handle->A & __handle->fetchedData;
    __handle->PSif.Z = (__handle->A == 0x00);
    __handle->PSif.N = (__handle->A & 0x00);

    return 0x1; 
}

besBYTE_t bes6502CPU_ASL(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    besWORD_t temp = (besWORD_t) __handle->fetchedData << 1;

    __handle->PSif.C = ((temp & 0xFF00) > 0);
    __handle->PSif.Z = ((temp & 0xFF) == 0x00);
    __handle->PSif.N = (temp & 0x80);

    if (__handle->instructionTable[__handle->opcode].addressMode == &bes6502CPU_IMP)
        __handle->A = temp & 0x00FF;
    else
        bes6502CPU_write(__handle, __handle->addressAbsolute, temp & 0x00FF);

    return 0x00; 
}

besBYTE_t bes6502CPU_BCC(bes6502CPU_t* __handle)
{
    if (__handle->PSif.C == 0)
    {
        __handle->cycles++;
        __handle->addressAbsolute = __handle->PC + __handle->addressRelative;

        if ((__handle->addressAbsolute & 0xFF00) != (__handle->PC & 0xFF00))
            __handle->cycles++;

        __handle->PC = __handle->addressAbsolute;
    }

    return 0x00; 
}

besBYTE_t bes6502CPU_BCS(bes6502CPU_t* __handle)
{
    if (__handle->PSif.C)
    {
        __handle->cycles++;
        __handle->addressAbsolute = __handle->PC + __handle->addressRelative;

        if ((__handle->addressAbsolute & 0xFF00) != (__handle->PC & 0xFF00))
            __handle->cycles++;

        __handle->PC = __handle->addressAbsolute;
    }

    return 0x00; 
}

besBYTE_t bes6502CPU_BEQ(bes6502CPU_t* __handle)
{
    if (__handle->PSif.Z)
    {
        __handle->cycles++;
        __handle->addressAbsolute = __handle->PC + __handle->addressRelative;

        if ((__handle->addressAbsolute & 0xFF00) != (__handle->PC & 0xFF00))
            __handle->cycles++;

        __handle->PC = __handle->addressAbsolute;
    }

    return 0x00; 
}

besBYTE_t bes6502CPU_BIT(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    besWORD_t temp = __handle->A & __handle->fetchedData;

    __handle->PSif.Z = ((temp & 0x00FF) == 0x00);
    __handle->PSif.N = __handle->fetchedData & (1 << 7);
    __handle->PSif.V = __handle->fetchedData & (1 << 6);

    return 0x00; 
}

besBYTE_t bes6502CPU_BMI(bes6502CPU_t* __handle)
{
    if (__handle->PSif.N)
    {
        __handle->cycles++;
        __handle->addressAbsolute = __handle->PC + __handle->addressRelative;

        if ((__handle->addressAbsolute & 0xFF00) != (__handle->PC & 0xFF00))
            __handle->cycles++;

        __handle->PC = __handle->addressAbsolute;
    }

    return 0x00; 
}

besBYTE_t bes6502CPU_BNE(bes6502CPU_t* __handle)
{
    if (__handle->PSif.Z == 0)
    {
        __handle->cycles++;
        __handle->addressAbsolute = __handle->PC + __handle->addressRelative;

        if ((__handle->addressAbsolute & 0xFF00) != (__handle->PC & 0xFF00))
            __handle->cycles++;

        __handle->PC = __handle->addressAbsolute;
    }

    return 0x00; 
}

besBYTE_t bes6502CPU_BPL(bes6502CPU_t* __handle)
{
    if (__handle->PSif.N == 0)
    {
        __handle->cycles++;
        __handle->addressAbsolute = __handle->PC + __handle->addressRelative;

        if ((__handle->addressAbsolute & 0xFF00) != (__handle->PC & 0xFF00))
            __handle->cycles++;

        __handle->PC = __handle->addressAbsolute;
    }

    return 0x00; 
}

besBYTE_t bes6502CPU_BRK(bes6502CPU_t* __handle)
{
    return 0x00; 
}

besBYTE_t bes6502CPU_BVC(bes6502CPU_t* __handle)
{
    if (__handle->PSif.V == 0)
    {
        __handle->cycles++;
        __handle->addressAbsolute = __handle->PC + __handle->addressRelative;

        if ((__handle->addressAbsolute & 0xFF00) != (__handle->PC & 0xFF00))
            __handle->cycles++;

        __handle->PC = __handle->addressAbsolute;
    }

    return 0x00; 
}

besBYTE_t bes6502CPU_BVS(bes6502CPU_t* __handle)
{
    if (__handle->PSif.V)
    {
        __handle->cycles++;
        __handle->addressAbsolute = __handle->PC + __handle->addressRelative;

        if ((__handle->addressAbsolute & 0xFF00) != (__handle->PC & 0xFF00))
            __handle->cycles++;

        __handle->PC = __handle->addressAbsolute;
    }

    return 0x00; 
}

besBYTE_t bes6502CPU_CLC(bes6502CPU_t* __handle)
{
    __handle->PSif.C = 0;
    return 0x00; 
}

besBYTE_t bes6502CPU_CLD(bes6502CPU_t* __handle)
{
    __handle->PSif.D = 0;
    return 0x00; 
}

besBYTE_t bes6502CPU_CLI(bes6502CPU_t* __handle)
{
    __handle->PSif.I = 0;
    return 0x00; 
}

besBYTE_t bes6502CPU_CLV(bes6502CPU_t* __handle)
{
    __handle->PSif.V = 0;
    return 0x00; 
}

besBYTE_t bes6502CPU_CMP(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    besWORD_t temp = (besWORD_t) __handle->A - (besWORD_t)__handle->fetchedData;

    __handle->PSif.C = (__handle->A >= __handle->fetchedData);
    __handle->PSif.Z = ((temp & 0xFF) == 0x0000);
    __handle->PSif.N = (temp & 0x0080);

    return 0x00; 
}

besBYTE_t bes6502CPU_CPX(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    besWORD_t temp = (besWORD_t) __handle->X - (besWORD_t)__handle->fetchedData;

    __handle->PSif.C = (__handle->X >= __handle->fetchedData);
    __handle->PSif.Z = ((temp & 0xFF) == 0x0000);
    __handle->PSif.N = (temp & 0x0080);

    return 0x00; 
}

besBYTE_t bes6502CPU_CPY(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    besWORD_t temp = (besWORD_t) __handle->Y - (besWORD_t)__handle->fetchedData;

    __handle->PSif.C = (__handle->Y >= __handle->fetchedData);
    __handle->PSif.Z = ((temp & 0xFF) == 0x0000);
    __handle->PSif.N = (temp & 0x0080);

    return 0x00; 
}

besBYTE_t bes6502CPU_DEC(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    besWORD_t temp = __handle->fetchedData - 1;

    bes6502CPU_write(__handle, __handle->addressAbsolute, (temp & 0x00FF));

    __handle->PSif.Z = ((temp & 0xFF) == 0x0000);
    __handle->PSif.N = (temp & 0x0080);

    return 0x00; 
}

besBYTE_t bes6502CPU_DEX(bes6502CPU_t* __handle)
{
    __handle->X--;

    __handle->PSif.Z = (__handle->X == 0x0000);
    __handle->PSif.N = (__handle->X & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_DEY(bes6502CPU_t* __handle)
{
    __handle->X--;

    __handle->PSif.Z = (__handle->X == 0x0000);
    __handle->PSif.N = (__handle->X & 0x80);
    
    return 0x00;
}

besBYTE_t bes6502CPU_EOR(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    __handle-> A ^= __handle->fetchedData;

    __handle->PSif.Z = (__handle->A == 0x0000);
    __handle->PSif.N = (__handle->A & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_INC(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    besWORD_t temp = __handle->fetchedData + 1;

    bes6502CPU_write(__handle, __handle->addressAbsolute, (temp & 0x00FF));

    __handle->PSif.Z = ((temp & 0xFF) == 0x0000);
    __handle->PSif.N = (temp & 0x0080);

    return 0x00; 
}

besBYTE_t bes6502CPU_INX(bes6502CPU_t* __handle)
{
    __handle->X++;

    __handle->PSif.Z = (__handle->X == 0x0000);
    __handle->PSif.N = (__handle->X & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_INY(bes6502CPU_t* __handle)
{
    __handle->Y++;

    __handle->PSif.Z = (__handle->Y == 0x0000);
    __handle->PSif.N = (__handle->Y & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_JMP(bes6502CPU_t* __handle)
{
    __handle->PC = __handle->addressAbsolute;

    return 0x00; 
}

besBYTE_t bes6502CPU_JSR(bes6502CPU_t* __handle)
{
    __handle->PC--;

	bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, (__handle->PC >> 8) & 0xFF);
	__handle->SP--;
	bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, __handle->PC & 0xFF);
	__handle->SP--;

	__handle->PC = __handle->addressAbsolute;

    return 0x00; 
}

besBYTE_t bes6502CPU_LDA(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    __handle->A = __handle->fetchedData;

    __handle->PSif.Z = (__handle->A == 0x0000);
    __handle->PSif.N = (__handle->A & 0x80);
    
    return 0x00; 
}

besBYTE_t bes6502CPU_LDX(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    __handle->X = __handle->fetchedData;

    __handle->PSif.Z = (__handle->X == 0x0000);
    __handle->PSif.N = (__handle->X & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_LDY(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    __handle->Y = __handle->fetchedData;

    __handle->PSif.Z = (__handle->Y == 0x0000);
    __handle->PSif.N = (__handle->Y & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_LSR(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    __handle->PSif.C = (__handle->fetchedData & 0x0001);

    besWORD_t temp = (besWORD_t) __handle->fetchedData << 1;

    __handle->PSif.Z = ((temp & 0xFF) == 0x00);
    __handle->PSif.N = (temp & 0x80);

    if (__handle->instructionTable[__handle->opcode].addressMode == &bes6502CPU_IMP)
        __handle->A = temp & 0x00FF;
    else
        bes6502CPU_write(__handle, __handle->addressAbsolute, temp & 0x00FF);

    return 0x00; 
}

besBYTE_t bes6502CPU_NOP(bes6502CPU_t* __handle)
{
    switch (__handle->opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 0x1;
		break;
	}

    return 0x00; 
}

besBYTE_t bes6502CPU_ORA(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
    __handle->A = __handle->A | __handle->fetchedData;

    __handle->PSif.Z = (__handle->A == 0x00);
    __handle->PSif.N = (__handle->A & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_PHA(bes6502CPU_t* __handle)
{
    bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, __handle->A);
    __handle->SP--;

    
    return 0x00; 
}

besBYTE_t bes6502CPU_PHP(bes6502CPU_t* __handle)
{
    bes6502CPU_write(__handle, BES_STACK_BASE_LOCATION + __handle->SP, __handle->PS | __handle->PSif.B | __handle->PSif.u);
	__handle->PSif.B = 0;
	__handle->PSif.u = 0;
	__handle->SP--;

    return 0x00; 
}

besBYTE_t bes6502CPU_PLA(bes6502CPU_t* __handle)
{
    __handle->SP++;
    __handle->A = bes6502CPU_read(__handle, BES_STACK_BASE_LOCATION + __handle->SP);
    __handle->PSif.Z = (__handle->A == 0x00);
    __handle->PSif.N = (__handle->A & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_PLP(bes6502CPU_t* __handle)
{
    __handle->SP++;
    __handle->A = bes6502CPU_read(__handle, BES_STACK_BASE_LOCATION + __handle->SP);
    __handle->PSif.u = 1;

    return 0x00; 
}

besBYTE_t bes6502CPU_ROL(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
	besWORD_t temp = (besWORD_t)(__handle->fetchedData << 1) | __handle->PSif.C;
	__handle->PSif.C = (temp & 0xFF00);
	__handle->PSif.Z = ((temp & 0x00FF) == 0x0000);
	__handle->PSif.N = (temp & 0x80);

	if (__handle->instructionTable[__handle->opcode].addressMode == &bes6502CPU_IMP)
		__handle->A = (temp & 0x00FF);
	else
		bes6502CPU_write(__handle, __handle->addressAbsolute, (temp & 0x00FF));

	return 0x00;
}

besBYTE_t bes6502CPU_ROR(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);
	besWORD_t temp = (besWORD_t) (__handle->PSif.C << 7) | (__handle->fetchedData >> 1);
	__handle->PSif.C = (temp & 0x01);
	__handle->PSif.Z = ((temp & 0x00FF) == 0x00);
	__handle->PSif.N = (temp & 0x80);

	if (__handle->instructionTable[__handle->opcode].addressMode == &bes6502CPU_IMP)
		__handle->A = (temp & 0x00FF);
	else
		bes6502CPU_write(__handle, __handle->addressAbsolute, (temp & 0x00FF));

	return 0x00;

}

besBYTE_t bes6502CPU_RTI(bes6502CPU_t* __handle)
{
    __handle->SP++;
    __handle->PS = bes6502CPU_read(__handle, BES_STACK_BASE_LOCATION + __handle->SP);
    __handle->PS &= ~__handle->PSif.B;
    __handle->PS &= ~__handle->PSif.u;

    __handle->SP++;
    __handle->PC = (besWORD_t) bes6502CPU_read(__handle, BES_STACK_BASE_LOCATION + __handle->SP);
    __handle->SP++;
    __handle->PC |=  (besWORD_t) bes6502CPU_read(__handle, BES_STACK_BASE_LOCATION + __handle->SP) << 8;

    return 0x00; 
}

besBYTE_t bes6502CPU_RTS(bes6502CPU_t* __handle)
{
    __handle->SP++;
    __handle->PC = (besWORD_t) bes6502CPU_read(__handle, BES_STACK_BASE_LOCATION + __handle->SP);
    __handle->SP++;
    __handle->PC |= (besWORD_t) bes6502CPU_read(__handle, BES_STACK_BASE_LOCATION + __handle->SP) << 8;

    return 0x00; 
}

besBYTE_t bes6502CPU_SBC(bes6502CPU_t* __handle)
{
    bes6502CPU_fetch(__handle);

    besWORD_t value = ((besWORD_t)__handle->fetchedData) ^ 0xFF;
    besWORD_t temp = (besWORD_t)__handle->A + value + (besWORD_t)__handle->PSif.C;
    __handle->PSif.C = (temp > 0xFF00);
    __handle->PSif.Z = ((temp & 0xFF) == 0);
    __handle->PSif.N = (temp & 0x80);
    __handle->PSif.V = ((temp ^ (besWORD_t)__handle->A) & (temp ^ value) & 0x0080);

    __handle->A = (temp & 0xFF);

    return 0x00; 
}

besBYTE_t bes6502CPU_SEC(bes6502CPU_t* __handle)
{
    __handle->PSif.C = 1;

    return 0x00; 
}

besBYTE_t bes6502CPU_SED(bes6502CPU_t* __handle)
{
    __handle->PSif.D = 1;

    return 0x00; 
}

besBYTE_t bes6502CPU_SEI(bes6502CPU_t* __handle)
{
    __handle->PSif.I = 1;

    return 0x00; 
}

besBYTE_t bes6502CPU_STA(bes6502CPU_t* __handle)
{
    bes6502CPU_write(__handle, __handle->addressAbsolute, __handle->A);

    return 0x00; 
}

besBYTE_t bes6502CPU_STX(bes6502CPU_t* __handle)
{
    bes6502CPU_write(__handle, __handle->addressAbsolute, __handle->X);

    return 0x00; 
}

besBYTE_t bes6502CPU_STY(bes6502CPU_t* __handle)
{
    bes6502CPU_write(__handle, __handle->addressAbsolute, __handle->Y);

    return 0x00; 
}

besBYTE_t bes6502CPU_TAX(bes6502CPU_t* __handle)
{
    __handle->X = __handle->A;

    __handle->PSif.Z = (__handle->X == 0x00);
    __handle->PSif.N = (__handle->X & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_TAY(bes6502CPU_t* __handle)
{
    __handle->Y = __handle->A;

    __handle->PSif.Z = (__handle->Y == 0x00);
    __handle->PSif.N = (__handle->Y & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_TSX(bes6502CPU_t* __handle)
{
    __handle->X = __handle->SP;

    __handle->PSif.Z = (__handle->X == 0x00);
    __handle->PSif.N = (__handle->X & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_TXA(bes6502CPU_t* __handle)
{
    __handle->A = __handle->X;

    __handle->PSif.Z = (__handle->A == 0x00);
    __handle->PSif.N = (__handle->A & 0x80);

    return 0x00; 
}

besBYTE_t bes6502CPU_TXS(bes6502CPU_t* __handle)
{
    __handle->SP = __handle->X;

    return 0x00; 
}

besBYTE_t bes6502CPU_TYA(bes6502CPU_t* __handle)
{
    __handle->A = __handle->Y;

    __handle->PSif.Z = (__handle->A == 0x00);
    __handle->PSif.N = (__handle->A & 0x80);

    return 0x00; 
}

// illegal opcodes

besBYTE_t bes6502CPU_XXX(bes6502CPU_t* __handle)
{
    return 0x00; 
}