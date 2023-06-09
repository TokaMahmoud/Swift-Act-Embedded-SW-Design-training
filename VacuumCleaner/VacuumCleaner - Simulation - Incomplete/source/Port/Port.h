#ifndef __PORT_H__
#define __PORT_H__

#include "../Main/main.h"

// Led pin
#define DUST_LED_PORT            (GPIOA)
#define DUST_LED_PIN             (LL_GPIO_PIN_5)

#define DUST_SW_PORT             (GPIOC)
#define DUST_SW_PIN              (LL_GPIO_PIN_13)

#define PLUS_SW_PORT             (GPIOA)
#define PLUS_SW_PIN              (LL_GPIO_PIN_6)

#define MINUS_SW_PORT            (GPIOA)
#define MINUS_SW_PIN             (LL_GPIO_PIN_7)

// UART Pins
#define USART_TX_PORT            (GPIOA)
#define USART_TX_PIN             (LL_GPIO_PIN_2)
#define USART_RX_PORT            (GPIOA)
#define USART_RX_PIN             (LL_GPIO_PIN_3)

#define MOTOR_PORT               (GPIOA)
#define MOTOR_PIN                (LL_GPIO_PIN_8)


#if 0
/* Fill missing code below */
/* Switches */
#define SW_PLUS_PORT_DR     (GPIO_PORTB_DATA)
#define SW_PLUS_PORT_CR     (GPIO_PORTB_CONTROL)
#define SW_PLUS_PIN         (GPIO_PIN_1)

#define SW_MINUS_PORT_DR    (GPIO_PORTB_DATA)
#define SW_MINUS_PORT_CR    (GPIO_PORTB_CONTROL)
#define SW_MINUS_PIN        (GPIO_PIN_0)


/* SSD */
#define SSD_DATA_PORT_DR        (GPIO_PORTD_DATA)
#define SSD_DATA_PORT_CR        (GPIO_PORTD_CONTROL)

#define SSD_LOW_DR       (GPIO_PORTB_DATA)
#define SSD_LOW_CR       (GPIO_PORTB_CONTROL)
#define SSD_LOW_PIN      (GPIO_PIN_7)

#define SSD_MEDIUM_DR      (GPIO_PORTB_DATA)
#define SSD_MEDIUM_CR      (GPIO_PORTB_CONTROL)
#define SSD_MEDIUM_PIN     (GPIO_PIN_6)

#define SSD_HIGH_DR     (GPIO_PORTB_DATA)
#define SSD_HIGH_CR     (GPIO_PORTB_CONTROL)
#define SSD_HIGH_PIN    (GPIO_PIN_5)

/* MOTOR */
#define MOTOR_DR       (GPIO_PORTC_DATA)
#define MOTOR_CR       (GPIO_PORTC_CONTROL)
#define MOTOR_PIN      (GPIO_PIN_7)
#endif

#endif // __PORT_H__
