#include "registers.h"
#include "timer.h"

 void init_timer(void)
 {
    // Enable TIM2 clock 
    RCC_APB1ENR |= (1 << 0);

    TIM2_PSC = 15999;

    TIM2_ARR = 1999;

    // To update Prescaler and APR values immediatly. otherwise there is no need here.

    TIM2_EGR |= (1 << 0);

    // It will enable interrupt from hardware side.

    TIM2_DIER |= (1 << 0);

    // Enable TIM2 interrupt in NVIC

    NVIC_ISER0 |= (1 << 28);  //TIM2 interrupt is at position 28 in NVIC

    //start the timer counter
    TIM2_CR1 |= (1 << 0);

 }

     /* ---------------- TIMER CONFIG ---------------- */

    /*
       Timer clock = 16 MHz

       PSC = 15999
       Counter clock = 1000 Hz

       1 count = 1 ms

       ARR = 1999

       Overflow = 2000 ms = 2 sec
    */
