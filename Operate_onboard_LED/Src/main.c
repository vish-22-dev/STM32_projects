/**
 * @file main.c
 * @brief Onboard LED Control using GPIO
 * 
 * This program demonstrates GPIO configuration on STM32F446RE microcontroller.
 * It configures GPIOA Pin 5 (PA5) as output for controlling an onboard LED, and GPIOB Pin 3 (PB3)
 * as input with pull-down. The LED is toggled based on the input pin 3 state:
 * - When PB3 goes HIGH, LED turns ON (PA5 goes HIGH)
 * - When PB3 goes LOW, LED turns OFF (PA5 goes LOW)
 * 
 * Hardware Connections:
 * - PA5: Connected to onboard LED
 * - PB3: Input pin (3.3V or GND for testing)
 * 
 * Registers Used:
 * - RCC PCLKR (0x40023830): Enable clock for GPIO ports
 * - GPIOx MODER: Configure pin mode (input/output)
 * - GPIOx PUPDR: Configure pull-up/pull-down
 * - GPIOx ODR: Output data register (write LED state)
 * - GPIOx IDR: Input data register (read pin state)
 */

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
    uint32_t* PCLKR = (uint32_t*)0x40023830;
    uint32_t* PMODER_A = (uint32_t*)0x40020000;
    uint32_t* PMODER_B = (uint32_t*)0x40020400;
    uint32_t* PODR_A = (uint32_t*)0x40020014;
    uint32_t* PIDR_B = (uint32_t*)0x40020410;
    uint32_t* PPUPDR_B = (uint32_t*)0x4002040C;


    *PCLKR |=(1<<0);	//make port A enable
    *PCLKR |=(1<<1);	//make port B enable

    *PMODER_A &= ~(3<<(5*2)); //reset the 10th bit MODER A register
    *PMODER_A |= (1<<(5*2)); // Set the 10th bit of MODER A register

    *PMODER_B &= ~(3<<(3*2)); // It set PB3 as input pin

    *PPUPDR_B &= ~(3<<(3*2));
    *PPUPDR_B |= (2<<(3*2));    // for PB3, Pull down is enabled

    while(1)
    {
    	if(*PIDR_B & (1<<3))
		{
    		*PODR_A |= (1<<5);   // LED ON
		}
    	else
    	{
				*PODR_A &= ~(1<<5);  // LED OFF
    	}
    }
}
