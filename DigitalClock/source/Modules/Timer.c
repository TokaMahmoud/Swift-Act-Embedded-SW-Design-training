#include "../Main/main.h"
#include "../Modules/Timer.h"
#include "../Modules/SW.h"
#include "../Modules/Time.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "stm32f4xx_ll_tim.h"

// For debugging only (For logic analyzer)
volatile uint32_t tick = 0;

void TMR_Init(void)
{
   // System clock frequency = 16MHz
   // Tick Period = 1ms
   SysTick_Config(16*TMR_TICK_MS*1000);
   TMR_Stop();
}
void TMR_Start(void)
{
   SysTick->CTRL |= (0x03);
}

void TMR_Stop(void)
{
   SysTick->CTRL &= ~(0x03);
}

void SysTick_Handler(void)
{
   // For debugging only (For logic analyzer)
   tick ^= 1;
   
   // Do nothing
   // It is made only to wake the cpu up
}

