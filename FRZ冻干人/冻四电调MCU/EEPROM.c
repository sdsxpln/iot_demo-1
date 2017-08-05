
//2017-02-14

#include "reg51.h"
//#include "UNIQ_ID.h"
#include "EEPROM.h"
#include "intrins.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

sfr  IAP_DATA   = 0xC2;     
sfr  IAP_ADDRH  = 0xC3;     
sfr  IAP_ADDRL  = 0xC4;   
sfr  IAP_CMD    = 0xC5;     
sfr  IAP_TRIG   = 0xC6;      
sfr  IAP_CONTR  = 0xC7;     

#define   CMD_IDLE      0   
#define   CMD_READ      1    
#define   CMD_WRITE     2    
#define   CMD_ERASE     3  

//IAP????
//#define   ENABLE_IAP   0x80    //??????<30MHz
#define   ENABLE_IAP   0x81    //??????<24MHz
//#define   ENABLE_IAP   0x82    //??????<20MHz
//#define   ENABLE_IAP   0x83    //??????<12MHz
//#define   ENABLE_IAP   0x84    //??????<6MHz
//#define   ENABLE_IAP   0x85    //??????<3MHz
//#define   ENABLE_IAP   0x86    //??????<2MHz
//#define   ENABLE_IAP   0x87    //??????<1MHz


//#define    IAP_ADDRE   0x0000



/*
例子：
#define    IAP_ADDRE   0x0000
#define    IAP_ADDRE   0x0000

	IapEraseSector(IAP_ADDRE);
	for(i = 0; i < 3*4; i++)
	{
		IapWriteByte( IAP_ADDRE + i, ip0[i] );
	}
	for(i = 0; i < 3*4; i++)
	{
		ip0[i] = IapReadByte( IAP_ADDRE + i );
	}
	//j = IapReadByte( IAP_ADDRE );
	//j++;
	//IapEraseSector(IAP_ADDRE);
	//IapWriteByte( IAP_ADDRE , j );
	*/
	


#if 0


void eeprom_read_block( unsigned int addr, unsigned char *p, unsigned int len )
{
	unsigned int eeprom_block_count_i;
	for( eeprom_block_count_i = 0; eeprom_block_count_i < len; eeprom_block_count_i++ )
	{
		p[eeprom_block_count_i] = IapReadByte( addr + eeprom_block_count_i );
	}
}


void eeprom_write_block( unsigned int addr, unsigned char *p, unsigned int len ) // 需要辅以 IapEraseSector	
{
	unsigned int eeprom_block_count_i;
	for( eeprom_block_count_i = 0; eeprom_block_count_i < len; eeprom_block_count_i++ )
	{
		IapWriteByte( addr + eeprom_block_count_i, p[eeprom_block_count_i] );
	}
}

unsigned char eeprom_check_diff_block( unsigned int addr, unsigned char *p, unsigned int len )
{
	unsigned int eeprom_block_count_i;
	for( eeprom_block_count_i = 0; eeprom_block_count_i < len; eeprom_block_count_i++ )
	{
		if( p[eeprom_block_count_i] != IapReadByte( addr + eeprom_block_count_i ) )
		{
			return 1;
		}
	}
	return 0;
}

#endif












#if 0



/**********************************************************
** ????: void IapIdle();
** ????: ??IAP??
**********************************************************/
//void IapIdle()
//{
//    IAP_CONTR = 0;       //?? IAP ??
//    IAP_CMD   = 0;       //?????????????
//    IAP_TRIG  = 0;       //???????
//    IAP_ADDRH = 0xFF;    //IAP?????? EEPROM ??
//    IAP_ADDRL = 0xFF;
//}

/*----------------------------
关闭IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //清除命令寄存器
    IAP_TRIG = 0;                   //清除触发寄存器
    IAP_ADDRH = 0x80;               //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}




/**********************************************************
** ????: unsigned char IapReadByte(unsigned int addr);
** ????: ?EEPROM
** ?   ?: unsigned int addr  ??
** ?   ?: unsigned char dat  ??
**********************************************************/
unsigned char IapReadByte(unsigned int addr)
{
    unsigned char dat;        //????
    IAP_CONTR = ENABLE_IAP;   //?? IAP ??, ???????
    IAP_CMD   = CMD_READ;     //?? ISP/IAP/EEPROM ????
    IAP_ADDRL = addr;         //?? ISP/IAP/EEPROM ????
    IAP_ADDRH = addr >> 8;    //?? ISP/IAP/EEPROM ????
    IAP_TRIG  = 0x5a;         //?????? 1 (0x5a)
    IAP_TRIG  = 0xa5;         //?????? 2 (0xa5)
    _nop_();                  //MCU ???? ISP/IAP/EEPROM ????
    _nop_();                  //??15F104E??bug,NOP3?
    _nop_();                  //
    dat = IAP_DATA;           //?? ISP/IAP/EEPROM ??
    IapIdle();                //?? ISP/IAP/EEPROM ??
    return dat;               //?? Flash ??
}



/**********************************************************
** ????: void IapWriteByte(unsigned int addr, unsigned char dat);
** ????: ?EEPROM??
** ?   ?: unsigned int addr  ???
             unsigned char dat  ???
**********************************************************/
void IapWriteByte(unsigned int addr, unsigned char dat)
{
    IAP_CONTR = ENABLE_IAP;    //?? IAP ??, ???????
    IAP_CMD   = CMD_WRITE;     //?? ISP/IAP/EEPROM ????
    IAP_ADDRL = addr;          //?? ISP/IAP/EEPROM ????
    IAP_ADDRH = addr >> 8;     //?? ISP/IAP/EEPROM ????
    IAP_DATA  = dat;           //? ISP/IAP/EEPROM ??
    IAP_TRIG  = 0x5a;          //?????? 1 (0x5a)
    IAP_TRIG  = 0xa5;          //?????? 2 (0xa5)
    _nop_();                   //MCU ???? ISP/IAP/EEPROM ????
    _nop_();                   //??15F104E??bug,NOP3?
    _nop_();                   //
    IapIdle();                 //?? ISP/IAP/EEPROM ??
}



/**********************************************************
** ????: void IapEraseSector(unsigned int addr);
** ????: ??EEPROM??
** ?   ?: unsigned int addr ????
**********************************************************/
void IapEraseSector(unsigned int addr)
{
    IAP_CONTR = ENABLE_IAP;   //?? IAP ??, ???????
    IAP_CMD   = CMD_ERASE;    //?? ISP/IAP/EEPROM ?????
    IAP_ADDRL = addr;         //?? ISP/IAP/EEPROM ????
    IAP_ADDRH = addr >> 8;    //?? ISP/IAP/EEPROM ????
    IAP_TRIG  = 0x5a;         //?????? 1 (0x5a)
    IAP_TRIG  = 0xa5;         //?????? 2 (0xa5)
    _nop_();                  //MCU ???? ISP/IAP/EEPROM ????
    _nop_();                  //??15F104E??bug,NOP3?
    _nop_();                  //
    IapIdle();                //?? ISP/IAP/EEPROM ??
}


#endif


