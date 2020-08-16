#include "Main.h"
#include "Port.h"
#include "Temperature.h"
#include "ADC.h"

#define TEMP_PERIOD_MS   (100)

#define Temp_Sensor_CHANNEL (2)

#define Readings_Num (10)


static tWord  Temp_val = 0;
static tWord  Temp_modified =  0 ;

void TEMPERATURE_Init(void)
{
    ADC_Init(ADC_FOSC_BY_8);
}

void TEMPERATURE_Update(void)
{

    static tWord TEMP_counter = 0;


    /* Check if it is time for the DISP_Update to run */
    TEMP_counter += TMR_TICK_MS;

    if (TEMP_counter != TEMP_PERIOD_MS)
    {
        return;
    }
    TEMP_counter = 0;

    Temp_val =  ADC_Convert(Temp_Sensor_CHANNEL, ADC_ADJUST_RESULT_LEFT);
    //Temp_modified =  Temp_val * ( Vref_val / ADC_MAX_READING ) * 100  ;
    Temp_modified =  Temp_val * 0.00488 * 100;
    
   
}


tWord TEMPERATURE_GetValue(void)
{
    tByte i;
    
    static tWord Temp_Stack [10] = {0};
    tWord Temp_Sum = 0;
    static float Temp_Avg = 0 ;
    
    for(i=0; i<10; i++)
    {
        
        if(i == 9)
        {
            Temp_Stack[i] =  Temp_modified ;
        }
        else
        {
            Temp_Stack[i] = Temp_Stack[i+1];
        }
        Temp_Sum += Temp_Stack[i];
        
    }
    Temp_Avg = (Temp_Sum / 10);
    return  (tWord)Temp_Avg  ;
}
