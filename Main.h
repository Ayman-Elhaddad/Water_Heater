#ifndef __MAIN_H__
#define __MAIN_H__


#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 8000000


#define TMR_TICK_MS (10)


/* GPIO definitions */
/* GPIO Pins */
#define GPIO_PIN_0              (0)
#define GPIO_PIN_1              (1)
#define GPIO_PIN_2              (2)
#define GPIO_PIN_3              (3)
#define GPIO_PIN_4              (4)
#define GPIO_PIN_5              (5)
#define GPIO_PIN_6              (6)
#define GPIO_PIN_7              (7)

/* GPIO Port Registers redefinition */
#define GPIO_PORTA_DATA         (PORTA)
#define GPIO_PORTA_CONTROL      (TRISA)

#define GPIO_PORTB_DATA         (PORTB)
#define GPIO_PORTB_CONTROL      (TRISB)

#define GPIO_PORTC_DATA         (PORTC)
#define GPIO_PORTC_CONTROL      (TRISC)

#define GPIO_PORTD_DATA         (PORTD)
#define GPIO_PORTD_CONTROL      (TRISD)

#define GPIO_PORTE_DATA         (PORTE)
#define GPIO_PORTE_CONTROL      (TRISE)

/* GPIO direction setting */
#define GPIO_OUT                (0)
#define GPIO_IN                 (1)

/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION)   ((CONTROL) = (DIRECTION)?(~GPIO_OUT):(GPIO_OUT))
#define GPIO_WritePort(PORT, DATA)          ((PORT) = (DATA))
#define GPIO_ReadPort(PORT)                 (PORT)

/* GPIO port pin operations */
#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION)   ((CONTROL) = (CONTROL & (~(1 << PIN)))|(DIRECTION << PIN))
#define GPIO_WritePortPin(PORT, PIN, DATA)          ((PORT) = (PORT & (~(1 << PIN)))|(DATA << PIN))
#define GPIO_ReadPortPin(PORT, PIN)                 (((PORT) & (1 << PIN)) >> (PIN))
/* End of code filling */

/* Timer 0 macros */

#define TMR_SET_PRESCALER_256			PS2 = 1;\
										PS1 = 1;\
										PS0 = 1;\
										PSA = 0

#define TMR_GET_FLAG					(TMR0IF)
#define TMR_CLEAR_FLAG					(TMR0IF = 0)

#define TMR_UPDATE_REGISTER(TIME)		(TMR0 = 256 - ((TIME) * 8))

#define TMR_ENABLE_INTERRUPT			(TMR0IE = 1)
#define GLOBAL_INTERRUPT_ENABLE			(GIE = 1)
#define PERIPHERAL_INTERRUPT_ENABLE		(PEIE = 1)

#define TMR_ENABLE_CLOCK				(T0CS = 0)
#define TMR_DISABLE_CLOCK				(T0CS = 1)




/********************************************************/

/* Timer 1 macros */

#define TMR1_SET_PRESCALER_1to2			T1CKPS1 = 0;\
										T1CKPS0 = 1

#define TMR1_GET_FLAG					(TMR1IF)
#define TMR1_CLEAR_FLAG					(TMR1IF = 0)


#define TMR1_ENABLE_INTERRUPT			(TMR1IE = 1)

#define TMR1_INTERNAL_CLOCK             (TMR1CS = 0)

#define TMR1_UPDATE_REGISTER(TIME)		(TMR1 = 65536 - ((TIME) * 1000))

#define TMR1_ENABLE				        (TMR1ON = 1)
#define TMR1_DISABLE			     	(TMR1ON = 0)

#define OSCILLATOR_SHUT_OFF             (T1OSCEN = 0)


/* ADC macros */
#define ADC_FOSC_BY_2   (0)
#define ADC_FOSC_BY_8   (1)
#define ADC_FOSC_BY_32  (2)
#define ADC_FRC_L       (3)
#define ADC_FOSC_BY_4   (4)
#define ADC_FOSC_BY_16  (5)
#define ADC_FOSC_BY_64  (6)
#define ADC_FRC_H       (7)


/* ADC Configuration */

#define ADC_ADJUST_RESULT_LEFT      (0)
#define ADC_ADJUST_RESULT_RIGHT     (1)

#define ADC_OFF (ADON = 0)
#define ADC_ON  (ADON = 1)

#define ADC_SELECT_CLOCK(clock) (ADCS2 = ((clock) & 0x4 ) >> 2);\
                                (ADCS1 = ((clock) & 0x2 ) >> 1);\
                                (ADCS0 = (clock) & 0x1)

#define ADC_CONFIGURE_PORT      PCFG3 = 0;\
                                PCFG2 = 0;\
                                PCFG1 = 1;\
                                PCFG0 = 0

#define ADC_ADJUST_RESULT(adjustment)   (ADFM = adjustment)

#define ADC_SELECT_CHANNEL(channel)     (CHS2 = ((channel & 0x4) >> 2));\
                                        (CHS1 = ((channel & 0x2) >> 1));\
                                        (CHS0 = (channel & 0x1))

#define ADC_START_CONVERSION    (GO = 1)
#define ADC_WAIT_FOR_RESULT     while(GO == 1)
#define ADC_READ_RESULT(adjustment) (adjustment)?((((tWord)ADRESH)<<8)|(ADRESL)):((((tWord)ADRESH)<<2)|(ADRESL>>6))

/* Standard data types */
typedef unsigned char tByte;
typedef unsigned int tWord;

#endif // __MAIN_H__
