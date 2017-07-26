/****** **************/
//#include <reg52.h>
#include "UNIQ_ID.h"
#include "Delay_12M.h"
#include "mpu9250iica.h"


//2017-06-06



sbit SCL = P2 ^ 0;
sbit SDA = P4 ^ 4;

//只接电源和IIC。实测电源用5V，IO用3.3V可工作。描述中3至5V都可工作。



#define   bool unsigned char
#define   TRUE 1
#define   FALSE 0
#define   u8 unsigned char
#define   uchar unsigned char
#define   uint unsigned int	
#define   u32 unsigned long	

// 定义MPU9250内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48

		
#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08


#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		  0x75	//IIC地址寄存器(默认数值0x68，只读)



//****************************
/*
mpu9250内部为mpu6500和AK8963的组合。是两个不同的I2C地址。读取加速度和陀螺仪需要对mpu6500的I2C地址及进行操作，读取磁力计需要对ak8963地址进行操作。
mpu6500根据电路中AD0的不同，地址为0x68或者0x69, 磁力计为0x0C（在mpu9250中，电路已经确定，地址无法更改）。
在读取时，注意需要人工将地址左移一位（I2C读写为左对齐，第8位要存读写标志位），mpu6500为0xD0或是0xD2,磁力计为0x18（如果I2C读写中进行了左移操作，那就不用人工左移一位）*/
#define	GYRO_ADDRESS   0xD0	  //陀螺地址
#define MAG_ADDRESS    0x18   //磁场地址
#define ACCEL_ADDRESS  0xD0 



static unsigned char BUF[10];       //接收数据缓存区
//static char  test=0; 				 //IIC用到

//short T_X,T_Y,T_Z,T_T;		 //X,Y,Z轴，温度
static int T_X;
static int T_Y;
static int T_Z;
static int T_T;		 //X,Y,Z轴，温度


float MPU9250RES_BUF[4];    // 数据保存处

char MPU9250_readRC; //读执行正确错误
float *MPU9250RES_F; 
int   *MPU9250RES_I;   
char  MPU9250RES_TYPE = 0;  // 0=float type   1=int type

//************************************
/*模拟IIC端口输出输入定义*/
//#define SCL_H         GPIOB->BSRR = GPIO_Pin_6
//#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 
//   
//#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
//#define SDA_L         GPIOB->BRR  = GPIO_Pin_7
//
//#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
//#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

//
//sbit SCL = P1 ^ 6;
//sbit SDA = P3 ^ 4;


#define SCL_H         SCL = 1
#define SCL_L         SCL = 0
#define SDA_H         SDA = 1
#define SDA_L         SDA = 0
//#define SCL_read      SCL
#define SDA_read      SDA


/*
********************************************************************************
** 函数功能 ： 长延时函数	
********************************************************************************
*/
static void Delayms(u32 m)
{
  //u32 i;
  //
  //for(; m != 0; m--)	
  //     for (i=0; i<500; i++);

	DelayMs(m);
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

static void delay5ms(void)
{
   //int i=5000;  
   //while(i) 
   //{ 
   //  i--; 
   //}  

	DelayMs(5);
}


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
//static void I2C_Ack(void)
//{	
//	SCL_L;
//	I2C_delay();
//	SDA_L;
//	I2C_delay();
//	SCL_H;
//	I2C_delay();
//	SCL_L;
//	I2C_delay();
//}  

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
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
static unsigned char I2C_RadeByte(void)  //数据从高位到低位//
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
//ZRX          
//单字节写入*******************************************

static bool Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte(REG_Address );   //设置低起始地址      
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    delay5ms();
    return TRUE;
}

//单字节读取*****************************************
static unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
	if(!I2C_Start())return MPU9250_readRC=FALSE;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck())
	{
		I2C_Stop();
		//test=1; 
		return MPU9250_readRC=FALSE;
	}
    I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

	REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();
    MPU9250_readRC= TRUE;
	return REG_data;

}						      




//初始化MPU9250，根据需要请参考pdf进行修改************************
void Init_MPU9250(void)
{

	MPU9250RES_F = MPU9250RES_BUF; 
	MPU9250RES_I = (int*)MPU9250RES_F;
	MPU9250RES_TYPE = 0;

/*
   Single_Write(GYRO_ADDRESS,PWR_M, 0x80);   //
   Single_Write(GYRO_ADDRESS,SMPL, 0x07);    //
   Single_Write(GYRO_ADDRESS,DLPF, 0x1E);    //±2000°
   Single_Write(GYRO_ADDRESS,INT_C, 0x00 );  //
   Single_Write(GYRO_ADDRESS,PWR_M, 0x00);   //
*/
  Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x07);
	Single_Write(GYRO_ADDRESS,CONFIG, 0x06);
	Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);
	Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);
  //----------------
//	Single_Write(GYRO_ADDRESS,0x6A,0x00);//close Master Mode	

}

	
//******读取MPU9250数据****************************************
void READ_MPU9250_ACCEL(void)
{ 

   BUF[0]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_L); if( MPU9250_readRC==FALSE ) return;
   BUF[1]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_X=	(BUF[1]<<8)|BUF[0];
   //T_X/=164; 	
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[0] = T_X;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[0] = (float)T_X/164.0; 	   //读取计算X轴数据

   BUF[2]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_L); if( MPU9250_readRC==FALSE ) return;
   BUF[3]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_Y=	(BUF[3]<<8)|BUF[2];
   //T_Y/=164; 						   //读取计算Y轴数据
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[1] = T_Y;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[1] = (float)T_Y/164.0; 

   BUF[4]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_L); if( MPU9250_readRC==FALSE ) return;
   BUF[5]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_Z=	(BUF[5]<<8)|BUF[4];
   //T_Z/=164; 					       //读取计算Z轴数据
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[2] = T_Z;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[2] = (float)T_Z/164.0; 
 
}


void READ_MPU9250_GYRO(void)
{ 

   BUF[0]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_L);  if( MPU9250_readRC==FALSE ) return;
   BUF[1]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_X=	(BUF[1]<<8)|BUF[0];
   //T_X/=16.4; 						   //读取计算X轴数据
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[0] = T_X;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[0] = (float)T_X/16.40;  

   BUF[2]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_L); if( MPU9250_readRC==FALSE ) return;
   BUF[3]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_Y=	(BUF[3]<<8)|BUF[2];
   //T_Y/=16.4; 						   //读取计算Y轴数据
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[1] = T_Y;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[1] = (float)T_Y/16.40; 

   BUF[4]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_L); if( MPU9250_readRC==FALSE ) return;
   BUF[5]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_Z=	(BUF[5]<<8)|BUF[4];
   //T_Z/=16.4; 					       //读取计算Z轴数据
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[2] = T_Z;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[2] = (float)T_Z/16.4; 
 
 


   BUF[6]=Single_Read(GYRO_ADDRESS,TEMP_OUT_L);  if( MPU9250_readRC==FALSE ) return;
   BUF[7]=Single_Read(GYRO_ADDRESS,TEMP_OUT_H);  if( MPU9250_readRC==FALSE ) return;
   T_T=(BUF[7]<<8)|BUF[6];
   //T_T = 35+ ((float) (T_T + 13200)) / 280;// 读取计算出温度
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[3] = T_T;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[3] = 35 + ((float) (T_T + 13200L)) / 280.0;// 读取计算出温度
}


void READ_MPU9250_MAG(void)
{ 
   Single_Write(GYRO_ADDRESS,0x37,0x02);//turn on Bypass Mode 
   Delayms(10);	
   Single_Write(MAG_ADDRESS,0x0A,0x01);
   Delayms(10);	
   BUF[0]=Single_Read (MAG_ADDRESS,MAG_XOUT_L); if( MPU9250_readRC==FALSE ) return;
   BUF[1]=Single_Read (MAG_ADDRESS,MAG_XOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_X=(BUF[1]<<8)|BUF[0];
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[0] = T_X;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[0] = (float)T_X;  

   BUF[2]=Single_Read(MAG_ADDRESS,MAG_YOUT_L); if( MPU9250_readRC==FALSE ) return;
   BUF[3]=Single_Read(MAG_ADDRESS,MAG_YOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_Y=	(BUF[3]<<8)|BUF[2];   						   //读取计算Y轴数据
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[1] = T_Y;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[1] = (float)T_Y;  
	 
   BUF[4]=Single_Read(MAG_ADDRESS,MAG_ZOUT_L); if( MPU9250_readRC==FALSE ) return;
   BUF[5]=Single_Read(MAG_ADDRESS,MAG_ZOUT_H); if( MPU9250_readRC==FALSE ) return;
   T_Z=	(BUF[5]<<8)|BUF[4]; 					       //读取计算Z轴数据
   if( MPU9250RES_TYPE == 1 ) MPU9250RES_I[2] = T_Z;
   if( MPU9250RES_TYPE == 0 ) MPU9250RES_F[2] = (float)T_Z;  
}



