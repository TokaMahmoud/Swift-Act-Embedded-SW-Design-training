#ifndef __VC_H_
#define __VC_H_

#define DUST_SPEED_PERIOD 10000

typedef enum{
    SPEED_LOW = 0,
    SPEED_MEDIUM,
    SPEED_HIGH
}SPEED;

void VC_Init(void);
void VC_Update(void);
SPEED VC_GetSpeed(void);

#endif // __VC_H_
