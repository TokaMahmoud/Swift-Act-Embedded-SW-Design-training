#ifndef __LED_H__
#define __LED_H__

typedef enum
{
   LED_OFF = 0,
   LED_ON  = 1
}tLED_State;

void LED_Init(void);
void LED_Update(void);
void LED_SetState(tLED_State state);
tLED_State LED_GetState(void);
void LED_Toggle(void);

#endif // __LED_H__
