#include "6502cpu.h"

/* BES 6502 CPU funcs */

bes6502CPU_t bes6502CPU_create()
{
    bes6502CPU_t _cpu = {
        .bus = NULL
    };
}

uint8_t bes6502CPU_connectBus(bes6502CPU_t __handle, besBus_t* __bus)
{   
    if (__bus)
    {
        __handle->bus = __bus;

        return BES_U8SUCCESS;
    }

    return BES_U8FAILURE;
}   

besBYTE_t bes6502CPU_read(bes6502CPU_t* __handle, besWORD_t __address)
{
    return besBus_read(__handle->bus, __address, 0);
}

uint8_t bes6502CPU_write(bes6502CPU_t* __handle, besWORD_t __address, besBYTE_t __data)
{
    return besBus_write(__handle->bus, __address, __data);
}

/* BES BUS funcs */

besBus_t besBus_create(bes6502CPU_t* __cpu) 
{ 
    besBus_t _bus = {.cpu = __cpu, .ram = {0x00}}; 
    bes6502CPU_connectBus(_bus.cpu, &_bus);
}

uint8_t besBus_write(besBus_t* __handle, besWORD_t __address, besBYTE_t __data) 
{
    if (__address >= 0x0000 && __address <= 0xFFFF)
    {
        __handle->ram[__address] = __data;

        return BES_U8SUCCESS;
    }

    return BES_U8FAILURE;
}

besBYTE_t besBus_read(besBus_t* __handle, besWORD_t __address, bool __readOnly)
{
    if (__address >= 0x0000 && __address <= 0xFFFF)
        return __handle->ram[__address]; 

    return BES_U8FAILURE;
}