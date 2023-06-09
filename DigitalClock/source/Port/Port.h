#ifndef __PORT_H__
#define __PORT_H__

#include "../Main/main.h"

// Led pin
#define LED_PORT           (GPIOA)
#define LED_PIN            (LL_GPIO_PIN_5)

#define SET_SW_PORT        (GPIOC)
#define SET_SW_PIN         (LL_GPIO_PIN_13)

#define PLUS_SW_PORT       (GPIOA)
#define PLUS_SW_PIN        (LL_GPIO_PIN_6)

#define MINUS_SW_PORT      (GPIOA)
#define MINUS_SW_PIN       (LL_GPIO_PIN_7)

// UART Pins
#define USART_TX_PORT      (GPIOA)
#define USART_TX_PIN       (LL_GPIO_PIN_2)
#define USART_RX_PORT      (GPIOA)
#define USART_RX_PIN       (LL_GPIO_PIN_3)

#endif // __PORT_H__
