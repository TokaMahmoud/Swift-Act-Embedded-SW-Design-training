#ifndef __MAIN_H__
#define __MAIN_H__

#include <stm32f411xe.h>

// Clock Enabling Macros
#define DUST_LED_ENABLE_CLOCK    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)

#define DUST_SW_ENABLE_CLOCK     (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN)
#define PLUS_SW_ENABLE_CLOCK     (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define MINUS_SW_ENABLE_CLOCK    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define MOTOR_ENABLE_CLOCK       (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)

#define USART_ENABLE_CLOCK       (RCC->APB1ENR |= RCC_APB1ENR_USART2EN)


#if 0
/* GPIO definitions */
/* GPIO Pins */
#define GPIO_PIN_0              (0)
#define GPIO_PIN_1              (1)
#define GPIO_PIN_2              (2)
#define GPIO_PIN_3              (3)
#define GPIO_PIN_4              (4)
#define GPIO_PIN_5              (5)
#define GPIO_PIN_6              (6)
#define GPIO_PIN_7              (7)

/* GPIO Port Registers redefinition */
#define GPIO_PORTA_DATA         (PORTA)
#define GPIO_PORTA_CONTROL      (TRISA)

#define GPIO_PORTB_DATA         (PORTB)
#define GPIO_PORTB_CONTROL      (TRISB)

#define GPIO_PORTC_DATA         (PORTC)
#define GPIO_PORTC_CONTROL      (TRISC)

#define GPIO_PORTD_DATA         (PORTD)
#define GPIO_PORTD_CONTROL      (TRISD)

#define GPIO_PORTE_DATA         (PORTE)
#define GPIO_PORTE_CONTROL      (TRISE)

/* GPIO direction setting */
#define GPIO_OUT                (0)
#define GPIO_IN                 (1)

/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION)   ((CONTROL) = (DIRECTION)?(~GPIO_OUT):(GPIO_OUT))
#define GPIO_WritePort(PORT, DATA)          ((PORT) = (DATA))
#define GPIO_ReadPort(PORT)                 (PORT)

/* GPIO port pin operations */
#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION)   ((CONTROL) = (CONTROL & (~(1 << PIN)))|(DIRECTION << PIN))
#define GPIO_WritePortPin(PORT, PIN, DATA)          ((PORT) = (PORT & (~(1 << PIN)))|(DATA << PIN))
#define GPIO_ReadPortPin(PORT, PIN)                 (((PORT) & (1 << PIN)) >> (PIN))
/* End of code filling */

#endif

/* Timer 0 macros */
/* Fill missing code below */

/* End of code filling */
#define TMR_SET_PRESCALER_256	PS2 = 1;\
								PS1 = 1;\
								PS0 = 1;\
								PSA = 0

#define TMR_GET_FLAG			(TMR0IF)
#define TMR_CLEAR_FLAG			(TMR0IF = 0)

#define TMR_UPDATE_REGISTER(TIME)		(TMR0 = (tDWORD)256 - (tDWORD)((TIME) * 8))

#define TMR_ENABLE_INTERRUPT	(TMR0IE = 1) //to enable the device to generate interrupts
#define GLOBAL_INTERRUPT_ENABLE	(GIE = 1) //to enable the CPU to accept the interrupts

#define TMR_ENABLE_CLOCK		(T0CS = 0)
#define TMR_DISABLE_CLOCK		(T0CS = 1)




/* TIMER1 DIFINITIONS */
#define TMR1_SET_PRESCALER_8    T1CKPS0 = 1;\
                                T1CKPS1 = 1

#define TMR1_GET_FLAG			(TMR1IF)
#define TMR1_CLEAR_FLAG			(TMR1IF = 0)

//#define TMR1_UPDATE_REGISTER(TIME)		(TMR1 = (u16)(65535‬ - ((u32)(TIME) * 250)))
//#define TMR1_UPDATE_REGISTER(TIME)		(TMR1 = 62535)
#define TMR1_UPDATE_REGISTER(ANGLE)		(TMR1L = (tByte)(65536 - (14 * (tDWORD)ANGLE)));\
                                        (TMR1H = (tByte)((65536 - (14 * (tDWORD)ANGLE))>>8))


#define TMR1_ENABLE_INTERRUPT	    (TMR1IE = 1)
#define TMR1_UNMASKED_ENABLE        (PEIE = 1)

#define TMR1_SELECT_INTERNAL		(TMR1CS = 0)
#define TMR1_SELECT_EXTERNAL		(TMR1CS = 1)

#define TMR1_OSC_ENABLE             (T1OSCEN = 1)

#define TMR1_ENABLE_CLOCK (TMR1ON = 1)
#define TMR1_DISABLE_CLOCK (TMR1ON = 0)


/* Standard data types */
typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long int tDWORD;

#endif // __MAIN_H__
