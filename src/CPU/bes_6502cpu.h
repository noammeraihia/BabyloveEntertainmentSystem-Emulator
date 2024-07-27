#ifndef BES_6502CPU_h
#define BES_6502CPU_h

#include <stdio.h>
#include <stdlib.h>

#include "bes_types.h"
#include "CPU/bes_6502cpu_common.h"
#include "bes_6502cpu_instructions.h"

bes6502CPU_t bes6502CPU_create();

uint8_t bes6502CPU_connectBus(bes6502CPU_t* __handle, besBus_t* __bus);
besBYTE_t bes6502CPU_read(bes6502CPU_t* __handle, besWORD_t __address);
uint8_t bes6502CPU_write(bes6502CPU_t* __handle, besWORD_t __address, besBYTE_t __data);

// other CPU funcs

void bes6502CPU_clock(bes6502CPU_t* __handle);
void bes6502CPU_reset(bes6502CPU_t* __handle);
void bes6502CPU_irq(bes6502CPU_t* __handle);
void bes6502CPU_nmi(bes6502CPU_t* __handle);

void bes6502CPU_fetch(bes6502CPU_t* __handle);

besBus_t besBus_create(bes6502CPU_t* __cpu);

uint8_t besBus_write(besBus_t* __handle, besWORD_t __address, besBYTE_t __data);
besBYTE_t besBus_read(besBus_t* __handle, besWORD_t __address, bool __readOnly);

#endif