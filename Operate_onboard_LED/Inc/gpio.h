/*
 * gpio.h
 *
 *  Created on: 19-Aug-2026
 *      Author: vishal Pandule
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct
{
    uint32_t MODER;       // 0x00
    uint32_t OTYPER;      // 0x04
    uint32_t OSPEEDR;     // 0x08
    uint32_t PUPDR;       // 0x0C
    uint32_t IDR;         // 0x10
    uint32_t ODR;         // 0x14
    uint32_t BSRR;        // 0x18
    uint32_t LCKR;        // 0x1C
    uint32_t AFR[2];      // 0x20, 0x24
} GPIO_RegDef_t;

#define GPIOA_BASE_ADDR    0x40020000U
#define GPIOC_BASE_ADDR    0x40020800U

#define GPIOA    ((GPIO_RegDef_t *)GPIOA_BASE_ADDR)
#define GPIOC    ((GPIO_RegDef_t *)GPIOC_BASE_ADDR)


#endif /* GPIO_H */
