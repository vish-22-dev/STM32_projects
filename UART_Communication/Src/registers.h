#ifndef REGISTERS_H
#define REGISTERS_H

/* RCC Registers */
#define RCC_AHB1ENR    (*(volatile unsigned int*)0x40023830)
#define RCC_APB1ENR    (*(volatile unsigned int*)0x40023840)

/* GPIOA Registers */
#define GPIOA_MODER    (*(volatile unsigned int*)0x40020000)
#define GPIOA_PUPDR    (*(volatile unsigned int*)0x4002000C)
#define GPIOA_ODR      (*(volatile unsigned int*)0x40020014)
#define GPIOA_AFRL     (*(volatile unsigned int*)0x40020020)

/* USART2 Registers */
#define USART2_SR      (*(volatile unsigned int*)0x40004400)
#define USART2_DR      (*(volatile unsigned int*)0x40004404)
#define USART2_BRR     (*(volatile unsigned int*)0x40004408)
#define USART2_CR1     (*(volatile unsigned int*)0x4000440C)

#endif