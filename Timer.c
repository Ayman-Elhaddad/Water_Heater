#include "Main.h"
#include "Timer.h"
#include "SW.h"
#include "Display.h"
#include "SSD.h"
#include "DO.h"
#include "WH.h"
#include "Temperature.h"

extern tByte flag;

void TMR_Init(void)
{
	/* Add your code here! */
	TMR_SET_PRESCALER_256;
	TMR_DISABLE_CLOCK;
	//data sheet
	/* End of your code!*/
}
void TMR_Start(void)
{

	TMR_CLEAR_FLAG;
	TMR_UPDATE_REGISTER(TMR_TICK_MS);
	TMR_ENABLE_INTERRUPT;
	GLOBAL_INTERRUPT_ENABLE;
	TMR_ENABLE_CLOCK;

}
tByte TMR_CheckOverFlow(void)
{
	/* Add your code here! */
	return TMR_GET_FLAG;
	/* End of your code!*/
}
void TMR_Stop(void)
{
	/* Add your code here! */
	TMR_DISABLE_CLOCK;
	/* End of your code!*/
}

void __interrupt () TMR_Update(void)
{
	/* Add your code here! */
    //RC7 = 1 ^ RC7;
	/* Call Tasks */
	//flag = 1;

    /* Reload timer */
	TMR_CLEAR_FLAG;
	TMR_UPDATE_REGISTER(TMR_TICK_MS);


    SW_Update();
    SSD_Update();
    DISP_Update();
    TEMPERATURE_Update(); 
    DO_Update ();
    WH_Update();

  
    
    
    

	/* End of your code!*/

}
