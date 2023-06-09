#ifndef __UART_H__
#define __UART_H__

void UART_Init(void);
void UART_Send(char character);
void UART_Send_String(char* string);
void UART_Send_String_Flipped(char* string);
uint8_t UART_Check_RX(void);
char UART_Receive(void);

#endif // __UART_H__
