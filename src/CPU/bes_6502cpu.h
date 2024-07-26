#ifndef BES_6502CPU_h
#define BES_6502CPU_h

#include <stdio.h>
#include <stdlib.h>

#include "bes_types.h"

#define BES_CPU_MAX_ADDR_MEM 64 * 1024

typedef struct s_6502CPU bes6502CPU_t;
typedef struct s_besBus besBus_t;

struct s_6502CPU {
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
};

bes6502CPU_t bes6502CPU_create();

uint8_t bes6502CPU_connectBus(bes6502CPU_t* __handle, besBus_t* __bus);
besBYTE_t bes6502CPU_read(bes6502CPU_t* __handle, besWORD_t __address);
uint8_t bes6502CPU_write(bes6502CPU_t* __handle, besWORD_t __address, besBYTE_t __data);

struct s_besBus {
    bes6502CPU_t* cpu;
    besBYTE_t ram[BES_CPU_MAX_ADDR_MEM];
};

besBus_t besBus_create(bes6502CPU_t* __cpu);

uint8_t besBus_write(besBus_t* __handle, besWORD_t __address, besBYTE_t __data);
besBYTE_t besBus_read(besBus_t* __handle, besWORD_t __address, bool __readOnly);

#endif BES_6502CPU_h