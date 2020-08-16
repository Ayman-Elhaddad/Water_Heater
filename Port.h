#ifndef __PORT_H__
#define __PORT_H__

#include "Main.h"


/*LED pin */
#define LAMP_1_PORT_DR   (GPIO_PORTB_DATA)
#define LAMP_1_PORT_CR   (GPIO_PORTB_CONTROL)
#define LAMP_1_PIN       (GPIO_PIN_7)

/* Heater pin*/
#define HEATER_PORT_DR   (GPIO_PORTC_DATA)
#define HEATER_PORT_CR   (GPIO_PORTC_CONTROL)
#define HEATER_PIN       (GPIO_PIN_5)


/*Motor pin*/
#define COOLER_PORT_DR   (GPIO_PORTC_DATA)
#define COOLER_PORT_CR   (GPIO_PORTC_CONTROL)
#define COOLER_PIN       (GPIO_PIN_2)

/* Fill missing code below */
/* Switches */
#define UP_SW_PORT_DR     (GPIO_PORTB_DATA)
#define UP_SW_PORT_CR     (GPIO_PORTB_CONTROL)
#define UP_SW_PIN         (GPIO_PIN_3)

#define DOWN_SW_PORT_DR   (GPIO_PORTB_DATA)
#define DOWN_SW_PORT_CR   (GPIO_PORTB_CONTROL)
#define DOWN_SW_PIN       (GPIO_PIN_4)

#define POWER_SW_PORT_DR   (GPIO_PORTB_DATA)
#define POWER_SW_PORT_CR   (GPIO_PORTB_CONTROL)
#define POWER_SW_PIN       (GPIO_PIN_5)



/* SSD */
#define SSD_DATA_PORT_DR        (GPIO_PORTD_DATA)
#define SSD_DATA_PORT_CR        (GPIO_PORTD_CONTROL)

#define SSD_TENS_DR       (GPIO_PORTA_DATA)
#define SSD_TENS_CR       (GPIO_PORTA_CONTROL)
#define SSD_TENS_PIN      (GPIO_PIN_3)

#define SSD_UNITS_DR      (GPIO_PORTA_DATA)
#define SSD_UNITS_CR      (GPIO_PORTA_CONTROL)
#define SSD_UNITS_PIN     (GPIO_PIN_4)



/* I2C */

#define I2C_PORT_DR        (GPIO_PORTC_DATA)
#define I2C_PORT_CR        (GPIO_PORTC_CONTROL)
#define I2C_SCL_PIN        (GPIO_PIN_3)
#define I2C_SDA_PIN        (GPIO_PIN_4)


#endif // __PORT_H__
