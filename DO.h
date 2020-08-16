

#ifndef __DO_H__
#define __DO_H__




typedef enum
{
    Heater,
    Cooler,
}tDO;

typedef enum
{
    OFF = 0,
    ON  = 1
}tDO_State;

typedef enum
{
    LED_OFF = 0,
    LED_ON = 1,
    LED_TOGGLE
}tLed_State;

void Set_Led_State(tLed_State state);
void DO_Update (void);

void DO_Init(void);
void DO_SetState(tDO device ,tDO_State state);


#endif	/* XC_HEADER_TEMPLATE_H */

