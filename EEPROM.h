
#ifndef _EEPROM_H
#define	_EEPROM_H



void EEPROM_Write(unsigned int add, unsigned char data);
void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len);
tByte EEPROM_Read(unsigned int add);
void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len);

#endif	/* XC_HEADER_TEMPLATE_H */

