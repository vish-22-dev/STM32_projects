/*
@file main.c
@brief Onboard LED Control using GPIO

This program demonstrates GPIO configuration on STM32F446RE microcontroller.
It configures GPIOA Pin 5 (PA5) as output for controlling an LED, and GPIOC Pin 13 (PC13)
as input with pull-up for a button. The LED is toggled based on the button state:
- When button is pressed (PC13 goes LOW), LED turns ON (PA5 goes HIGH)
- When button is released (PC13 goes HIGH), LED turns OFF (PA5 goes LOW)

Hardware Connections:
- PA5: Connected to onboard LED
- PC13: Connected to user button with internal pull-up

Registers Used:
- RCC PCLKR (0x40023830): Enable clock for GPIO ports A and C
- GPIOx MODER: Configure pin mode (input/output)
- GPIOx PUPDR: Configure pull-up/pull-down
- GPIOx ODR: Output data register (write LED state)
- GPIOx IDR: Input data register (read button state)
*/

#include <stdint.h>
int main(void)
{
    uint32_t* PCLKR = (uint32_t*)0x40023830;
    uint32_t* PMODER_A = (uint32_t*)0x40020000;
    uint32_t* PMODER_C = (uint32_t*)0x40020800;
    uint32_t* PODR_A = (uint32_t*)0x40020014;
    uint32_t* PIDR_C = (uint32_t*)0x40020810;
    uint32_t* PPUPDR_C = (uint32_t*)0x4002080C;

    *PCLKR |=(1<<0);	//make port A enable
    *PCLKR |=(1<<2);	//make port C enable

    // PA5 ---> Output
    *PMODER_A &= ~(3<<(5*2)); //reset the 10th bit MODER A register
    *PMODER_A |= (1<<(5*2)); // Set the 10th bit of MODER A register

    // PC ----> Input
    *PMODER_C &= ~(3<<(13*2)); // It set PC13 as input pin

    //Pull up
    *PPUPDR_C &= ~(3<<(13*2));
    *PPUPDR_C |= (1<<(13*2));    // for PC13, Pull up is enabled

    while(1)
    {
    	if(!(*PIDR_C & (1<<13)))
		{
    		*PODR_A |= (1<<5);   // LED ON
		}
    	else
    	{
				*PODR_A &= ~(1<<5);  // LED OFF
    	}
    }
}
