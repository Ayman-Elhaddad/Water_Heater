#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Main.h"
#include "WH.h"

void DISP_Init(void);
void DISP_Update(void);
void Set_Disp_Temp (tWord);
void Display_Temp(void);
void Set_Disp_State (tWH_State );
#endif // __DISPLAY_H__
