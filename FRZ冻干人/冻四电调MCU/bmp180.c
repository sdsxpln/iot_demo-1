/*
 * BMP085模块
 * 用途：BMP085模块IIC测试程序
 */
//#include "reg52.h"
#include "UNIQ_ID.h"
#include  <math.h>    //Keil library  
#include  <stdlib.h>  //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H> //Keil library  
#include "Delay_12M.h"
#include "bmp180.h"

#define   uchar unsigned char
#define   uint unsigned int	
#define   u8 unsigned char


sbit  SCL = P2 ^ 0;      //IIC时钟引脚定义
sbit  SDA = P4 ^ 4;      //IIC数据引脚定义


long  g_bmp085_temperature;
long  g_bmp085_pressure;


#define	BMP085_SlaveAddress   0xee	  //定义器件在IIC总线中的从地址                               

#define OSS 0	// Oversampling Setting (note: code is not set up to use other OSS values)
							   
typedef unsigned char  BYTE;
typedef unsigned short WORD;
   	
short ac1;
short ac2; 
short ac3; 
unsigned short ac4;
unsigned short ac5;
unsigned short ac6;
short b1; 
short b2;
short mb;
short mc;
short md;

void delay(unsigned int k);

void  Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data);   //单个写入数据
uchar Single_Read(uchar REG_Address);                                      //单个读取内部寄存器数据
void  Multiple_Read(uchar,uchar);                                          //连续的读取内部寄存器数据
//------------------------------------
void I2C_delay();
void Delay5ms();
void BMP085_Start();
void BMP085_Stop();
void BMP085_SendACK(bit ack);
bit  BMP085_RecvACK();
void BMP085_SendByte(BYTE dat);
BYTE BMP085_RecvByte();
void BMP085_ReadPage();
void BMP085_WritePage();
//-----------------------------------

/**********************   1=100微秒  *********/

/*******************************/
//void delay(unsigned int k)	
//{						
//	unsigned int i,j;				
//	for(i=0;i<k;i++)
//	{			
//		for(j=0;j<121;j++)			
//		{;}
//	}						
//}
static void delay(unsigned int k)	
{
	unsigned int ll;
	for( ll = 0 ; ll < k; ll++ )
		DelayUs2x(50);	 
}




/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
static void I2C_delay(void)
{
   u8 i=33; 
   while(i) 
   { 
     i--; 
   }  
}
/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
//void I2C_delay()
//{
//    _nop_();_nop_();_nop_();_nop_();
//    _nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();
//}

 

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
//void Delay5ms()
//{
//    WORD n = 560;
//    while (n--);
//}

static void Delay5ms()
{
    DelayMs(5);
}



/**************************************
起始信号
**************************************/
void BMP085_Start()
{
    SDA = 1;                    //拉高数据线
    I2C_delay(); 
	SCL = 1;                    //拉高时钟线
    I2C_delay();                 //延时
    SDA = 0;                    //产生下降沿
    I2C_delay();                 //延时
    SCL = 0;                    //拉低时钟线
    I2C_delay(); 
}

/**************************************
停止信号
**************************************/
void BMP085_Stop()
{
    SDA = 0;                    //拉低数据线
    I2C_delay(); 
    SCL = 1;                    //拉高时钟线
    I2C_delay();                 //延时
    SDA = 1;                    //产生上升沿
    I2C_delay();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void BMP085_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    I2C_delay(); 
    SCL = 1;                    //拉高时钟线
    I2C_delay();                 //延时
    SCL = 0;                    //拉低时钟线
    I2C_delay();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit BMP085_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    I2C_delay();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    I2C_delay();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void BMP085_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        I2C_delay(); 
        SCL = 1;                //拉高时钟线
        I2C_delay();             //延时
        SCL = 0;                //拉低时钟线
        I2C_delay();             //延时
    }
    BMP085_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE BMP085_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        I2C_delay();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        I2C_delay();             //延时
    }
    return dat;
}
/*
//单字节写入BMP085内部数据*******************************

void Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data)
{
    BMP085_Start();                  //起始信号
    BMP085_SendByte(SlaveAddress);   //发送设备地址+写信号
    BMP085_SendByte(REG_Address);    //内部寄存器地址
    BMP085_SendByte(REG_data);       //内部寄存器数据
    BMP085_Stop();                   //发送停止信号
}
*/
/*
//单字节读取BMP085内部数据********************************
uchar Single_Read(uchar REG_Address)
{  uchar REG_data;
    BMP085_Start();                          //起始信号
    BMP085_SendByte(BMP085_SlaveAddress);           //发送设备地址+写信号
    BMP085_SendByte(REG_Address);            //发送存储单元地址	
    BMP085_Start();                          //起始信号
    BMP085_SendByte(BMP085_SlaveAddress+1);         //发送设备地址+读信号
    REG_data=BMP085_RecvByte();              //读出寄存器数据
	BMP085_SendACK(1);   
	BMP085_Stop();                           //停止信号
    return REG_data; 
}
*/
//*********************************************************
//读出BMP085内部数据,连续两个
//*********************************************************
short Multiple_read(uchar ST_Address)
{   
	uchar msb, lsb;
	short _data;
    BMP085_Start();                          //起始信号
    BMP085_SendByte(BMP085_SlaveAddress);    //发送设备地址+写信号
    BMP085_SendByte(ST_Address);             //发送存储单元地址
    BMP085_Start();                          //起始信号
    BMP085_SendByte(BMP085_SlaveAddress+1);         //发送设备地址+读信号

    msb = BMP085_RecvByte();                 //BUF[0]存储
    BMP085_SendACK(0);                       //回应ACK
    lsb = BMP085_RecvByte();     
	BMP085_SendACK(1);                       //最后一个数据需要回NOACK

    BMP085_Stop();                           //停止信号
    Delay5ms();
    _data = msb << 8;
	_data |= lsb;	
	return _data;
}

//********************************************************************
long bmp085ReadTemp(void)
{
    BMP085_Start();                  //起始信号
    BMP085_SendByte(BMP085_SlaveAddress);   //发送设备地址+写信号
    BMP085_SendByte(0xF4);	          // write register address
    BMP085_SendByte(0x2E);       	// write register data for temp
    BMP085_Stop();                   //发送停止信号
	delay(10);	// max time is 4.5ms
	
	return (long) Multiple_read(0xF6);
}
//*************************************************************
long bmp085ReadPressure(void)
{
	long pressure = 0;

    BMP085_Start();                   //起始信号
    BMP085_SendByte(BMP085_SlaveAddress);   //发送设备地址+写信号
    BMP085_SendByte(0xF4);	          // write register address
    BMP085_SendByte(0x34);       	  // write register data for pressure
    BMP085_Stop();                    //发送停止信号
	delay(10);    	                  // max time is 4.5ms
	
	pressure = Multiple_read(0xF6);
	pressure &= 0x0000FFFF;
	
	return pressure;	
	//return (long) bmp085ReadShort(0xF6);
}

//**************************************************************

//初始化BMP085，根据需要请参考pdf进行修改**************
void Init_BMP085()
{
	ac1 = Multiple_read(0xAA);
	ac2 = Multiple_read(0xAC);
	ac3 = Multiple_read(0xAE);
	ac4 = Multiple_read(0xB0);
	ac5 = Multiple_read(0xB2);
	ac6 = Multiple_read(0xB4);
	b1 =  Multiple_read(0xB6);
	b2 =  Multiple_read(0xB8);
	mb =  Multiple_read(0xBA);
	mc =  Multiple_read(0xBC);
	md =  Multiple_read(0xBE);
}


//***********************************************************************
void bmp085Convert()
{
	long ut;
	long up;
	long x1, x2, b5, b6, x3, b3, p;
	unsigned long b4, b7;
	long  temperature;
	long  pressure;
	
	ut = bmp085ReadTemp();
	ut = bmp085ReadTemp();	   // 读取温度
	up = bmp085ReadPressure();
	up = bmp085ReadPressure();  // 读取压强
	
	x1 = ((long)ut - ac6) * ac5 >> 15;
	x2 = ((long) mc << 11) / (x1 + md);
	b5 = x1 + x2;
	 temperature = (b5 + 8) >> 4;
	g_bmp085_temperature = temperature;

     //*************
	b6 = b5 - 4000;
	x1 = (b2 * (b6 * b6 >> 12)) >> 11;
	x2 = ac2 * b6 >> 11;
	x3 = x1 + x2;
	b3 = (((long)ac1 * 4 + x3) + 2)/4;
	x1 = ac3 * b6 >> 13;
	x2 = (b1 * (b6 * b6 >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (ac4 * (unsigned long) (x3 + 32768)) >> 15;
	b7 = ((unsigned long) up - b3) * (50000 >> OSS);
	if( b7 < 0x80000000)
	     p = (b7 * 2) / b4 ;
           else  
		    p = (b7 / b4) * 2;
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	g_bmp085_pressure =  pressure = p + ((x1 + x2 + 3791) >> 4);
}

//*********************************************************
//******主程序******** 
//int j;
//unsigned char g_sz[33];
//long  a_pressure[4];
//unsigned char a_light = 0;
//
//void main()
//{
//	//初始化
//	TMOD=0X01;		 //设置定时器0为模式一，即16位计算模式 
//	TH0 = (65536-55000) / 256;
//	TL0 = (65536-55000) % 256;
//	EA=0;		// 总中断 
//	ET0=0;		//开启定时器0中断 
//	TR0=1;		//启动定时器0 
//
//    SCON  = 0x50;	   // SCON: 模式 1, 8-bit UART, 使能接收 
//    TMOD |= 0x20;      // TMOD: timer 1, mode 2, 8-bit 重装 
//    TH1   = 0xFD;     // TH1:  重装值 9600 波特率 晶振 11.0592MHz 
//    TR1   = 1;        // TR1:  timer 1 打开 
//    ES    = 0;        //打开串口中断 
//
//
//	delay(50);	         //上电延时		
//	Init_BMP085();       //初始化BMP085 
//	while(1)             //循环
//	{ 
//		bmp085Convert();
//
//		//myltoa( g_sz, g_bmp085_temperature, 0x00 );
//		myltoa( g_sz, g_bmp085_pressure, 0x00 );
//
//		for( j = 0; ; j++ )
//		{
//			if( g_sz[j] == 0 )
//				break;
//
//			SBUF = g_sz[j]; 
//			while(!TI); 
//			TI = 0;
//		}
//
//		SBUF = 0x0d; 
//		while(!TI); 
//		TI = 0;
//
//		SBUF = 0x0a; 
//		while(!TI); 
//		TI = 0;
//
//		//判断
//		a_pressure[0] = a_pressure[1];
//		a_pressure[1] = a_pressure[2];
//		a_pressure[2] = a_pressure[3];
//		a_pressure[3] = g_bmp085_pressure;
//
//		if( a_pressure[0] < a_pressure[1] &&
//			a_pressure[1] < a_pressure[2] &&
//			a_pressure[2] < a_pressure[3] ||  
//			a_pressure[3] - a_pressure[0] > 30 )
//		{
//			if( a_light == 1 )
//			{
//				delay(222); 
//			}
//			a_light = 0;
//		}
//
//		if( a_pressure[0] > a_pressure[1] &&
//			a_pressure[1] > a_pressure[2] &&
//			a_pressure[2] > a_pressure[3] ||  
//			a_pressure[0] - a_pressure[3] > 30 )
//		{
//			if( a_light == 0 )
//				delay(222); 
//			a_light = 1;
//		}
//		
//		LIGHT = a_light ? 1 : 0;
//
//		delay(2); 
//	}
//} 



