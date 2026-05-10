#include <stdint.h>

#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000
#define USART2_BASE     0x40004400

/* RCC Registers */
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x40))

/* GPIOA Registers */
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL      (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

/* USART2 Registers */
#define USART2_SR       (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR       (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR      (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1      (*(volatile uint32_t *)(USART2_BASE + 0x0C))

void USART2_Init(void);
void USART2_WriteChar(char ch);
void USART2_WriteString(char *str);

int main(void)
{
    USART2_Init();

    for(int i=0; i<1; i++)
    {
        USART2_WriteString("Hey Guys\r\n");
        USART2_WriteString("We are using UART Communication on STM32 \r\n");

        for(volatile int i = 0; i < 500000; i++); // Delay
    }
}

void USART2_Init(void)
{
    /* Enable GPIOA clock */
    RCC_AHB1ENR |= (1 << 0);

    /* Enable USART2 clock */
    RCC_APB1ENR |= (1 << 17);

    /* Set PA2 and PA3 to Alternate Function mode */
    GPIOA_MODER &= ~(0xF << 4);
    GPIOA_MODER |=  (0xA << 4);

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

    /* Enable USART */
    USART2_CR1 |= (1 << 13);
}

void USART2_WriteChar(char ch)
{
    /* Wait until TX buffer empty */
    while(!(USART2_SR & (1 << 7)));

    USART2_DR = ch;
}

void USART2_WriteString(char *str)
{
    while(*str)
    {
        USART2_WriteChar(*str++);
    }
}
