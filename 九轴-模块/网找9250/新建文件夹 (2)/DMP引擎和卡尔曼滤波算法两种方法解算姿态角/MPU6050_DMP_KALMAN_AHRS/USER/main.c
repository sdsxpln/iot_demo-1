/******************************************
 * 文件名  ：main.c
 * 描述    : DMP引擎和卡尔曼滤波算法两种方法解算姿态角    
 * 库版本  ：ST3.5.0
 * Author  ： 朝阳
 * QQ      ：547336083
*********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "eeprom.h"
#include "I2C.h"
#include "mpu6050.h"
#include "systick.h"
#include "twatch.h"
#include "inv_mpu.h"
#include "config.h"
#include "hmc5883l.h"
#include "math.h"
#include "kalman.h"

//#define LIMIT_PITCH  //使用哪种方法解算俯仰角和横滚角选择
#define USE_GYRO   //使用原始陀螺仪数据积分姿态角还是使用无偏卡尔曼滤波器滤波之后的陀螺仪数据解算姿态角
//#define USE_DMP  //是否使用MPU6050内置的DMP引擎解算姿态角

#define DEBUG  //DEBUG 模式下会通过串口1打印输出解算结果

double exroll,expitch,exyaw;//三角函数求取的欧拉角
double gyroXangle, gyroYangle, gyroZangle; // 只使用陀螺仪计算得到的角度
double compAngleX, compAngleY, compAngleZ; // 使用无偏移卡尔曼滤波器计算的陀螺仪角度
double gyroXrate,gyroYrate,gyroZrate; //原始陀螺仪数据 度/秒

double kalAngleX, kalAngleY, kalAngleZ; //卡尔曼滤波器求取的欧拉角
void calcPitchRoll(void);//两种方法解算俯仰角和横滚角，方法1和方法2的区别仅仅是俯仰角和横滚角的意义与MPU6050的芯片的物理方向有不同的对应关系，通过实验数据很容易明白
		
void calcYaw(void);//使用三轴磁强计数据和卡尔曼滤波器计算得到的俯仰角和横滚角估算偏航角Yaw

int main(void)
{	
	float inpitch,inroll,inyaw; 		//欧拉角
	uint32_t eular_cnt=0,soft_cnt=0;
	int32_t idleLoops=0;
	uint32_t lastTime;
	float idlePerf;
	uint16_t count=0;
	uint32_t get_data_time=0;
	
	char buf[100]={0};
	/* USART1 config 9600 8-N-1 */
	USART1_Config();
	NVIC_Configuration();
	
	initSystick();
	bsp_I2c_Init();
	/* I2C 外设初始化 for (EEPROM) */
	I2c_EEPROM_Init();
	
	Init_MPU6050();
	idleMax=GetIdleMax();//获取CPU空闲状态下的1ms最大计数值,后面用来计算CPU使用率
	myPrintf("获取CPU空闲状态下的1ms最大计数值,后面用来计算CPU使用率\r\n");
#ifdef USE_DMP //如果使用DMP引擎解算姿态角
	{
		uint8_t init_Try=10;//初始化重试次数
		while(mpu_dmp_init()&&init_Try!=0)
		{
			myPrintf("mpu_dmp_init Exeing\r\n");
			init_Try--;
		}
		if(0!=init_Try)
		myPrintf("mpu_dmp_init Exeing ok\r\n");
		else myPrintf("mpu_dmp_init Exeing Fail\r\n");
	}
#else //否则使用卡尔曼滤波器+互补滤波器+三角函数解算姿态角

	Init_Hmc5883();//初始化HMC5883
	
	xInit_Kalman();//初始化卡尔曼滤波器
	yInit_Kalman();
	zInit_Kalman();
	
	get_Accel_Gyro_Temp(&six_axis);//获取9轴姿态数据
	updateHMC5883L(); //获取9轴姿态数据
	
	calcPitchRoll();
	calcYaw();//第一次计算
	
	xKalmanSetAngle(exroll);//卡尔曼输入初始角度 Roll
	gyroXangle = exroll;
  compAngleX = exroll;
	
	
	yKalmanSetAngle(expitch); //卡尔曼输入初始角度Pitch
  gyroYangle = expitch;
  compAngleY = expitch;
	
	zKalmanSetAngle(exyaw); //卡尔曼输入初始角度 yaw
  gyroZangle = exyaw;
  compAngleZ = exyaw;
	
	sprintf(buf,"roll:%8.3f  pitch:%8.3f  yaw:%8.3f\r\n",exroll,expitch,exyaw);//初始角度
	myPrintf(buf);
#endif
	
	lastTime = micros();
#ifdef USE_DMP	
	StopWatchInit(&td);
#endif
	for(;;)
	{
#ifndef USE_DMP
		//1RAD弧度=57.2956度 1DEG度=0.0174533弧度
		unsigned int currentTime;
		double dT;
		
		
		get_Accel_Gyro_Temp(&six_axis);//获取9轴姿态数据
		updateHMC5883L(); //获取9轴姿态数据
		
		currentTime = micros();
		dT = currentTime - lastTime;
		lastTime = currentTime;
		dT=dT/1000000.0f;
		
		calcPitchRoll();//计算俯仰角和横滚角
		
		gyroXrate = six_axis.gyro_x / 131.0; // 转换到度每秒 deg/s
    gyroYrate = six_axis.gyro_y / 131.0; // 转换到度每秒 deg/s
		
		
		//方法1和方法二的区别仅仅是俯仰角和横滚角的意义与MPU6050的芯片的物理方向有不同的对应关系，通过实验数据很容易明白
		
	#ifdef LIMIT_PITCH //方法一
		 if ((exroll < -90 && kalAngleX > 90) || (exroll > 90 && kalAngleX < -90)) {
			xKalmanSetAngle(exroll);//如果exroll在正确的范围内，将它输入卡尔曼滤波器
			compAngleX = exroll;
			kalAngleX = exroll;
			gyroXangle = exroll;
			} 
			else{ //否则使用卡尔曼滤波器融合陀螺仪数据计算角度
			kalAngleX = xgetAngle(exroll, gyroXrate, dT); // 使用kalman计算roll角度
			}
		if (_abs(kalAngleX) > 90)//如果俯仰角大于90度或者小于-90度，反转陀螺仪Y轴数据
			gyroYrate = -gyroYrate; 
		
			kalAngleY = ygetAngle(expitch, gyroYrate, dT);
	#else
		   //方法二
		
  if ((expitch < -90 && kalAngleY > 90) || (expitch > 90 && kalAngleY < -90)) {
    yKalmanSetAngle(expitch);//如果expitch在正确的范围内，将它输入卡尔曼滤波器
    compAngleY = expitch;
    kalAngleY = expitch;
    gyroYangle = expitch;
  } else  //否则使用卡尔曼滤波器融合陀螺仪数据计算角度
	{
    kalAngleY = ygetAngle(expitch, gyroYrate, dT); // 使用kalman计算pitch角度
	}
  if (_abs(kalAngleY) > 90) 
    gyroXrate = -gyroXrate; 
	
		kalAngleX = xgetAngle(exroll, gyroXrate, dT); //使用kalman计算roll角度
		
	#endif
		
		calcYaw();//计算YAW
		gyroZrate = six_axis.gyro_z / 131.0; // 转换到度每秒 deg/s
		
		if ((exyaw < -90 && kalAngleZ > 90) || (exyaw > 90 && kalAngleZ < -90)) {
    zKalmanSetAngle(exyaw); //如果exyaw在正确的范围内，将它输入卡尔曼滤波器
    compAngleZ = exyaw;
    kalAngleZ = exyaw;
    gyroZangle = exyaw;
		} else{//否则使用卡尔曼滤波器融合陀螺仪数据计算角度
    kalAngleZ = zgetAngle(exyaw, gyroZrate, dT); //使用kalman计算YAW角度
		}
#ifdef USE_GYRO
		 /* 估算角度只使用陀螺仪数据，并且陀螺仪数据没有使用滤波器滤波 */
		gyroXangle += gyroXrate * dT;  
		gyroYangle += gyroYrate * dT;
		gyroZangle += gyroZrate * dT;
#else
		/*使用无偏移卡尔曼滤波器滤波后的陀螺仪数据估算角度*/
		gyroXangle += xrate * dT; 
		gyroYangle += yrate * dT;
		gyroZangle += zrate * dT;
		
#endif	
		 /* 使用互补滤波器融合数据，计算角度 */
		compAngleX = 0.93 * (compAngleX + gyroXrate * dT) + 0.07 * exroll;
		compAngleY = 0.93 * (compAngleY + gyroYrate * dT) + 0.07 * expitch;
		compAngleZ = 0.93 * (compAngleZ + gyroZrate * dT) + 0.07 * exyaw;

		/* 当陀螺仪积分角度偏移太多时候，使用卡尔曼滤波器得到的角度重置陀螺仪积分角度 */
		if (gyroXangle < -180 || gyroXangle > 180)
			gyroXangle = kalAngleX;
		if (gyroYangle < -180 || gyroYangle > 180)
			gyroYangle = kalAngleY;
		if (gyroZangle < -180 || gyroZangle > 180)
			gyroZangle = kalAngleZ;

		#ifdef DEBUG
		eular_cnt++;
		if(eular_cnt>100)
		{
			eular_cnt=0;
			myPrintf("**************************************************************\r\n");
			sprintf(buf,"roll      :%3.3f  pitch     :%3.3f  yaw       :%3.3f\r\n",exroll,expitch,exyaw);
			myPrintf(buf);
			
			sprintf(buf,"gyroXangle:%3.3f  gyroYangle:%3.3f  gyroZangle:%3.3f\r\n",gyroXangle,gyroYangle,gyroZangle);
			myPrintf(buf);
			sprintf(buf,"compAngleX:%3.3f  compAngleY:%3.3f  compAngleZ:%3.3f\r\n",compAngleX,compAngleY,compAngleZ);
			myPrintf(buf);
			sprintf(buf,"kalAngleX :%3.3f  kalAngleY :%3.3f  kalAngleZ :%3.3f\r\n",kalAngleX,kalAngleY,kalAngleZ);
			myPrintf(buf);
			myPrintf("**************************************************************\r\n");
			
		}
		
		#endif

#else
		//如果使用MPU6050内置的DMP引擎解算姿态角
		
		unsigned int currentTime;
		double dT;
		
		idleLoops++;
		currentTime = micros();
		dT = currentTime - lastTime;
		
	  if(dT >=1000 ) //1000us执行一次
		{ 
			
//			dT: CPU经过的时间，单位是us
//			idleLoops ：空闲计数值，1ms时间的空闲计数值最大是idleMax，而dT单位是us,所以idleLoops需要乘以1000。
//			idleLoops  * 1000.0f / dT :计算每毫秒的空闲计数值
//			idleLoops  * 1000.0f / dT / (float)idleMax ：每毫秒的空闲计数值/每毫秒最大空闲计数值 ，是计算空闲百分比，最后乘以 100 ，转换成整数。
		
			idlePerf =(float)(idleLoops  * 1000.0f / dT / (float)idleMax) *100.0f; 
			idleLoops = 0;
					
			
		
			#if USE_WAY==USE_DMP_WAY //1  ，如果使用DMP引擎解算姿态角
			
			eular_cnt++;
			if(eular_cnt>100){
				eular_cnt=0;
				
				if(mpu_dmp_get_data(&inpitch,&inroll,&inyaw)==0)
				{ 
						sprintf(buf,"pitch:%8.3f  roll:%8.3f  yaw:%8.3f \r\n",inpitch,inroll,inyaw);
						myPrintf(buf);
				}
				
			}
			
			#elif USE_WAY==USE_SOFT_WAY  //2 ，如果使用其他方法解算姿态角，目前这里没有加入其他解算方法，不过可以在这里使用四元数解算姿态角
			
			soft_cnt++;
			if(soft_cnt>100){
				soft_cnt=0;
				StopWatchLap(&td);
				
				get_Accel_Gyro_Temp(&six_axis);
				get_data_time=StopWatchLap(&td);
				myPrintf("\r\n获取MPU6050六轴数据和温度用时 %d us \r\n",get_data_time);
				sprintf(buf,"accel_x:%d\r\naccel_y:%d\r\naccel_z:%d\r\ngyro_x:%d\r\ngyro_y:%d\r\ngyro_z:%d\r\nTemperature:%0.6f\r\n",
				six_axis.accel_x,six_axis.accel_y,six_axis.accel_z,six_axis.gyro_x,six_axis.gyro_y,six_axis.gyro_z,six_axis.Temperature);
				
				myPrintf("\r\n");
				myPrintf(buf);
				myPrintf("\r\n");
			
				
			}
			
			#endif
			
			++count;
			if(count>1000){//打印CPU使用率
				count=0;
				
						myPrintf("                                           CPU 空闲进程:%8.6f%% ",idlePerf);
						myPrintf("                                                          CPU 使用率 :%8.6f%% \r\n",100.0f-idlePerf);
		
			}
						
			
			lastTime = currentTime;//保存旧的时间
	 }
	 
	 
	 
#endif
	}
}

void calcPitchRoll(void)
{
	//方法1和方法2的区别仅仅是俯仰角和横滚角的意义与MPU6050的芯片的物理方向有不同的对应关系，通过实验数据很容易明白
		
	#ifdef LIMIT_PITCH //方法1
	
	exroll = atan2(six_axis.accel_y, six_axis.accel_z) * RAD_TO_DEG;
	expitch = atan(-six_axis.accel_x / sqrt(six_axis.accel_y * six_axis.accel_y + six_axis.accel_z * six_axis.accel_z)) * RAD_TO_DEG;
	#else
	//方法2
	exroll = atan(six_axis.accel_y / sqrt(six_axis.accel_x * six_axis.accel_x + six_axis.accel_z * six_axis.accel_z)) * RAD_TO_DEG;
  expitch = atan2(-six_axis.accel_x , six_axis.accel_z) * RAD_TO_DEG;
	
	#endif
}

void calcYaw(void)//使用三轴磁强计数据和卡尔曼滤波器计算得到的俯仰角和横滚角估算偏航角Yaw
{
	double rollAngle ,pitchAngle,Bfy,Bfx;
	
	magX *= -1; 
  magZ *= -1;

  magX *= magGain[0];
  magY *= magGain[1];
  magZ *= magGain[2];

  magX -= offsetX;
  magY -= offsetY;
  magZ -= offsetZ;
	
	rollAngle = kalAngleX * DEG_TO_RAD;
	pitchAngle = kalAngleY * DEG_TO_RAD;

  Bfy = magZ * sin(rollAngle) - magY * cos(rollAngle);
  Bfx = magX * cos(pitchAngle) + magY * sin(pitchAngle) * sin(rollAngle) + magZ * sin(pitchAngle) * cos(rollAngle);
  exyaw = atan2(-Bfy, Bfx) * RAD_TO_DEG;

  exyaw *= -1;
}



