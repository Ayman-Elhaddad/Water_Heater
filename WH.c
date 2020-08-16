
#include "Temperature.h"
#include "WH.h"
#include "Display.h"
#include "DO.h"
#include "SW.h"
#include "SSD.h"
#include "EEPROM.h"

#define WH_Update_PERIOD (20)
#define SECOND_PERIOD (1000)
#define SW_Step (5)

static tWH_State Decision(void);
static void OFF_Actions(void);
static void Heating_Actions(void);
static void Cooling_Actions(void);
static void Setting_Actions(void);
static void Normal_Actions(void);


static tWord Current_Temp = 0;

static tWord Actual_Temp = Temp_Initial_val ;

static tWH_State Current_WH_State = POWER_OFF;

static tByte flag = 0;


void WH_Update(void)
{
    static tByte WH_Update_Counter = 10;
    WH_Update_Counter += TMR_TICK_MS;
    if(WH_Update_Counter != WH_Update_PERIOD)
    {
        return;
    }
    WH_Update_Counter = 0;
    
    /*update display state  */
    Set_Disp_State (Current_WH_State);
    /*Get the new current_temp */
    Current_Temp = TEMPERATURE_GetValue();
    
    switch(Current_WH_State)
    {
        case POWER_OFF:
            
            OFF_Actions();
            if(SW_GetState(POWER_SW) == SW_PRE_PRESSED)
            {
                EEPROM_Write(0x0020, Actual_Temp);
                
                Current_WH_State = NORMAL;
                
                if(flag)
                {
                   Actual_Temp =  EEPROM_Read(0x0020);
                 }
                 else
                {
                    flag = 1;
                }
            }
            
            break;
        
        case SETTING:
            
            Setting_Actions();
            
            if(SW_GetState(POWER_SW) == SW_PRE_PRESSED)
            {
                Current_WH_State = POWER_OFF;
                
                return;
            }
            
            break;
        
        case HEATING:
            
            Heating_Actions();
            
            if(SW_GetState(POWER_SW) == SW_PRE_PRESSED)
            {
                Current_WH_State = POWER_OFF;
                return;
            }
            else if((SW_GetState(DOWN_SW) == SW_PRE_RELEASED) || (SW_GetState(UP_SW) == SW_PRE_RELEASED))
            {
                Current_WH_State = SETTING;
                return;
            }
            
            break;
        
        case COOLING:
            
            Cooling_Actions();

            if(SW_GetState(POWER_SW) == SW_PRE_PRESSED)
            {
                Current_WH_State = POWER_OFF;
                return;
            }
            else if((SW_GetState(DOWN_SW) == SW_PRE_RELEASED) || (SW_GetState(UP_SW) == SW_PRE_RELEASED))
            {
                Current_WH_State = SETTING;
                return;
            }
            
            break;
        
        case NORMAL:
     
            Normal_Actions();
            Current_WH_State = Decision();
            if(SW_GetState(POWER_SW) == SW_PRE_PRESSED)
            {
                Current_WH_State = POWER_OFF;
                return;
            }
            else if((SW_GetState(DOWN_SW) == SW_PRE_RELEASED) || (SW_GetState(UP_SW) == SW_PRE_RELEASED))
            {
                Current_WH_State = SETTING;
                return;
            }
            
            break;
        
        default :
            break;
    }
}

static void OFF_Actions(void)
{
    SSD_SetState(SSD_TENS, SSD_OFF);
    SSD_SetState(SSD_UNITS, SSD_OFF);
    
    DO_SetState(Heater , OFF);
    DO_SetState(Cooler , OFF);
    Set_Led_State(LED_OFF);
}

static void Heating_Actions(void)
{
    
    Set_Disp_Temp (Current_Temp);
    
    DO_SetState(Heater ,ON );
    DO_SetState(Cooler , OFF);
    Set_Led_State(LED_TOGGLE);
    
    if(Actual_Temp == Current_Temp )
    {
        Current_WH_State = NORMAL;
    }

    
}
static void Cooling_Actions(void)
{
    Set_Disp_Temp (Current_Temp);

    DO_SetState(Heater , OFF);
    DO_SetState(Cooler , ON);
    Set_Led_State(LED_ON);
    
    if(Actual_Temp == Current_Temp )
    {
        Current_WH_State = NORMAL;
    }
    
}

static void Normal_Actions(void)
{
    Set_Disp_Temp (Current_Temp);    

    DO_SetState(Heater , OFF);
    DO_SetState(Cooler , OFF);
    Set_Led_State(LED_OFF);
}

static void Setting_Actions(void)
{
    static tWord Exit_Count=0;
    
    Set_Disp_Temp (Actual_Temp);   
    
    if(SW_GetState(UP_SW) == SW_PRE_PRESSED)
    {
        Exit_Count = 0;
        Actual_Temp += SW_Step ;
        if(Actual_Temp > 75 )
        {
            Actual_Temp = 75;
        }
    }
    else if(SW_GetState(DOWN_SW) == SW_PRE_PRESSED)
    {
        Exit_Count = 0;
        Actual_Temp -= SW_Step ;
        if(Actual_Temp < 35 )
        {
            Actual_Temp = 35;
        }
    }
    else
    {
        Exit_Count += WH_Update_PERIOD ;
        
        if(Exit_Count == SECOND_PERIOD * 5)
        {
        Exit_Count = 0;
        Current_WH_State = Decision();
        return;
        }
    }
    EEPROM_Write(0x0020, Actual_Temp);
}

static tWH_State Decision(void)
{
    if(Actual_Temp >= (Current_Temp + 5 ) )
    {
        return HEATING;
    }
    else if((Actual_Temp + 5 ) <= Current_Temp )
    {
        return COOLING;
    }
    else
    {
        return NORMAL;
    }
}

tByte WH_Get_Current_state (void)
{
    return Current_WH_State;
}