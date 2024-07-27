#include "core/CPU/bes_6502cpu_common.h"

besBYTE_t bes6502CPU_getFlag(bes6502CPU_t *__handle, bes6502PSFlags_t __flag)
{
    return ((__handle->PS & __flag) > 0);
}

void bes6502CPU_setFlag(bes6502CPU_t *__handle, bes6502PSFlags_t __flag, besWORD_t __value)
{
    if (__value)
        __handle->PS |= __flag;
    else
        __handle->PS &= ~__flag;
}