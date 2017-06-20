#include "hmc5883l.h"

#include "stdio.h"
#include "math.h"
#include "usart1.h"
#include "systick.h"



int16_t magX,magY,magZ;
float magGain[3]={0.0};
int16_t offsetX , offsetY , offsetZ ;


int _abs( int p)
{
    return p>0?p:-p;
}

void updateHMC5883L(void) {
	
	uint8_t i2cData[6]={0};


	I2C_BufferRead(HMC5883L_ADR, i2cData,0x03, 6);

	
  magX = ((i2cData[0] << 8) | i2cData[1]);
  magZ = ((i2cData[2] << 8) | i2cData[3]);
  magY = ((i2cData[4] << 8) | i2cData[5]);
	
	#ifdef DUBUG_MAG
	{
		char buf[100]={0};
		sprintf(buf,"\nmagX=%d   magY=%d   magZ=%d \n",magX,magY,magZ);
		myPrintf(buf);
	}
	#endif
}


void Init_Hmc5883(void)
{
	//ADR  DATA  REG
	I2C_ByteWrite(HMC5883L_ADR,0x00,0x02) ; //选择模式寄存器 , 连续测量模式:0x00,单一测量模式:0x01  
	delay_x_ms(100);
	calibrateMag();
	get_offset();
}


void calibrateMag(void) 
{
	int16_t magPosOff[3] = { 0, 0, 0 };
	int16_t magNegOff[3] = { 0, 0, 0 };

	I2C_ByteWrite(HMC5883L_ADR, 0x11, 0x00);//选择配置寄存器A  
	
	delay_x_ms(100);
	
	updateHMC5883L();
	
	magPosOff[0]=magX;
	magPosOff[1]=magY;
	magPosOff[2]=magZ;

	I2C_ByteWrite(HMC5883L_ADR, 0x12, 0x00);

	delay_x_ms(100);
	updateHMC5883L();

	magNegOff[0]=magX;
	magNegOff[1]=magY;
	magNegOff[2]=magZ;

	I2C_ByteWrite(HMC5883L_ADR, 0x10, 0x00); 

	magGain[0] = -2500 / (float)(magNegOff[0] - magPosOff[0]);
  magGain[1] = -2500 / (float)(magNegOff[1] - magPosOff[1]);
  magGain[2] = -2500 / (float)(magNegOff[2] - magPosOff[2]);
	
	#ifdef DUBUG_MAG
	{
		char buf[100]={0};
		sprintf(buf,"\nMag cal  X:%8.3f  Y:%8.3f  Z:%8.3f\n",(float)(magNegOff[0] - magPosOff[0]),(float)(magNegOff[1] - magPosOff[1]),(float)(magNegOff[2] - magPosOff[2]));
		myPrintf(buf);
		sprintf(buf,"\r\nGain   X:%8.3f  Y:%8.3f  Z:%8.3f\n",magGain[0],magGain[1],magGain[2]);
		myPrintf(buf);
	}
	#endif
}


void get_offset(void)
{
  int xMax, xMin, yMax, yMin, zMax, zMin, i;  

	updateHMC5883L();
	
  xMax=xMin=magX;  
  yMax=yMin=magY;  
  zMax=zMin=magZ;  
	
  offsetX = offsetY = offsetZ = 0; 

	
	#ifdef DUBUG_MAG
	myPrintf("开始校准电子罗盘......\r\n");  
  myPrintf("请全方位转动你的电子罗盘大约20秒钟以完成校准\r\n"); 
	#endif
	
	for(i=0;i<200;i++)  
  {  
    updateHMC5883L();
    // 计算最大值与最小值  
    // 计算传感器绕X,Y,Z轴旋转时的磁场强度最大值和最小值  
    if (magX > xMax)  
      xMax = magX;  
    if (magX < xMin )  
      xMin = magX;  
    if(magY > yMax )  
      yMax = magY;  
    if(magY < yMin )  
      yMin = magY;  
    if(magZ > zMax )  
      zMax = magZ;  
    if(magZ < zMin )  
      zMin = magZ;  
   
    delay_x_ms(100);  
   
    if(i%10 == 0)  
    {  
			#ifdef DUBUG_MAG
			{ 
				char buf[60]={0};
				sprintf(buf,"\r\nxMax:%8.3f xMin:%8.3f\r\n",(double)xMax,(double)xMin);
				myPrintf(buf); 
				sprintf(buf,"\r\nyMax:%8.3f yMin:%8.3f\r\n",(double)yMax,(double)yMin);
				myPrintf(buf); 
				sprintf(buf,"\r\nzMax:%8.3f zMin:%8.3f\r\n",(double)zMax,(double)zMin);
				myPrintf(buf); 
			}
			#endif
     
    }  
		
  }

	if(_abs(xMax - xMin) > CalThreshold )  
	offsetX = (xMax + xMin)/2;  
	if(_abs(yMax - yMin) > CalThreshold )  
	offsetY = (yMax + yMin)/2;  
	if(_abs(zMax - zMin) > CalThreshold )  
	offsetZ = (zMax +zMin)/2;  

	#ifdef DUBUG_MAG
	{ 
		char buf[60]={0};
		
		sprintf(buf,"\r\noffsetX:%8.3f offsetY:%8.3f  offsetZ:%8.3f\r\n",(double)offsetX,(double)offsetY,(double)offsetZ);
	
		myPrintf(buf); 
	
	}
	#endif  
	
	
}


int calculateHeading(int* x ,int* y,int* z)  
{  
	int headingDegrees;
  float headingRadians = atan2((double)((*y)-offsetY),(double)((*x)-offsetX));  
  // 保证数据在0-2*PI之间  
  if(headingRadians < 0)  
    headingRadians += 2*PI;  
   
  headingDegrees = headingRadians * 180/PI;  
  headingDegrees += MagnetcDeclination; //磁偏角  
   
  // 保证数据在0-360之间  
  if(headingDegrees > 360)  
    headingDegrees -= 360;  
   
  return headingDegrees;  
}


void printf_Heading_angle(void)
{
	float head_angle=0;
	int x,y,z;
	
	updateHMC5883L();
	x=magX;
	y=magY;
	z=magZ;
	head_angle=calculateHeading(&x,&y,&z);
	
	#ifdef DUBUG_MAG
	{ 
		char buf[60]={0};
		
		sprintf(buf,"\r\nangle(x,y):%8.3f \r\n",(double)head_angle);
		
		myPrintf(buf); 
		
	}
	#endif 
}






