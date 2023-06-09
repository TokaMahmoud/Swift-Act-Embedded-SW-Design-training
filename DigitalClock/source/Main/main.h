#ifndef __MAIN_H__
#define __MAIN_H__

#include <stm32f411xe.h>

// Clock Enabling Macros
#define LED_ENABLE_CLOCK         (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define USART_ENABLE_CLOCK       (RCC->APB1ENR |= RCC_APB1ENR_USART2EN)
#define SET_SW_ENABLE_CLOCK      (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN)
#define PLUS_SW_ENABLE_CLOCK     (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define MINUS_SW_ENABLE_CLOCK    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)

/* Standard data types */
typedef unsigned char tByte;
typedef unsigned int tWord;

#endif // __MAIN_H__
