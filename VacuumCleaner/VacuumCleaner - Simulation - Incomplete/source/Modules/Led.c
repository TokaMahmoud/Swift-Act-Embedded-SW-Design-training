#include "../Main/main.h"
#include "../Port/Port.h"
#include "../Modules/Led.h"
#include "stm32f4xx_ll_gpio.h"

void LED_Init(tLED led, tLED_State state)
{
   #if 0
    /* Configure led pins as output */
    GPIO_InitPortPin(LED_DUST_PORT_CR, LED_DUST_PIN, GPIO_OUT);

    /* Set led state */
    LED_SetState(led, state);
   #endif
   
   switch(led)
   {
      case LED_DUST:
         // Enable peripheral clock 
         DUST_LED_ENABLE_CLOCK;
         
         LL_GPIO_InitTypeDef LED_GPIO;
         LED_GPIO.Pin        = DUST_LED_PIN;
         LED_GPIO.Mode       = LL_GPIO_MODE_OUTPUT;
         LED_GPIO.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
         LED_GPIO.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
         LED_GPIO.Pull       = LL_GPIO_PULL_NO;
         LED_GPIO.Alternate  = LL_GPIO_AF_0;
         LL_GPIO_Init(DUST_LED_PORT,&LED_GPIO);
      
         if(state == LED_ON)
         {
            LL_GPIO_SetOutputPin(DUST_LED_PORT,DUST_LED_PIN);
         }
         else if(state == LED_OFF)
         {
            LL_GPIO_ResetOutputPin(DUST_LED_PORT,DUST_LED_PIN);
         }
         else
         {
            // Should not be here
         }
         break;
      default:
         // Should not be here
         break;
   }
   
}

void LED_SetState(tLED led, tLED_State state)
{
   
   #if 0
    /* Set led state */
    if(led == LED_DUST){
        GPIO_WritePortPin(LED_DUST_PORT_DR, LED_DUST_PIN, state);
    }
   #endif
   
   switch(led)
   {
      case LED_DUST:      
         if(state == LED_ON)
         {
            LL_GPIO_SetOutputPin(DUST_LED_PORT,DUST_LED_PIN);
         }
         else if(state == LED_OFF)
         {
            LL_GPIO_ResetOutputPin(DUST_LED_PORT,DUST_LED_PIN);
         }
         else
         {
            // Should not be here
         }
         break;
      default:
         // Should not be here
         break;
   }
   
}

tLED_State LED_GetState(tLED led)
{
   #if 0
    tLED_State ret = LED_OFF;
    if(led == LED_DUST){
        ret = GPIO_ReadPortPin(LED_DUST_PORT_DR, LED_DUST_PIN);
    }
    return ret;
   #endif
   
   
   tLED_State ret = LED_OFF;
   switch(led)
   {
      case LED_DUST:      
         if((LL_GPIO_ReadOutputPort(DUST_LED_PORT) & DUST_LED_PIN) == 0)
         {
            ret = LED_OFF;
         }
         else
         {
            ret = LED_ON;
         }
         break;
      default:
         // Should not be here
         break;
   }
   
   return ret;
}
