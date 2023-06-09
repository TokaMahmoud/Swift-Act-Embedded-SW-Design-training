
#ifndef _TIMER2_H_
#define _TIMER2_H_

#include "../Main/main.h"
#include "stm32f4xx_ll_tim.h"

#define TIMER2_PRESCALER (10)

/*system frequemcy and prescaler dependent
*TIMER_TICK_TIME_IN_MICRO_SEC = 1/Timer Frequency after prescaler*/
#define TIMER_TICK_TIME_IN_MICRO_SEC   (0.625)

/*timer initilization function*/
void Timer2_init(void);
/*update timer2 maximum or compared value (ARR register) */
void set_firing_angle_num_of_counts(uint32_t couns_num);

/*this func just make the counter stop counting
*and disable the clock nothing else 
*TIM2->CR1 &=~(1<<0)*/
void stop_Timer2(void);
/*set the call back function by passing CB func address to it 
 * to be executed every interrupt */
void Timer2_set_call_back_func(void(*a_ptr)(void)); 

#endif /* TIMER2_DRV_H_ */