/****** **************/
//#include <reg52.h>
#include "UNIQ_ID.h"
#include "INTRINS.H"
#include "Delay_12M.h"
#include "bmp280iica.h"

//2017-06-07


#define   bool unsigned char
#define   TRUE 1
#define   FALSE 0
#define   u8 unsigned char
#define   uchar unsigned char
#define   uint unsigned int	
#define   u32 unsigned long	

//  内部地址
//****************************************
//BMP280 I2C address is 0x76(108)
#define	BMP280_I2C_ADDRESS   0x76	


#define	data   BUF	


static char BUF[24];       // 数据缓存区   


char BMP280_readRC; //读执行正确错误
char   *BMP280RES_C; 
 float BMP280_Temperature; 
 float BMP280_Pressure; 




sbit SCL = P2 ^ 0;
sbit SDA = P4 ^ 4;

// SDI/CSB 接3.3V --影响协议 HIGH=iic
// SDO接地 --影响地址  应该=0,ADDRESS=0x76





#define SCL_H         SCL = 1
#define SCL_L         SCL = 0
#define SDA_H         SDA = 1
#define SDA_L         SDA = 0
//#define SCL_read      SCL
#define SDA_read      SDA


/*
********************************************************************************
** 函数功能 ： 长延时函数	
******************************************************************************** */
//static void Delayms(u32 m)
//{
//  //u32 i;
//  //
//  //for(; m != 0; m--)	
//  //     for (i=0; i<500; i++);
//
//	DelayMs(m);
//}



/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
static void I2C_delay(void)
{
   u8 i=93; 
   while(i) 
   { 
     i--; 
   }  
}

#define delay5us I2C_delay


//static void delay5ms(void)
//{
//   //int i=5000;  
//   //while(i) 
//   //{ 
//   //  i--; 
//   //}  
//
//	DelayMs(5);
//}


/*******************************************************************************
* Function Name  : I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
static bool I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return FALSE;	//SDA线为低电平则总线忙,退出
	SDA_L;
	I2C_delay();
	if(SDA_read) return FALSE;	//SDA线为高电平则总线出错,退出
	SDA_L;
	I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
static void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 

/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
static void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}  

/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
static void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 

/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
static bool I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
	  I2C_delay();
      return FALSE;
	}
	SCL_L;
	I2C_delay();
	return TRUE;
}

/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
static void I2C_SendByte(u8 SendByte) //数据从高位到低位//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
		SCL_H;
        I2C_delay();
    }
    SCL_L;
}  

/*******************************************************************************
* Function Name  : I2C_ReadByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
static unsigned char I2C_ReadByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
	  SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
} 

//           
//单字节写入*******************************************
static bool Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)	 
{
  	if(!I2C_Start()) return FALSE;
    I2C_SendByte( SlaveAddress * 2 ); 
    if(!I2C_WaitAck())
	{
		//I2C_Stop();
		//return FALSE;
	}

    I2C_SendByte( REG_Address);      
    I2C_WaitAck();

    I2C_SendByte(REG_data);
    I2C_WaitAck(); 

    I2C_Stop(); 
    
    return TRUE;
}


// 读取*****************************************
static bool Many_Read(unsigned char SlaveAddress, unsigned char REG_Address, unsigned char ret_len )
{ 
	unsigned char i;

	if(!I2C_Start()) return BMP280_readRC = FALSE;
    I2C_SendByte( SlaveAddress * 2 ); 
    if(!I2C_WaitAck())
	{
		//I2C_Stop();
		//return BMP280_readRC = FALSE;
	}

    I2C_SendByte( REG_Address);      
    I2C_WaitAck();

    I2C_Start();
    I2C_SendByte( SlaveAddress * 2 + 1 );
    I2C_WaitAck();

	for( i = 0; i < ret_len ; i++ )
	{
		BUF[i] = I2C_ReadByte();
		if( i != ret_len - 1 ) I2C_Ack();
	}

    I2C_NoAck();
    I2C_Stop();
    return BMP280_readRC = TRUE;
}						      


#define   double float

static uint dig_T1;
static int dig_T2;
static int dig_T3;
static uint dig_P1;
static int dig_P2;
static int dig_P3;
static int dig_P4;
static int dig_P5;
static int dig_P6;
static int dig_P7;
static int dig_P8;
static int dig_P9;



void Reset_BMP280( void )
{
	BMP280RES_C = BUF;


	//Single_Write( BMP280_I2C_ADDRESS, 0xe0, 0xb6 );
	//DelayMs(999);


	// Read 24 bytes of data from address(0x88)
	Many_Read( BMP280_I2C_ADDRESS, 0x88 , 24 ); 
	if( BMP280_readRC == FALSE ) return;
      I2C_delay();
      I2C_delay();
	DelayMs(10);
	

	dig_T1 = data[1] * 256 + data[0];
	dig_T2 = data[3] * 256 + data[2];
	dig_T3 = data[5] * 256 + data[4];
	dig_P1 = data[7] * 256 + data[6];
	dig_P2 = data[9] * 256 + data[8];
	dig_P3 = data[11]* 256 + data[10];
	dig_P4 = data[13]* 256 + data[12];
	dig_P5 = data[15]* 256 + data[14];
	dig_P6 = data[17]* 256 + data[16];
	dig_P7 = data[19]* 256 + data[18];
	dig_P8 = data[21]* 256 + data[20];
	dig_P9 = data[23]* 256 + data[22];

	// Select control measurement register(0xF4)
	// Normal mode, temp and pressure over sampling rate = 1(0x27)
	Single_Write( BMP280_I2C_ADDRESS, 0xF4, 0x27 );
	DelayMs(10);

	// Select config register(0xF5)
	// Stand_by time = 1000 ms(0xA0)
	Single_Write( BMP280_I2C_ADDRESS, 0xF5, 0xA0 );
	DelayMs(10);

}

	 


// *******************
void Get_BMP280(void)
{
 long adc_p;
 long adc_t;
 double var1;
 double var2;
 double t_fine;
 double cTemp;
	double p;

	BMP280RES_C = BUF;

	//// Read 24 bytes of data from address(0x88)
	//Many_Read( BMP280_I2C_ADDRESS, 0x88 , 24 ); 
	//if( BMP280_readRC == FALSE ) return;
 //     I2C_delay();
 //     I2C_delay();
	//DelayMs(10);
	//

	//dig_T1 = data[1] * 256 + data[0];
	//dig_T2 = data[3] * 256 + data[2];
	//dig_T3 = data[5] * 256 + data[4];
	//dig_P1 = data[7] * 256 + data[6];
	//dig_P2 = data[9] * 256 + data[8];
	//dig_P3 = data[11]* 256 + data[10];
	//dig_P4 = data[13]* 256 + data[12];
	//dig_P5 = data[15]* 256 + data[14];
	//dig_P6 = data[17]* 256 + data[16];
	//dig_P7 = data[19]* 256 + data[18];
	//dig_P8 = data[21]* 256 + data[20];
	//dig_P9 = data[23]* 256 + data[22];

	//// Select control measurement register(0xF4)
	//// Normal mode, temp and pressure over sampling rate = 1(0x27)
	//Single_Write( BMP280_I2C_ADDRESS, 0xF4, 0x27 );
	//DelayMs(10);

	//// Select config register(0xF5)
	//// Stand_by time = 1000 ms(0xA0)
	//Single_Write( BMP280_I2C_ADDRESS, 0xF5, 0xA0 );
	//DelayMs(10);

	
	// Read from register(0xF7)
	Many_Read( BMP280_I2C_ADDRESS, 0xF7 , 6 ); 
	//DelayMs(10);

	// Convert pressure and temperature data to 19-bits
	 adc_p = (((long)data[0] * 65536L) + ((long)data[1] * 256L) + (long)(data[2] & 0xF0)) / 16;
	 adc_t = (((long)data[3] * 65536L) + ((long)data[4] * 256L) + (long)(data[5] & 0xF0)) / 16;
	 //int adc_T = ((tmp_buff[0]<<16)|(tmp_buff[1]<<8)|(tmp_buff[2]))>>4; 
	 //adc_t =    	( ( (long)(data[3]) ) << 16 ) | 
		//			( ( (long)(data[4]) ) <<  8 ) | 
		//			  ( data[5] & 0xF0  )    ; 
	 //adc_t /= 16; 
		
	 // Temperature offset calculations
	 var1 = (((double)adc_t) / 16384.0 - ((double)dig_T1) / 1024.0) * ((double)dig_T2);
	 var2 = ((((double)adc_t) / 131072.0 - ((double)dig_T1) / 8192.0) *(((double)adc_t)/131072.0 - ((double)dig_T1)/8192.0)) * ((double)dig_T3);
	 t_fine = (long)(var1 + var2);
	 cTemp = (var1 + var2) / 5120.0;
	 BMP280_Temperature = cTemp * 1.8 + 32;

	 // Pressure offset calculations
	var1 = ((double)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
	var1 = (((double) dig_P3) * var1 * var1 / 524288.0 + ((double) dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((double)dig_P1);
	 p = 1048576.0 - (double)adc_p;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double) dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double) dig_P8) / 32768.0;
	 BMP280_Pressure = (p + (var1 + var2 + ((double)dig_P7)) / 16.0) ; 

}



