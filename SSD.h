#ifndef __SDD_H__
#define __SDD_H__

#include "Main.h"
//#include "Port.h"

/* Number of SSDs */
#define N_SSD           (2)


typedef enum
{
    SSD_TENS,
    SSD_UNITS
}tSSD;

/* SSD states */
typedef enum
{
    SSD_OFF = 0,
    SSD_ON = 1
}tSSD_State;

/* SSD symbols */

typedef enum
{
    SSD_0 = 0,
    SSD_1,
    SSD_2,
    SSD_3,
    SSD_4,
    SSD_5,
    SSD_6,
    SSD_7,
    SSD_8,
    SSD_9,
    SSD_NULL
}tSSD_Symbol;

void SSD_Init(void);
void SSD_Update(void);
void SSD_SetValue(tSSD ssd, tSSD_Symbol ssd_symbol);
void SSD_SetState(tSSD ssd, tSSD_State state);



#endif // __SDD_H__
