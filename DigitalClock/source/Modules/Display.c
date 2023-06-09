#include "../Main/main.h"
#include "../Port/Port.h"
#include "../Modules/Timer.h"
#include "../Modules/Time.h"
#include "../Modules/Display.h"
#include "../Modules/SW.h"
#include "../Modules/Uart.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_usart.h"

#if SIM == 1
#include "stdio.h"
#endif

// DISP_Update period and Clock update period
#define DISP_PERIOD_MS   (20)
#define DISP_NORMAL_PERIOD_MS   (1000)

static char time[9];

void DISP_Init(void)
{
   uint8_t i = 0;
   tTIM_Time TIM_Time;
   
   for (i = 0; i < 8; i++)
   {
      time[i] = 0;
   }
   
   time[2] = ':';
   time[5] = ':';
   time[8] = 0;

   printf("BEAT THE CLOCK\n");
   printf("Clock is running ...\n");         
   printf("Press on 's' to set the clock\n         ");
   UART_Send_String("BEAT THE CLOCK\n");
   UART_Send_String("Clock is running ...\n");         
   UART_Send_String("Press on 's' to set the clock\n         ");
   
   TIM_GetTime(&TIM_Time);
   DISP_Display_Time(&TIM_Time);
}

void DISP_Update(void)
{
   static tWord DISP_counter = 0;
   static tWord DISP_NORMAL_counter = 0;
   static tTIM_Time TIM_Time;
   
   // Check if it is time for DISP_Update to run
   DISP_counter += TMR_TICK_MS;

   if (DISP_counter != DISP_PERIOD_MS)
   {
      return;
   }
   DISP_counter = 0;

   switch(TIM_GetState())
   {
      case TIM_NORMAL:
      {
         // Check if it is time for Updating the clock
         DISP_NORMAL_counter += DISP_PERIOD_MS;

         if (DISP_NORMAL_counter != DISP_NORMAL_PERIOD_MS)
         {
            return;
         }
         DISP_NORMAL_counter = 0;
         
         TIM_GetTime(&TIM_Time);
         DISP_Display_Time(&TIM_Time);
         
         break;
      }
      
      case TIM_SET_HOURS:
      {
         static tByte Old_Hours = 0;
         TIM_GetTime(&TIM_Time);
         
         // If no arrow is pressed, do nothing now
         if(Old_Hours == TIM_Time.hours)
         {
            // Do not re-display if no
            // button is pressed
            break;
         }

         Old_Hours = TIM_Time.hours;
         DISP_Display_Time(&TIM_Time);
         
         break;
      }
      
      case TIM_SET_MINUTES:
      {
         static tByte Old_Minutes = 0;
         TIM_GetTime(&TIM_Time);
         
         // If no arrow is pressed, do nothing now
         if(Old_Minutes == TIM_Time.minutes)
         {
            // Do not re-display if no
            // button is pressed
            break;
         }

         Old_Minutes = TIM_Time.minutes;
         DISP_Display_Time(&TIM_Time);
         
         break;
      }
   }
}

void DISP_Display_Time(tTIM_Time* TIM_Time)
{
   time[7] = (TIM_Time->seconds % 10) + 48;
   time[6] = (TIM_Time->seconds / 10) + 48;

   time[4] = (TIM_Time->minutes % 10) + 48;
   time[3] = (TIM_Time->minutes / 10) + 48;

   time[1] = (TIM_Time->hours % 10) + 48;
   time[0] = (TIM_Time->hours / 10) + 48;
   
   
   printf("\b\b\b\b\b\b\b\b\b");
   printf("%s",time);
   printf("\n");
   UART_Send_String("\b\b\b\b\b\b\b\b\b");
   UART_Send_String(time);
   UART_Send('\n');
}
