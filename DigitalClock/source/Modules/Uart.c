#include "../Main/main.h"
#include "../Port/Port.h"
#include "../Modules/Uart.h"
#include "../Modules/Time.h"
#include "../Modules/Timer.h"
#include "../Modules/SW.h"
#include "../Modules/Display.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_usart.h"

void UART_Init(void)
{
   // Enable peripherals clock
   LED_ENABLE_CLOCK;
   USART_ENABLE_CLOCK;
   
   // UART TX pin initialization
   LL_GPIO_InitTypeDef TX_GPIO;
   TX_GPIO.Pin        = USART_TX_PIN;
   TX_GPIO.Mode       = LL_GPIO_MODE_ALTERNATE;
   TX_GPIO.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
   TX_GPIO.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
   TX_GPIO.Pull       = LL_GPIO_PULL_UP;
   TX_GPIO.Alternate  = LL_GPIO_AF_7;
   LL_GPIO_Init(USART_TX_PORT,&TX_GPIO);
   
   // UART RX pin initialization
   LL_GPIO_InitTypeDef RX_GPIO;
   RX_GPIO.Pin        = USART_RX_PIN;
   RX_GPIO.Mode       = LL_GPIO_MODE_ALTERNATE;
   RX_GPIO.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
   RX_GPIO.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
   RX_GPIO.Pull       = LL_GPIO_PULL_NO;
   RX_GPIO.Alternate  = LL_GPIO_AF_7;
   LL_GPIO_Init(USART_RX_PORT,&RX_GPIO);
   
   // UART initialization
   LL_USART_InitTypeDef UART;
   UART.BaudRate            = 9600U;
   UART.DataWidth           = LL_USART_DATAWIDTH_8B;
   UART.StopBits            = LL_USART_STOPBITS_1;
   UART.Parity              = LL_USART_PARITY_NONE ;
   UART.TransferDirection   = LL_USART_DIRECTION_TX_RX;
   UART.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
   UART.OverSampling        = LL_USART_OVERSAMPLING_16;
   LL_USART_Init(USART2,&UART);
   LL_USART_Enable(USART2);
   
   #if SIM == 1
   USART2->SR |= USART_SR_TC;
   #else
   LL_USART_ClearFlag_TC(USART2);
   #endif
}

void UART_Send(char character)
{
   LL_USART_TransmitData8(USART2,character);
   
   #if SIM != 1
   // Wait until transmission is completed
   while(LL_USART_IsActiveFlag_TC(USART2) == 0);
   #endif
}

void UART_Send_String(char* string)
{
   volatile uint32_t i = 0;
   while(string[i] != 0)
      {
         UART_Send(string[i]);
         i++;
      }
}

// Send a string after flipping it
void UART_Send_String_Flipped(char* string)
{
   volatile int32_t i = 0;
   while(string[i] != 0)
   {
      i++;
   }
   i--;
   while(i >= 0)
   {
      UART_Send(string[i]);
      i--;
   }
}

// Check if we received a new byte
uint8_t UART_Check_RX(void)
{
   if(LL_USART_IsActiveFlag_RXNE(USART2) != 0)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

// Return the new received byte
char UART_Receive(void)
{
   return LL_USART_ReceiveData8(USART2);
}

