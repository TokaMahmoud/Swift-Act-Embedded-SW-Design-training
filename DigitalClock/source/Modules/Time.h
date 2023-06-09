#ifndef __TIME_H__
#define __TIME_H__

#include "../Main/main.h"

typedef struct
{
    tByte seconds;
    tByte minutes;
    tByte hours;
}tTIM_Time;

typedef enum
{
    TIM_NORMAL = 0,
    TIM_SET_HOURS,
    TIM_SET_MINUTES
}tTIM_State;

void TIM_Init(void);
void TIM_Update(void);
void TIM_GetTime(tTIM_Time * time);
tByte TIM_CompareTime(tTIM_Time * first, tTIM_Time * second);
tTIM_State TIM_GetState(void);
void TIM_CopyTime(tTIM_Time * dest, tTIM_Time * src);

#endif // __TIME_H__
