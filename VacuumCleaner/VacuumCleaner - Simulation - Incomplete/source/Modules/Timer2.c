
#include "Timer2.h"
#include "stdint.h"

static  void (*g_Timer2_callBackPtr)(void) = NULL_PTR ;


void timer2_init(void)
{
	/*enales Timer2 clk*/
	RCC->AHB1ENR |=(1<<0);
	/*auto reload register is buffered */
	TIM2->CR1|=(1<<7) ;
	/*URS=1 => only counter overflow and underflow generates an iterupt*/
	TIM2->CR1|=(1<<2) ;

	/*select edge aligned mode to make timer cabalbe for counting up or down depending on DIR bit  */
	TIM2->CR1 &=~((1<<5)|(1<<6)) ;
	/*upcounting mode DIR=0*/
	TIM2->CR1 &=~(1<<4);
	/*Fcpu =16MH ,prescaler =PSC+1  ,Ftimer2=(16MHZ/10)=16*10^5*/
	TIM2->PSC=9 ; 
	/*coresponding to 170 deg initial speed */
	TIM2->ARR=15111;
	/*update interrupt enable*/
	TIM2->DIER|=(1<<0) ;
	/*to enable IRQ number 28 which is the IRQ of timer2 */
	NVIC->ISER[0]= 1<<28 ; 
	
	
}
 
void set_firing_angle_num_of_counts(uint32_t couns_num)
{
	
	/*set the compared or max value of thecounter  */
	TIM2->ARR=couns_num;
	/*UG (update generation)is enable (to re_initialize the counter ,start from 0)*/
	TIM2->EGR |=(1<<0);
	/*start the counter*/
	TIM2->CR1 |=(1<<0);
}

/*this func just make the counter stop counting nothing else 
*TIM2->CR1 &=~(1<<0)*/
void stop_Timer2(void)
{
	TIM2->CR1 &=~(1<<0); 
	
}

/*======================================================*/
void Timer2_set_call_back_func(void(*a_ptr)(void))
{
	
	g_Timer2_callBackPtr = a_ptr ; 
	
}

/*======================================================*/
/*ISR handler */
void TIM2_IRQHandler(void) 
{
	/*clera the intrrupt flag */
	TIM2->SR &=~(1<<0) ; 
	
	 if(g_Timer2_callBackPtr != NULL_PTR)/*Execute call back function if it is enabled */
	{
		(*g_Timer2_callBackPtr)();
	} 
}
