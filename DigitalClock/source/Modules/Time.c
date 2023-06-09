#include "../Main/main.h"
#include "../Modules/SW.h"
#include "../Modules/Timer.h"
#include "../Modules/Time.h"
#include "../Modules/Uart.h"
#include "../Modules/Display.h"

#if SIM == 1
#include "stdio.h"
#endif

#define TIM_PERIOD_MS   (20)
#define TIM_SECOND_MS   (1000)

// For debugging only (For logic analyzer)
volatile uint32_t second = 0;

static void TIM_UpdateTime(void);

static tTIM_Time TIM_CurrentTime = {0, 0, 0};
static tTIM_State TIM_State = TIM_NORMAL;

void TIM_Init(void)
{
    TIM_CurrentTime.seconds = 0;
    TIM_CurrentTime.minutes = 0;
    TIM_CurrentTime.hours = 0;
   
   TIM_State = TIM_NORMAL;
}

void TIM_Update(void)
{
   static tWord TIM_counter = 0;
   static tWord TIM_seconds_counter = 0;

   // Check if it is time for the TIM_Update to run
   TIM_counter += TMR_TICK_MS;

   if (TIM_counter != TIM_PERIOD_MS)
   {
      return;
   }
   TIM_counter = 0;

   switch (TIM_State)
   {
      case TIM_NORMAL:
      {
         if (SW_GetState(SW_SET) == (SW_PRE_PRESSED))
         {
            printf("Please, Set Hours ...\n");         
            printf("Use 'UP' and 'DOWN' arrows\n");
            printf("Press on 's' to set minutes\n         ");
            UART_Send_String("Please, Set Hours ...\n");         
            UART_Send_String("Use 'UP' and 'DOWN' arrows\n");
            UART_Send_String("Press on 's' to set minutes\n         ");
            
            DISP_Display_Time(&TIM_CurrentTime);
            TIM_State = TIM_SET_HOURS;
            TIM_seconds_counter = 0;
         }
         else
         {
            TIM_seconds_counter += TIM_PERIOD_MS;
            if (TIM_seconds_counter == TIM_SECOND_MS)
            {
               // For debugging only (For logic analyzer)
               second ^= 1;
               
               TIM_seconds_counter = 0;
               TIM_UpdateTime();
            }
         }
         break;
      }
      
      case TIM_SET_HOURS:
      {         
         if (SW_GetState(SW_SET) == SW_PRE_PRESSED)
         {
            
            printf("Please, Set Minutes ...\n");         
            printf("Use 'UP' and 'DOWN' arrows\n");
            printf("Press on 's' to run the clock\n         "); 
            UART_Send_String("Please, Set Minutes ...\n");         
            UART_Send_String("Use 'UP' and 'DOWN' arrows\n");
            UART_Send_String("Press on 's' to run the clock\n         ");            
            
            DISP_Display_Time(&TIM_CurrentTime);
            TIM_State = TIM_SET_MINUTES;
            TIM_seconds_counter = 0;
         }
         else if (SW_GetState(SW_PLUS) == SW_PRE_PRESSED)
         {
            TIM_CurrentTime.hours ++;
            if (TIM_CurrentTime.hours == 24)
            {
               TIM_CurrentTime.hours = 0;
            }
         }
         else if (SW_GetState(SW_MINUS) == SW_PRE_PRESSED)
         {
            TIM_CurrentTime.hours --;
            if (TIM_CurrentTime.hours == 255)
            {
               TIM_CurrentTime.hours = 23;
            }
         }
         else
         {
            // Do nothing
         }
         break;
      }
      
      case TIM_SET_MINUTES:
      {
         if (SW_GetState(SW_SET) == SW_PRE_PRESSED)
         {
            
            printf("Clock is running ...\n");         
            printf("Press on 's' to set the clock\n         ");
            UART_Send_String("Clock is running ...\n");         
            UART_Send_String("Press on 's' to set the clock\n         ");

            DISP_Display_Time(&TIM_CurrentTime);
            TIM_State = TIM_NORMAL;
            TIM_seconds_counter = 0;
         }
         else if (SW_GetState(SW_PLUS) == SW_PRE_PRESSED)
         {
            TIM_CurrentTime.minutes ++;
            if (TIM_CurrentTime.minutes == 60)
            {
               TIM_CurrentTime.minutes = 0;
            }
         }
         else if (SW_GetState(SW_MINUS) == SW_PRE_PRESSED)
         {
            TIM_CurrentTime.minutes --;
            if (TIM_CurrentTime.minutes == 255)
            {
               TIM_CurrentTime.minutes = 59;
            }
         }
         else
         {
            // Do nothing
         }
         break;
      }
   }
}

void TIM_GetTime(tTIM_Time * time)
{
   time->seconds = TIM_CurrentTime.seconds;
   time->minutes = TIM_CurrentTime.minutes;
   time->hours = TIM_CurrentTime.hours;
}

// Compares Hours and minutes only
tByte TIM_CompareTime(tTIM_Time * first, tTIM_Time * second)
{
   tByte ret = 1;
   if ((first -> minutes == second->minutes) &&
     (first -> hours == second->hours))
   {
     ret = 0;
   }
   return ret;
}

tTIM_State TIM_GetState(void)
{
    return TIM_State;
}

void TIM_CopyTime(tTIM_Time * dest, tTIM_Time * src)
{
   dest -> seconds = src->seconds;
   dest -> minutes = src->minutes;
   dest -> hours = src->hours;
}

static void TIM_UpdateTime(void)
{
   TIM_CurrentTime.seconds ++;
   if (TIM_CurrentTime.seconds == 60)
   {
      TIM_CurrentTime.seconds = 0;
      TIM_CurrentTime.minutes++;
      if (TIM_CurrentTime.minutes == 60)
      {
         TIM_CurrentTime.minutes = 0;
         TIM_CurrentTime.hours++;
         if (TIM_CurrentTime.hours == 24)
         {
            TIM_CurrentTime.hours = 0;
         }
      }
   }
}
