#include <stdint.h>

int main(void)
{
    uint32_t* pclkreg = (uint32_t*)0x40023830;
    uint32_t* pmodeselectreg = (uint32_t*)0x40020000;
    uint32_t* poutputreg = (uint32_t*)0x40020014;

    *pclkreg |= 0x00000001;

    *pmodeselectreg &= 0xFFFFF3FF;
    *pmodeselectreg |= 0x00000400;

    *poutputreg |= 0x00000020;

    while(1);
}
