
#ifndef __I2C_H
#define	__I2C_H


void I2C_Master_Init(const unsigned long baud);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_ACK();
void I2C_NACK();
tByte I2C_Master_Write(unsigned char data);
tByte I2C_Read_Byte(void);


#endif	/* XC_HEADER_TEMPLATE_H */

