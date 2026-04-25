#include <stdint.h>
void delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++)
    {
    	for(volatile uint32_t j = 0; j < 2000; j++);
    }
}
int main(void)
{
    uint32_t* pclkreg = (uint32_t*)0x40023830;
    uint32_t* pmodeselectreg = (uint32_t*)0x40020000;
    uint32_t* poutputreg = (uint32_t*)0x40020014;

    *pclkreg |= 0x00000001;

    *pmodeselectreg &= 0xFFFFF3FF;
    *pmodeselectreg |= 0x00000400;

    while(1)
    {
        *poutputreg |= 0x20;   // LED ON
        delay_ms(2000);

        *poutputreg &= ~0x20;  // LED OFF
        delay_ms(1000);
    }
}
