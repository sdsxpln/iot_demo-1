
//2017-02-14

#ifndef __EEPROM_H__
#define __EEPROM_H__



void IapEraseSector(unsigned int addr);

void IapWriteByte(unsigned int addr, unsigned char dat);
unsigned char IapReadByte(unsigned int addr);

//void Delay(unsigned char n);



void eeprom_read_block( unsigned int addr, unsigned char *p, unsigned int len );
void eeprom_write_block( unsigned int addr, unsigned char *p, unsigned int len );
unsigned char eeprom_check_diff_block( unsigned int addr, unsigned char *p, unsigned int len );   // 0=全对。 1=有不同



#endif



