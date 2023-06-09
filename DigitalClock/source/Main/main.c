#include "main.h"
#include "../Modules/SW.h"
#include "../Modules/Timer.h"
#include "../Modules/Time.h"
#include "../Modules/Display.h"
#include "../Modules/Uart.h"

int main (void)
{
   /* Bootloader */
   
   /* Modules Initialization */
   UART_Init();
   SW_Init();
   TIM_Init();
   DISP_Init();

   /* OS Initialization */
   TMR_Init();
   TMR_Start();

   while (1)
   {
      /* Call Tasks */
      SW_Update();
      TIM_Update();
      DISP_Update();
      
      /* Sleep */
      __WFI();
   }
}

