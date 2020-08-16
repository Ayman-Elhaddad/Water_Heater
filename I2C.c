#include "Main.h"
#include "I2C.h"

#include <xc.h>

void I2C_Master_Init(const unsigned long baud)
{
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*baud))-1;
    SSPSTAT = 0;
    TRISC3 = 1;
    TRISC4 = 1;
}
void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;
}
void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;
}
void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;
}
tByte I2C_Master_Write(unsigned char data)
{
    I2C_Master_Wait();
    SSPBUF = data;
    while(!SSPIF);  // Wait Until Completion
	SSPIF = 0;
    return ACKSTAT;
}
tByte I2C_Read_Byte(void)
{
    //---[ Receive & Return A Byte ]---
	I2C_Master_Wait();
    RCEN = 1;		  // Enable & Start Reception
	while(!SSPIF);	  // Wait Until Completion
	SSPIF = 0;		  // Clear The Interrupt Flag Bit
    I2C_Master_Wait();
    return SSPBUF;	  // Return The Received Byte
}
void I2C_ACK(void)
{
	ACKDT = 0;			// 0 -> ACK
	I2C_Master_Wait();
    ACKEN = 1;			// Send ACK
}
void I2C_NACK(void)
{
	ACKDT = 1;			// 1 -> NACK
    I2C_Master_Wait();
	ACKEN = 1;			// Send NACK
}
