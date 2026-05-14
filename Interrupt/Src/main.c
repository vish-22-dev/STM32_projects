#include "registers.h"
#include "led.h"
#include "timer.h"

int main(void)
{
    init_timer();
    init_led();
    while(1);
    
}

void TIM2_IRQHandler(void)
{
    /* Check UIF flag */

    if(TIM2_SR & (1 << 0))
    {
        /* Clear UIF flag */

        TIM2_SR &= ~(1 << 0);

        toggle_led();
    }
}