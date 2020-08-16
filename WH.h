
#ifndef __WH_H__
#define	__WH_H__

typedef enum
{
    POWER_OFF,
    NORMAL,
    SETTING,
    HEATING,
    COOLING
    
}tWH_State;


void WH_Update(void);

tByte WH_Get_Current_state (void);

#endif	

