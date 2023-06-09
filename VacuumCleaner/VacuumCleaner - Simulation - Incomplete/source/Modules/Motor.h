#ifndef __MOTOR_H__
#define __MOTOR_H__

//initial angle to start the motor
#define MOTOR_START_ANGLE		MOTOR_ANGLE_90

typedef enum{
	soft_switching,
	harmonic_reduction
}tmotor_state;


typedef enum{
	MOTOR_ANGLE_90  = 90,
	MOTOR_ANGLE_140 = 140,
	MOTOR_ANGLE_10  = 10
}tmotor_angle;


//prototypes
void Motor_Init(void);
void Motor_SetAngle(tmotor_angle MOTOR_ANGLE);
void Motor_Update(void);
void call_back_firing(void);
#endif