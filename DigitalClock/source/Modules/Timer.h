#ifndef __TIMER_H__
#define __TIMER_H__

#include "../Main/main.h"

#define TMR_TICK_MS				(20)   // HCF(P1, P2, ..., PN)

void TMR_Init(void);
void TMR_Start(void);
void TMR_Stop(void);
void SysTick_Handler(void);

#endif // __TIMER_H__
