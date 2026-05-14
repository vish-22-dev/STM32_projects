#include "registers.h"
#include "led.h"

void init_led(void)
{
    RCC_AHB1ENR |= (1 << 0);

    // Set PA5 to output mode (01 binary)
    GPIOA_MODER &= ~(3 << (5 * 2));
    GPIOA_MODER |= (1 << (5 * 2));
}

void toggle_led(void)
{
    GPIOA_ODR ^= (1 << 5); // Toggle PA5 to switch LED state
}

