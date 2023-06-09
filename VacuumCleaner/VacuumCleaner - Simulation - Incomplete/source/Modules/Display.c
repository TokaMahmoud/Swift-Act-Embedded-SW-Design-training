#include "../Main/main.h"
#include "../Modules/Timer.h"
#include "../Modules/Display.h"
#include "../Modules/SW.h"
#include "../Modules/Led.h"
#include "../Modules/VC.h"
#include "../Modules/Uart.h"
#include "stdio.h"

/* SSD_Update period */
#define DISP_PERIOD_MS   (20)

tWord speed = SPEED_LOW;

void DISP_Init(void)
{
   #if 0
    //SSD Initialization
    SSD_Init(SSD_LOW);
    SSD_Init(SSD_MEDIUM);
    SSD_Init(SSD_HIGH);

    SSD_SetValue(SSD_LOW, SSD_SINGLE);
    SSD_SetValue(SSD_MEDIUM,SSD_DOUBLE);
    SSD_SetValue(SSD_HIGH, SSD_TRIPLE);

    //Led Initialization
    LED_Init(LED_DUST,LED_OFF);
   #endif
   
   //Uart Initialization
   UART_Init();
   
   //Led Initialization
   LED_Init(LED_DUST,LED_OFF);
}

void DISP_Update(void)
{
   #if 1
    static tWord DISP_counter = 0;

    /* Check if it is time for the DISP_Update to run */
    DISP_counter += TMR_TICK_MS;

    if (DISP_counter != DISP_PERIOD_MS)
    {
        return;
    }
    DISP_counter = 0;

    //Determine the last SSD should be displayed
    switch(VC_GetSpeed())
    {
        case SPEED_LOW:
            //SSD_SetCurrentLevel(SSD_LOW);
            if(speed != SPEED_LOW)
            {
               printf("LOW\n");
               UART_Send_String("\nLOW");
               speed = SPEED_LOW;
            }
            break;
        case SPEED_MEDIUM:
            //SSD_SetCurrentLevel(SSD_MEDIUM);
            
            if(speed != SPEED_MEDIUM)
            {
               printf("MEDIUM\n");
               UART_Send_String("\nMEDIUM");
               speed = SPEED_MEDIUM;
            }
            break;
        case SPEED_HIGH:
            //SSD_SetCurrentLevel(SSD_HIGH);
            
            if(speed != SPEED_HIGH)
            {
               printf("HIGH\n");
               UART_Send_String("\nHIGH");
               speed = SPEED_HIGH;
            }
            break;
    }

    //Illuminate the LED when the dust sensor is HIGH
    if(SW_GetState(SW_DUST) == SW_PRESSED){
        LED_SetState(LED_DUST,LED_ON);
    }else{
        LED_SetState(LED_DUST,LED_OFF);
    }

   #endif
   
}
