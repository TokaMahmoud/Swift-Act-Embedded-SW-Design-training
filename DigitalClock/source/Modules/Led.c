#include "../Main/main.h"
#include "../Port/Port.h"
#include "../Modules/Led.h"
#include "stm32f4xx_ll_gpio.h"

#define LED_PERIOD_MS (1000)

// For debugging only (For logic analyzer)
volatile uint32_t task_led_et = 0;

void LED_Init(void)
{
   // Enable peripheral clock 
   LED_ENABLE_CLOCK;
   
   LL_GPIO_InitTypeDef SW_GPIO;
   SW_GPIO.Pin        = LED_PIN;
   SW_GPIO.Mode       = LL_GPIO_MODE_OUTPUT;
   SW_GPIO.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
   SW_GPIO.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
   SW_GPIO.Pull       = LL_GPIO_PULL_NO;
   SW_GPIO.Alternate  = LL_GPIO_AF_0;
   LL_GPIO_Init(LED_PORT,&SW_GPIO);
}

void LED_Update(void)
{
   static uint16_t count = 0;
   if(++count == LED_PERIOD_MS)
   {
      task_led_et = 1;
      count = 0;
      LED_Toggle();
		task_led_et = 0;
   }
}

void LED_Toggle(void)
{
   // Toggle led
   if (LED_GetState() == LED_ON)
   {
      LED_SetState(LED_OFF);
   }
   else
   {
      LED_SetState(LED_ON);
   }
}


void LED_SetState(tLED_State state)
{
   if(state == LED_ON)
   {
      LL_GPIO_SetOutputPin(LED_PORT,LED_PIN);
   }
   else if(state == LED_OFF)
   {
      LL_GPIO_ResetOutputPin(LED_PORT,LED_PIN);
   }
   else
   {
      // Should not be here ...
   }
}

tLED_State LED_GetState(void)
{
   tLED_State ret = LED_OFF;
   if((LL_GPIO_ReadOutputPort(LED_PORT) & LED_PIN) == 0)
   {
      ret = LED_OFF;
   }
   else
   {
      ret = LED_ON;
   }
   return ret;
}
