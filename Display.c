#include "Main.h"
#include "SSD.h"
#include "Timer.h"
#include "WH.h"
#include "Display.h"
#include "SW.h"
#include "Temperature.h"



#define DISP_PERIOD_MS   (100)
#define DISP_SECOND_BLINK_MS (1000)

static void Disp_Temp_state (tWH_State );

static tByte Disp_Current_State = POWER_OFF;

tWord Temp  = 0;

void DISP_Init(void)
{
        SSD_Init();
        
        SSD_SetValue(SSD_TENS, SSD_NULL);
        SSD_SetValue(SSD_UNITS,SSD_NULL);
}


void DISP_Update(void)
{
    static tWord DISP_counter = 10;

    /* Check if it is time for the DISP_Update to run */
    DISP_counter += TMR_TICK_MS;

    if (DISP_counter != DISP_PERIOD_MS)
    {
        return;
    }
    DISP_counter = 0;
    
    Disp_Temp_state(Disp_Current_State);
}


void Display_Temp(void)
{
    SSD_SetValue(SSD_UNITS,Temp %10);
    SSD_SetValue(SSD_TENS, Temp /10);
}

void Display_Null(void)
{
    SSD_SetValue(SSD_UNITS,SSD_NULL);
    SSD_SetValue(SSD_TENS,SSD_NULL);
}

static void Disp_Temp_state (tWH_State Disp_Current_State)
{
  
     if(Disp_Current_State == SETTING)
    {
        static tWord sec_count = 0;
        sec_count += DISP_PERIOD_MS;
        
        if(sec_count == DISP_SECOND_BLINK_MS / 2 )
        {
            Display_Temp();
        }
        else if(sec_count == DISP_SECOND_BLINK_MS  )
        {
            Display_Null();
            sec_count = 0;         
        }
               
    }
     else if (Disp_Current_State == POWER_OFF)
    {
        Display_Null();
    }
 
    else 
    {
        Display_Temp();
    }
}

void Set_Disp_Temp (tWord Temp_val)
{
    Temp = Temp_val ;
}

void Set_Disp_State (tWH_State Current_WH_State)
{
    Disp_Current_State = Current_WH_State;
}
