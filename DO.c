#include "Main.h"
#include "Port.h"
#include "DO.h"
#define Toggle_Update_Period (100)
#define Lamp_Toggle_PERIOD  (1000)
#define DO_UPDATE_PERIOD (100)

static tByte Led_Current_State = LED_OFF ;

void DO_Init(void)
{

    GPIO_InitPortPin(HEATER_PORT_CR, HEATER_PIN , GPIO_OUT);
    GPIO_InitPortPin(COOLER_PORT_CR, COOLER_PIN , GPIO_OUT);
    GPIO_InitPortPin(LAMP_1_PORT_CR, LAMP_1_PIN , GPIO_OUT);


    GPIO_WritePortPin(HEATER_PORT_DR, HEATER_PIN , OFF);
    GPIO_WritePortPin(COOLER_PORT_DR, COOLER_PIN , OFF);
    GPIO_WritePortPin(LAMP_1_PORT_DR, LAMP_1_PIN , OFF);


}

void DO_SetState(tDO device ,tDO_State state)
{
    switch (device)
    {
        case Heater :
            GPIO_WritePortPin(HEATER_PORT_DR, HEATER_PIN , state);
            break;

        case Cooler :
            GPIO_WritePortPin(COOLER_PORT_DR, COOLER_PIN , state);
            break;

        default :
            break;
    }

}

void DO_Update (void)
{
    static tWord Toggle_Count = 0;
    static tWord DO_Counter = 90;
    DO_Counter += TMR_TICK_MS;
    if(DO_Counter != DO_UPDATE_PERIOD)
    {
        return;
    }

    DO_Counter = 0;
    
    switch(Led_Current_State)
    {
        case LED_OFF:
            GPIO_WritePortPin(LAMP_1_PORT_DR, LAMP_1_PIN , LED_OFF);
            break;
        
        case LED_ON:
            GPIO_WritePortPin(LAMP_1_PORT_DR, LAMP_1_PIN , LED_ON);
            break;
        
        case LED_TOGGLE:
            
            Toggle_Count += Toggle_Update_Period;
            if(Toggle_Count == Lamp_Toggle_PERIOD / 2)
            {
                GPIO_WritePortPin(LAMP_1_PORT_DR, LAMP_1_PIN , LED_ON);
            }
            else if(Toggle_Count == Lamp_Toggle_PERIOD )
            {
                GPIO_WritePortPin(LAMP_1_PORT_DR, LAMP_1_PIN , LED_OFF);
                Toggle_Count = 0;
            }
            break;
            
        default :
            break;   

    }
    

}

void Set_Led_State(tLed_State state)
{
    Led_Current_State = state ;
}


