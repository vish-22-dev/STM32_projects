#include <stdint.h>
#include "registers.h"
#include "uart.h"

void init_uart(void)
{
    /* Set PA2 and PA3 to Alternate Function mode */
    GPIOA_MODER &= ~(0xF << 4);
    GPIOA_MODER |=  (0xA << 4);

    // For receiving data from pin3 make it pull-up to avoid floating state
    GPIOA_PUPDR &= ~(0x3 << 6);
    GPIOA_PUPDR |=  (0x1 << 6);

    /* Set AF7 for USART2 */
    GPIOA_AFRL &= ~(0xFF << 8);
    GPIOA_AFRL |=  (0x77 << 8);

    /*
      Baud Rate Calculation

      Assuming:
      APB1 Clock = 16 MHz

      Baud Rate = 9600

      USARTDIV = 16000000 / (16 * 9600)
                = 104.166

      BRR = 0x0683
    */

    USART2_BRR = 0x0683;

    /* Enable Transmitter */
    USART2_CR1 |= (1 << 3);

    // Enable Receiver
    USART2_CR1 |= (1 << 2);

    /* Enable USART */
    USART2_CR1 |= (1 << 13);

}

char read_uart_char(void)
{
    while(!(USART2_SR & (1 << 5))); // RXNE

    return USART2_DR;
}

void write_uart_char (char ch)
{
    /* Wait until TX buffer empty */
    while(!(USART2_SR & (1 << 7)));
    USART2_DR = ch;
}

void read_uart_string(char *buffer, uint32_t max_length)
{
    uint32_t i = 0;
    char ch;

    while(i < (max_length - 1))
    {
        ch = read_uart_char();

        if(ch == '\r' || ch == '\n')
        {
            break;
        }

        buffer[i++] = ch;

        write_uart_char(ch); // echo
    }

    buffer[i] = '\0';
}

void write_uart_string (char *str)
{
    while(*str)
    {
        write_uart_char(*str++);
    }
}

