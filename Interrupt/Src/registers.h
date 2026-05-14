#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

/* ---------------- RCC REGISTERS ---------------- */

#define RCC_AHB1ENR      (*(volatile uint32_t*)0x40023830)
#define RCC_APB1ENR      (*(volatile uint32_t*)0x40023840)

/* ---------------- GPIOA REGISTERS ---------------- */

#define GPIOA_MODER      (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR        (*(volatile uint32_t*)0x40020014)

/* ---------------- TIM2 REGISTERS ---------------- */

#define TIM2_CR1         (*(volatile uint32_t*)0x40000000)
#define TIM2_DIER        (*(volatile uint32_t*)0x4000000C)
#define TIM2_SR          (*(volatile uint32_t*)0x40000010)
#define TIM2_EGR         (*(volatile uint32_t*)0x40000014)
#define TIM2_PSC         (*(volatile uint32_t*)0x40000028)
#define TIM2_ARR         (*(volatile uint32_t*)0x4000002C)

/* ---------------- NVIC REGISTERS ---------------- */

#define NVIC_ISER0       (*(volatile uint32_t*)0xE000E100)

#endif