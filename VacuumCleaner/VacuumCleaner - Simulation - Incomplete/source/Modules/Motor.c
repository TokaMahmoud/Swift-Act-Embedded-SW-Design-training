#include "../Modules/Timer.h"
#include "../Modules/VC.h"
#include "../Modules/Motor.h"
#include "stm32f4xx_ll_gpio.h"
#include "../Main/main.h"
#include "../Port/Port.h"
#include "../Modules/Timer2.h"

#define SOFT_SWITCHING_PERIOD_MS       (40)
#define HARMONIC_REDUCTION_PERIOD_MS   (20)
#define FIRING_ANGLE_PERIOD_MS				 (10)

typedef enum 
{ down = 0 , 
  up
}tHarmonic_state ; 

tByte fire =0;
static tmotor_state current_motor_state ;
static tByte current_angle, target_angle, firing_angle ;
static tHarmonic_state harmonic_state = up ; 

void Motor_Init(void){
	 
	MOTOR_ENABLE_CLOCK;
	
	//GPIO pin config
	LL_GPIO_InitTypeDef MOTOR_GPIO;
  MOTOR_GPIO.Pin        = MOTOR_PIN ;
  MOTOR_GPIO.Mode       = LL_GPIO_MODE_OUTPUT;
  MOTOR_GPIO.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  MOTOR_GPIO.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  MOTOR_GPIO.Pull       = LL_GPIO_PULL_NO;
  MOTOR_GPIO.Alternate  = LL_GPIO_AF_0;
  LL_GPIO_Init(MOTOR_PORT ,&MOTOR_GPIO);
	
	//set the initial angle for mid speed 
	Motor_SetAngle(MOTOR_START_ANGLE);
	
	//make current angle = firing angle = initial angle
	current_angle = MOTOR_START_ANGLE;
	firing_angle = MOTOR_START_ANGLE ; 
	
	//set the mode to be harmonic_reduction (no speed change at first)
	current_motor_state = harmonic_reduction ; 
	
	Timer2_set_call_back_func(call_back_firing);
}


tWord angle_to_time(tByte angle)
{
	float time_one_angle = (1 *1000)/18 ;
	tWord require_time_micro =  angle * time_one_angle;
	return require_time_micro;
}


void Motor_SetAngle(tmotor_angle MOTOR_ANGLE){

  switch(MOTOR_ANGLE)
	{
		case MOTOR_ANGLE_90:
			target_angle = 90;
			break;
		case MOTOR_ANGLE_10:
			target_angle = 10;
			break;
		case MOTOR_ANGLE_140:
			target_angle = 140;
			break;
		default:
			break;
	}
	
}

void call_back_firing(void){

	fire = 1;
	
}

//called every 10 ms
void Motor_Update(void){
	
//counts the tick number to handle the periodicty 
//soft_switching periodicty     = 40 ms = 4 ticks 
//harmonic_reduction periodicty = 20 ms = 2 ticks
static tWord soft_switching_counter = 0 ; 
static tWord harmonic_reduction_counter = 0 ; 
tByte counter =0;

stop_Timer2();
tWord timer_delay = angle_to_time(firing_angle);
set_firing_angle_num_of_counts(timer_delay);
 	
//FIRING
stop_Timer2();
tWord delay = angle_to_time(firing_angle);
set_firing_angle_num_of_counts(timer_delay);	
	
	
//check for motor state
switch(current_motor_state) {
	
	//to change motor speed level --> target angel != current
	case soft_switching : 
		//wait 4 ticks before change
		if(counter%3 == 0 ) 
		{
			current_angle = firing_angle ;
			if ( current_angle < target_angle)
			{
				firing_angle++ ; 
				current_angle = firing_angle ;  
			}
			else if ( current_angle > target_angle ) 
			{
				firing_angle-- ; 
				current_angle = firing_angle ;  
			}
			else
			{
				current_motor_state = harmonic_reduction ; 
			}
		}
		break;
	//to stay at the same speed level (target angel = current) we need to handle the harmonic  
	case harmonic_reduction : 
		//wait 2 ticks before change
		if(counter%2 == 0 ) {
			switch(harmonic_state) 
			{
				case up : 
					if (firing_angle == current_angle + 5 ) 
					{
						firing_angle -= 5 ; 
						harmonic_state = down ; 
					}
					else 
					{
						firing_angle += 5 ; 
					} 
					break;
				case down : 
					if ( firing_angle == current_angle - 5 ) 
					{
						firing_angle += 5 ; 
						harmonic_state = up ; 
					}
					else 
					{
						firing_angle -= 5 ; 
					}
					break;
				default:
					break;
			}
		}
		break;
	default:
		break;
}
counter = (counter + 1 )  % 4 ;
}

