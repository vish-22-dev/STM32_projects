#include "registers.h"
#include "led.h"

void init_led(void)
{
    // Set PA5 to output mode (01 binary)
    GPIOA_MODER &= ~(3 << (5 * 2));
    GPIOA_MODER |= (1 << (5 * 2));
}

void turn_on_led(void)
{
    GPIOA_ODR |= (1 << 5); // Set PA5 high to turn on LED
}

void turn_off_led(void)
{
    GPIOA_ODR &= ~(1 << 5); // Set PA5 low to turn off LED
}