#include <string.h>
#include "registers.h"
#include "uart.h"
#include "led.h"

void init_clk (void);

int main(void)
{
    char command[10];
    init_clk();
    init_uart();
    init_led();

    write_uart_string("Welcome to STM32 UART Communication\r\n");
    write_uart_string("UART Communication Initialized\r\n");
    write_uart_string("Enter a command \"ON\" to turn on the LED and \"OFF\" to turn it off\r\n");
    while(1)
    {
        memset(command, 0, sizeof(command));  // Clear the command buffer before reading new input
        read_uart_string(command, sizeof(command));
        if (strcmp(command, "ON") == 0)
        {
            turn_on_led();
            write_uart_string("\nLED is turned ON\r\n");
        }
        else if (strcmp(command, "OFF") == 0)
        {
            turn_off_led();
            write_uart_string("\nLED is turned OFF\r\n");
        }
        else
        {
            write_uart_string("\nInvalid command. Please enter \"ON\" or \"OFF\"\r\n");
        }
   }
}

void init_clk (void)
{
    // Enable GPIOA clock
    RCC_AHB1ENR |= (1 << 0);
    // Enable USART2 clock
    RCC_APB1ENR |= (1 << 17);
}
