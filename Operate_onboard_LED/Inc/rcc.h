/*
 * rcc.h
 *
 *  Created on: 19-Aug-2026
 *      Author: vishal Pandule
 */


#ifndef RCC_H
#define RCC_H

#include <stdint.h>

typedef struct
{
    uint32_t CR;            // 0x00
    uint32_t PLLCFGR;       // 0x04
    uint32_t CFGR;          // 0x08
    uint32_t CIR;           // 0x0C
    uint32_t AHB1RSTR;      // 0x10
    uint32_t AHB2RSTR;      // 0x14
    uint32_t AHB3RSTR;      // 0x18
    uint32_t RESERVED0;     // 0x1C
    uint32_t APB1RSTR;      // 0x20
    uint32_t APB2RSTR;      // 0x24
    uint32_t RESERVED1[2];  // 0x28 - 0x2C
    uint32_t AHB1ENR;       // 0x30
    uint32_t AHB2ENR;       // 0x34
    uint32_t AHB3ENR;       // 0x38
    uint32_t RESERVED2;     // 0x3C
    uint32_t APB1ENR;       // 0x40
    uint32_t APB2ENR;       // 0x44

} RCC_RegDef_t;

#define RCC_BASE_ADDR    0x40023800U

#define RCC    ((RCC_RegDef_t *)RCC_BASE_ADDR)




#endif /* RCC_H */
