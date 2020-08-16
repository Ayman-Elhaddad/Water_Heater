#ifndef __SW_H__
#define __SW_H__


#define N_SWITCHES      (3)

typedef enum
{
    UP_SW,
    DOWN_SW,
    POWER_SW
}tSW;

typedef enum
{
    SW_RELEASED,
    SW_PRE_PRESSED,
    SW_PRESSED,
    SW_PRE_RELEASED
}tSW_State;

void SW_Init(void);
//void SW_Init(tSW , tSW_State); is better

tSW_State SW_GetState(tSW sw);
void SW_Update(void);

#endif // __SW_H__
