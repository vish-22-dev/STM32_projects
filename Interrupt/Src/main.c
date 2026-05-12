/**
 * @file main.c
 * @brief Interrupt-driven LED control using external interrupts on STM32F446RE
 * 
 * @details
 * This program demonstrates interrupt handling on the STM32F446RE microcontroller.
 * It implements a button-controlled LED toggle using external interrupts (EXTI).
 * 
 * Hardware Configuration:
 * - PA5: Output pin connected to an LED (toggled on button press)
 * - PC13: Input pin connected to a push button (active low with internal pull-up)
 * 
 * Functionality:
 * - When the button at PC13 is pressed (falling edge), an external interrupt is triggered
 * - The interrupt handler toggles the LED at PA5
 * - Uses NVIC (Nested Vectored Interrupt Controller) for interrupt management
 * 
 * Registers Used:
 * - RCC: Reset and Clock Control (enables clocks for GPIO and SYSCFG)
 * - GPIO: General-Purpose Input/Output configuration and data registers
 * - EXTI: External Interrupt/Event controller (line 13 for PC13)
 * - SYSCFG: System configuration controller (connects external interrupt lines to GPIO pins)
 * - NVIC: Nested Vectored Interrupt Controller (enables interrupts in processor core)
 */

#include <stdint.h>

/* ============================================================
 * Register Definitions for STM32F446RE
 * ============================================================ */

// RCC Registers - Reset and Clock Control
#define RCC_AHB1ENR     (*(volatile uint32_t *)(0x40023830))  // AHB1 Peripheral clock enable register
#define RCC_APB2ENR     (*(volatile uint32_t *)(0x40023844))  // APB2 Peripheral clock enable register

// GPIOA Registers - General-Purpose I/O Port A
#define GPIOA_MODER     (*(volatile uint32_t *)(0x40020000))  // Mode register (configures pin direction)
#define GPIOA_ODR       (*(volatile uint32_t *)(0x40020014))  // Output data register (sets/clears output pins)

// GPIOC Registers - General-Purpose I/O Port C
#define GPIOC_MODER     (*(volatile uint32_t *)(0x40020800))  // Mode register (configures pin direction)
#define GPIOC_PUPDR     (*(volatile uint32_t *)(0x4002080C))  // Pull-up/Pull-down register (internal resistor config)
#define GPIOC_IDR       (*(volatile uint32_t *)(0x40020810))  // Input data register (reads input pin states)

// SYSCFG - System Configuration Controller
#define SYSCFG_EXTICR4 (*(volatile uint32_t*)0x40013814)  // External interrupt configuration register 4 (lines 12-15)

// EXTI Registers - External Interrupt/Event Controller
#define EXTI_IMR       (*(volatile uint32_t*)0x40013C00)  // Interrupt mask register (enables/disables specific lines)
#define EXTI_FTSR      (*(volatile uint32_t*)0x40013C0C)  // Falling trigger selection register (triggers on falling edge)
#define EXTI_PR        (*(volatile uint32_t*)0x40013C14)  // Pending register (indicates pending interrupt, write to clear)

// NVIC - Nested Vectored Interrupt Controller
#define NVIC_ISER1     (*(volatile uint32_t*)0xE000E104)  // Interrupt set-enable register 1 (enables interrupts in core)

// Forward declaration of the external interrupt handler
void EXTI15_10_IRQHandler(void);

int main(void)
{
    // Enable clock for GPIOA (AHB1 peripheral clock enable register, bit 0)
    RCC_AHB1ENR |= (1<<0);
    
    // Enable clock for GPIOC (AHB1 peripheral clock enable register, bit 2)
    RCC_AHB1ENR |= (1<<2);

    // Enable clock for SYSCFG (APB2 peripheral clock enable register, bit 14)
    // SYSCFG is needed to configure external interrupt multiplexing
    RCC_APB2ENR |= (1<<14);

    // Configure PA5 as Output for LED
    // Clear mode bits for PA5 (bits 11:10 in MODER register)
    // Mode 00 = input, 01 = output, 10 = alternate, 11 = analog
    GPIOA_MODER &= ~(3<<(5*2));
    // Set PA5 to output mode (01 binary)
    GPIOA_MODER |= (1<<(5*2));

    // Configure PC13 as Input with Internal Pull-up for Button
    // Clear mode bits for PC13 (bits 27:26 in MODER register)
    // This sets it to input mode (00 binary)
    GPIOC_MODER &= ~(3<<(13*2));
    // Clear pull-up/pull-down bits for PC13 (bits 27:26 in PUPDR register)
    GPIOC_PUPDR &= ~(3<<(13*2));
    // Enable pull-up for PC13 (01 binary in PUPDR)
    // This pulls the pin high when button is not pressed
    GPIOC_PUPDR |= (1<<(13*2));

    // Connect EXTI Line 13 to PC13
    SYSCFG_EXTICR4 &= ~(0xF << 4);
    // Set EXTI13 to use PC13 (0x2 = port C selection)
    SYSCFG_EXTICR4 |= (0x2 << 4);

    // Unmask EXTI line 13 to enable interrupts on this line
    // This allows the interrupt signal to reach the NVIC
    EXTI_IMR |= (1<<13);

    // Configure to trigger on Falling Edge
    EXTI_FTSR |= (1 << 13);

    // Clear any pending interrupts before enabling
    EXTI_PR |= (1 << 13);

    // Enable Interrupt in NVIC
    // EXTI15_10_IRQHandler covers EXTI lines 10-15 (IRQ number 40)
    // In NVIC_ISER1: bit 8 corresponds to IRQ 40 (32 + 8)
    // Setting this bit enables the interrupt in the processor core
    NVIC_ISER1 |= (1 << 8);

    // Wait for Interrupts
    while(1)
    {
  
    }

    return 0;  
}

void EXTI15_10_IRQHandler(void)
{

    if(EXTI_PR & (1 << 13))
    {
        GPIOA_ODR ^= (1 << 5); // Toggle LED on PA5 by XORing the output data register bit

        EXTI_PR |= (1 << 13);
    }
}
