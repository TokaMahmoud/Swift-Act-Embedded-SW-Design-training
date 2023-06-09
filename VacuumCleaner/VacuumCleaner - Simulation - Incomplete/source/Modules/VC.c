#include "../Modules/SW.h"
#include "../Modules/Timer.h"
#include "../Modules/VC.h"
#include "../Modules/Motor.h"

#define VC_TICK_TIME 20

static SPEED motor_speed;

tByte dust = 0;

void VC_Init(void){
    motor_speed = SPEED_MEDIUM;
}

void VC_Update(void){
   #if 0
    static uint32_t vc_counter = 0;
    /* Check if it is time for the VC_Update to run */
    vc_counter += TMR_TICK_MS;

    if(vc_counter != VC_TICK_TIME)
    {
        return;
    }
    vc_counter = 0;

    //Adjust motor speed according to switches
    if(SW_GetState(SW_DUST) != SW_PRESSED && SW_GetState(SW_PLUS) == SW_PRE_PRESSED){
        if(motor_speed == SPEED_HIGH)
        {
            Motor_SetAngle(MOTOR_ANGLE_10);
        }else if(motor_speed == SPEED_MEDIUM){
            motor_speed = SPEED_HIGH;
            Motor_SetAngle(MOTOR_ANGLE_10);
        }else if(motor_speed == SPEED_LOW){
            motor_speed = SPEED_MEDIUM;
            Motor_SetAngle(MOTOR_ANGLE_90);
        }
    }else if((SW_GetState(SW_DUST) != SW_PRESSED && SW_GetState(SW_MINUS) == SW_PRE_PRESSED) || (SW_GetPressedTime(SW_DUST) == RequiredPress)){
        if(motor_speed == SPEED_LOW)
        {
            Motor_SetAngle(MOTOR_ANGLE_140);
        }else if(motor_speed == SPEED_MEDIUM){
            motor_speed = SPEED_LOW;
            Motor_SetAngle(MOTOR_ANGLE_140);
        }else if(motor_speed == SPEED_HIGH){
            motor_speed = SPEED_MEDIUM;
            Motor_SetAngle(MOTOR_ANGLE_90);
        }
    }
    
   #endif
   
   static tWord old_pressed_time = 0;
   
   static uint32_t vc_counter = 0;
    /* Check if it is time for the VC_Update to run */
    vc_counter += TMR_TICK_MS;

    if(vc_counter != VC_TICK_TIME)
    {
        return;
    }
    vc_counter = 0;

    //Adjust motor speed according to switches
    if(SW_GetState(SW_DUST) != SW_PRESSED && SW_GetState(SW_PLUS) == SW_PRE_PRESSED){
        if(motor_speed == SPEED_HIGH)
        {
            Motor_SetAngle(MOTOR_ANGLE_10);
        }else if(motor_speed == SPEED_MEDIUM){
            motor_speed = SPEED_HIGH;
            Motor_SetAngle(MOTOR_ANGLE_10);
        }else if(motor_speed == SPEED_LOW){
            motor_speed = SPEED_MEDIUM;
            Motor_SetAngle(MOTOR_ANGLE_90);
        }
        old_pressed_time = 0;
        dust = 0;
    }else if((SW_GetState(SW_DUST) != SW_PRESSED && SW_GetState(SW_MINUS) == SW_PRE_PRESSED)){
        if(motor_speed == SPEED_LOW)
        {
            Motor_SetAngle(MOTOR_ANGLE_140);
        }else if(motor_speed == SPEED_MEDIUM){
            motor_speed = SPEED_LOW;
            Motor_SetAngle(MOTOR_ANGLE_140);
        }else if(motor_speed == SPEED_HIGH){
            motor_speed = SPEED_MEDIUM;
            Motor_SetAngle(MOTOR_ANGLE_90);
        }
        old_pressed_time = 0;
        dust = 0;
    }else if((SW_GetState(SW_DUST) == SW_PRESSED) && (SW_GetPressedTime(SW_DUST) > old_pressed_time)){
      dust = 1;
      if(((SW_GetPressedTime(SW_DUST) - old_pressed_time) >= DUST_SPEED_PERIOD))
      {
       if(motor_speed == SPEED_LOW)
        {
            Motor_SetAngle(MOTOR_ANGLE_140);
        }else if(motor_speed == SPEED_MEDIUM){
            motor_speed = SPEED_LOW;
            Motor_SetAngle(MOTOR_ANGLE_140);
           old_pressed_time = SW_GetPressedTime(SW_DUST);
        }else if(motor_speed == SPEED_HIGH){
            motor_speed = SPEED_MEDIUM;
            Motor_SetAngle(MOTOR_ANGLE_90);
           old_pressed_time = SW_GetPressedTime(SW_DUST);
        }
      }
    }else{
      old_pressed_time = 0;
       dust = 0;
    }

}

SPEED VC_GetSpeed(void){
    return motor_speed;
}
