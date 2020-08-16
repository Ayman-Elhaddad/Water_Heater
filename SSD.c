#include "Main.h"
#include "Port.h"
#include "SSD.h"

/* SSD_Update period */
#define SSD_PERIOD_MS   (10)

/* Number of SSD symbols */
#define N_SSD_SYMBOLS   (11)


/* SSD Symbols port data values */
static tByte SSD_Data[N_SSD_SYMBOLS] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b00000000, //null
};


/* Current SSD to be updated >> to be enabled and disable the other three */
static tSSD SSD_current = SSD_TENS;

/* SSD values */
static tSSD_Symbol SSD_Values[N_SSD] = {SSD_NULL};
//SSD_Values is a the buffer for data which comes from [DISP] module .. going to look up data before [SSD]



static void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol);
//the main logic of the SSD_Update

void SSD_Init(void)
{

    /* Initialize SSD data pins */
    GPIO_InitPort(SSD_DATA_PORT_CR, GPIO_OUT);
    SSD_Out(SSD_TENS, SSD_NULL);
    SSD_Out(SSD_UNITS, SSD_NULL);

    /* Initialize SSD control pin and turn SSD OFF*/

    GPIO_InitPortPin(SSD_TENS_CR, SSD_TENS_PIN, GPIO_OUT);

    GPIO_InitPortPin(SSD_UNITS_CR, SSD_UNITS_PIN, GPIO_OUT);


    SSD_SetState(SSD_TENS, SSD_OFF);
    SSD_SetState(SSD_UNITS, SSD_OFF);
    //to make sure that it not displaying any thing .. but initialized as an output

}

void SSD_Update(void)
{
    static tWord SSD_counter = 0;


    /* Check if it is time for the SSD_Update to run */
    SSD_counter += TMR_TICK_MS;

    if (SSD_counter != SSD_PERIOD_MS){
        return;
    }

    SSD_counter = 0;

    /* display current SSD value "from the buffer"  to the current SSD */
    SSD_Out(SSD_current, SSD_Values[SSD_current]);

    if (SSD_current == SSD_UNITS)
    {
        SSD_current = SSD_TENS;
    } else
    {
        SSD_current++;
    }

}
//Get_Symbol
//take data from the current display
tSSD_Symbol SSD_GetValue(tSSD ssd)
{

    return SSD_Values[ssd];

}
//Set_Symbol
//write data to the current display
void SSD_SetValue(tSSD ssd, tSSD_Symbol ssd_symbol)
{

    SSD_Values[ssd] = ssd_symbol;
    /* End of your code!*/
}

tSSD_State SSD_GetState(tSSD ssd)
{
    tSSD_State ret = SSD_OFF;

    switch (ssd)
    {
        case SSD_TENS:
            ret = GPIO_ReadPortPin(SSD_TENS_DR, SSD_TENS_PIN);
            break;
        case SSD_UNITS:
            ret = GPIO_ReadPortPin(SSD_UNITS_DR, SSD_UNITS_PIN);
            break;


        /* Should not be here */
        default:
            break;
    }

     return ret;

}

void SSD_SetState(tSSD ssd, tSSD_State state)
{

    switch (ssd)
    {
        case SSD_TENS:
            GPIO_WritePortPin(SSD_TENS_DR, SSD_TENS_PIN, state);
            break;
        case SSD_UNITS:
            GPIO_WritePortPin(SSD_UNITS_DR, SSD_UNITS_PIN, state);
            break;

        default:
            break;
    }

}

static  void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol)
{
    /* Turn off SSDs */
    SSD_SetState(SSD_TENS, SSD_OFF);
    SSD_SetState(SSD_UNITS, SSD_OFF);

    /* Output ssd_symbol on selected ssd */
    GPIO_WritePort(SSD_DATA_PORT_DR, SSD_Data[ssd_symbol]);


    /* Turn ssd ON */
    SSD_SetState(ssd, SSD_ON);

}

