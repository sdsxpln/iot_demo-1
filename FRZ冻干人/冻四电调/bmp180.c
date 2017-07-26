/*
 * BMP085ģ��
 * ��;��BMP085ģ��IIC���Գ���
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


sbit  SCL = P4 ^ 3;      //IICʱ�����Ŷ���
sbit  SDA = P4 ^ 2;      //IIC�������Ŷ���


long  g_bmp085_temperature;
long  g_bmp085_pressure;


#define	BMP085_SlaveAddress   0xee	  //����������IIC�����еĴӵ�ַ                               

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

void  Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data);   //����д������
uchar Single_Read(uchar REG_Address);                                      //������ȡ�ڲ��Ĵ�������
void  Multiple_Read(uchar,uchar);                                          //�����Ķ�ȡ�ڲ��Ĵ�������
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

/**********************   1=100΢��  *********/

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
   u8 i=3; 
   while(i) 
   { 
     i--; 
   }  
}
/**************************************
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
//void I2C_delay()
//{
//    _nop_();_nop_();_nop_();_nop_();
//    _nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();
//}

 

/**************************************
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
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
��ʼ�ź�
**************************************/
void BMP085_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    I2C_delay();                 //��ʱ
    SDA = 0;                    //�����½���
    I2C_delay();                 //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void BMP085_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    I2C_delay();                 //��ʱ
    SDA = 1;                    //����������
    I2C_delay();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BMP085_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    I2C_delay();                 //��ʱ
    SCL = 0;                    //����ʱ����
    I2C_delay();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit BMP085_RecvACK()
{
    SCL = 1;                    //����ʱ����
    I2C_delay();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    I2C_delay();                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BMP085_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        I2C_delay();             //��ʱ
        SCL = 0;                //����ʱ����
        I2C_delay();             //��ʱ
    }
    BMP085_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE BMP085_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        I2C_delay();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        I2C_delay();             //��ʱ
    }
    return dat;
}
/*
//���ֽ�д��BMP085�ڲ�����*******************************

void Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data)
{
    BMP085_Start();                  //��ʼ�ź�
    BMP085_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    BMP085_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ
    BMP085_SendByte(REG_data);       //�ڲ��Ĵ�������
    BMP085_Stop();                   //����ֹͣ�ź�
}
*/
/*
//���ֽڶ�ȡBMP085�ڲ�����********************************
uchar Single_Read(uchar REG_Address)
{  uchar REG_data;
    BMP085_Start();                          //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress);           //�����豸��ַ+д�ź�
    BMP085_SendByte(REG_Address);            //���ʹ洢��Ԫ��ַ	
    BMP085_Start();                          //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=BMP085_RecvByte();              //�����Ĵ�������
	BMP085_SendACK(1);   
	BMP085_Stop();                           //ֹͣ�ź�
    return REG_data; 
}
*/
//*********************************************************
//����BMP085�ڲ�����,��������
//*********************************************************
short Multiple_read(uchar ST_Address)
{   
	uchar msb, lsb;
	short _data;
    BMP085_Start();                          //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress);    //�����豸��ַ+д�ź�
    BMP085_SendByte(ST_Address);             //���ʹ洢��Ԫ��ַ
    BMP085_Start();                          //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress+1);         //�����豸��ַ+���ź�

    msb = BMP085_RecvByte();                 //BUF[0]�洢
    BMP085_SendACK(0);                       //��ӦACK
    lsb = BMP085_RecvByte();     
	BMP085_SendACK(1);                       //���һ��������Ҫ��NOACK

    BMP085_Stop();                           //ֹͣ�ź�
    Delay5ms();
    _data = msb << 8;
	_data |= lsb;	
	return _data;
}

//********************************************************************
long bmp085ReadTemp(void)
{
    BMP085_Start();                  //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress);   //�����豸��ַ+д�ź�
    BMP085_SendByte(0xF4);	          // write register address
    BMP085_SendByte(0x2E);       	// write register data for temp
    BMP085_Stop();                   //����ֹͣ�ź�
	delay(10);	// max time is 4.5ms
	
	return (long) Multiple_read(0xF6);
}
//*************************************************************
long bmp085ReadPressure(void)
{
	long pressure = 0;

    BMP085_Start();                   //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress);   //�����豸��ַ+д�ź�
    BMP085_SendByte(0xF4);	          // write register address
    BMP085_SendByte(0x34);       	  // write register data for pressure
    BMP085_Stop();                    //����ֹͣ�ź�
	delay(10);    	                  // max time is 4.5ms
	
	pressure = Multiple_read(0xF6);
	pressure &= 0x0000FFFF;
	
	return pressure;	
	//return (long) bmp085ReadShort(0xF6);
}

//**************************************************************

//��ʼ��BMP085��������Ҫ��ο�pdf�����޸�**************
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
	ut = bmp085ReadTemp();	   // ��ȡ�¶�
	up = bmp085ReadPressure();
	up = bmp085ReadPressure();  // ��ȡѹǿ
	
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
//******������******** 
//int j;
//unsigned char g_sz[33];
//long  a_pressure[4];
//unsigned char a_light = 0;
//
//void main()
//{
//	//��ʼ��
//	TMOD=0X01;		 //���ö�ʱ��0Ϊģʽһ����16λ����ģʽ 
//	TH0 = (65536-55000) / 256;
//	TL0 = (65536-55000) % 256;
//	EA=0;		// ���ж� 
//	ET0=0;		//������ʱ��0�ж� 
//	TR0=1;		//������ʱ��0 
//
//    SCON  = 0x50;	   // SCON: ģʽ 1, 8-bit UART, ʹ�ܽ��� 
//    TMOD |= 0x20;      // TMOD: timer 1, mode 2, 8-bit ��װ 
//    TH1   = 0xFD;     // TH1:  ��װֵ 9600 ������ ���� 11.0592MHz 
//    TR1   = 1;        // TR1:  timer 1 �� 
//    ES    = 0;        //�򿪴����ж� 
//
//
//	delay(50);	         //�ϵ���ʱ		
//	Init_BMP085();       //��ʼ��BMP085 
//	while(1)             //ѭ��
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
//		//�ж�
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



