/******************************************
 * �ļ���  ��main.c
 * ����    : DMP����Ϳ������˲��㷨���ַ���������̬��    
 * ��汾  ��ST3.5.0
 * Author  �� ����
 * QQ      ��547336083
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

//#define LIMIT_PITCH  //ʹ�����ַ������㸩���Ǻͺ����ѡ��
#define USE_GYRO   //ʹ��ԭʼ���������ݻ�����̬�ǻ���ʹ����ƫ�������˲����˲�֮������������ݽ�����̬��
//#define USE_DMP  //�Ƿ�ʹ��MPU6050���õ�DMP���������̬��

#define DEBUG  //DEBUG ģʽ�»�ͨ������1��ӡ���������

double exroll,expitch,exyaw;//���Ǻ�����ȡ��ŷ����
double gyroXangle, gyroYangle, gyroZangle; // ֻʹ�������Ǽ���õ��ĽǶ�
double compAngleX, compAngleY, compAngleZ; // ʹ����ƫ�ƿ������˲�������������ǽǶ�
double gyroXrate,gyroYrate,gyroZrate; //ԭʼ���������� ��/��

double kalAngleX, kalAngleY, kalAngleZ; //�������˲�����ȡ��ŷ����
void calcPitchRoll(void);//���ַ������㸩���Ǻͺ���ǣ�����1�ͷ���2����������Ǹ����Ǻͺ���ǵ�������MPU6050��оƬ���������в�ͬ�Ķ�Ӧ��ϵ��ͨ��ʵ�����ݺ���������
		
void calcYaw(void);//ʹ�������ǿ�����ݺͿ������˲�������õ��ĸ����Ǻͺ���ǹ���ƫ����Yaw

int main(void)
{	
	float inpitch,inroll,inyaw; 		//ŷ����
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
	/* I2C �����ʼ�� for (EEPROM) */
	I2c_EEPROM_Init();
	
	Init_MPU6050();
	idleMax=GetIdleMax();//��ȡCPU����״̬�µ�1ms������ֵ,������������CPUʹ����
	myPrintf("��ȡCPU����״̬�µ�1ms������ֵ,������������CPUʹ����\r\n");
#ifdef USE_DMP //���ʹ��DMP���������̬��
	{
		uint8_t init_Try=10;//��ʼ�����Դ���
		while(mpu_dmp_init()&&init_Try!=0)
		{
			myPrintf("mpu_dmp_init Exeing\r\n");
			init_Try--;
		}
		if(0!=init_Try)
		myPrintf("mpu_dmp_init Exeing ok\r\n");
		else myPrintf("mpu_dmp_init Exeing Fail\r\n");
	}
#else //����ʹ�ÿ������˲���+�����˲���+���Ǻ���������̬��

	Init_Hmc5883();//��ʼ��HMC5883
	
	xInit_Kalman();//��ʼ���������˲���
	yInit_Kalman();
	zInit_Kalman();
	
	get_Accel_Gyro_Temp(&six_axis);//��ȡ9����̬����
	updateHMC5883L(); //��ȡ9����̬����
	
	calcPitchRoll();
	calcYaw();//��һ�μ���
	
	xKalmanSetAngle(exroll);//�����������ʼ�Ƕ� Roll
	gyroXangle = exroll;
  compAngleX = exroll;
	
	
	yKalmanSetAngle(expitch); //�����������ʼ�Ƕ�Pitch
  gyroYangle = expitch;
  compAngleY = expitch;
	
	zKalmanSetAngle(exyaw); //�����������ʼ�Ƕ� yaw
  gyroZangle = exyaw;
  compAngleZ = exyaw;
	
	sprintf(buf,"roll:%8.3f  pitch:%8.3f  yaw:%8.3f\r\n",exroll,expitch,exyaw);//��ʼ�Ƕ�
	myPrintf(buf);
#endif
	
	lastTime = micros();
#ifdef USE_DMP	
	StopWatchInit(&td);
#endif
	for(;;)
	{
#ifndef USE_DMP
		//1RAD����=57.2956�� 1DEG��=0.0174533����
		unsigned int currentTime;
		double dT;
		
		
		get_Accel_Gyro_Temp(&six_axis);//��ȡ9����̬����
		updateHMC5883L(); //��ȡ9����̬����
		
		currentTime = micros();
		dT = currentTime - lastTime;
		lastTime = currentTime;
		dT=dT/1000000.0f;
		
		calcPitchRoll();//���㸩���Ǻͺ����
		
		gyroXrate = six_axis.gyro_x / 131.0; // ת������ÿ�� deg/s
    gyroYrate = six_axis.gyro_y / 131.0; // ת������ÿ�� deg/s
		
		
		//����1�ͷ���������������Ǹ����Ǻͺ���ǵ�������MPU6050��оƬ���������в�ͬ�Ķ�Ӧ��ϵ��ͨ��ʵ�����ݺ���������
		
	#ifdef LIMIT_PITCH //����һ
		 if ((exroll < -90 && kalAngleX > 90) || (exroll > 90 && kalAngleX < -90)) {
			xKalmanSetAngle(exroll);//���exroll����ȷ�ķ�Χ�ڣ��������뿨�����˲���
			compAngleX = exroll;
			kalAngleX = exroll;
			gyroXangle = exroll;
			} 
			else{ //����ʹ�ÿ������˲����ں����������ݼ���Ƕ�
			kalAngleX = xgetAngle(exroll, gyroXrate, dT); // ʹ��kalman����roll�Ƕ�
			}
		if (_abs(kalAngleX) > 90)//��������Ǵ���90�Ȼ���С��-90�ȣ���ת������Y������
			gyroYrate = -gyroYrate; 
		
			kalAngleY = ygetAngle(expitch, gyroYrate, dT);
	#else
		   //������
		
  if ((expitch < -90 && kalAngleY > 90) || (expitch > 90 && kalAngleY < -90)) {
    yKalmanSetAngle(expitch);//���expitch����ȷ�ķ�Χ�ڣ��������뿨�����˲���
    compAngleY = expitch;
    kalAngleY = expitch;
    gyroYangle = expitch;
  } else  //����ʹ�ÿ������˲����ں����������ݼ���Ƕ�
	{
    kalAngleY = ygetAngle(expitch, gyroYrate, dT); // ʹ��kalman����pitch�Ƕ�
	}
  if (_abs(kalAngleY) > 90) 
    gyroXrate = -gyroXrate; 
	
		kalAngleX = xgetAngle(exroll, gyroXrate, dT); //ʹ��kalman����roll�Ƕ�
		
	#endif
		
		calcYaw();//����YAW
		gyroZrate = six_axis.gyro_z / 131.0; // ת������ÿ�� deg/s
		
		if ((exyaw < -90 && kalAngleZ > 90) || (exyaw > 90 && kalAngleZ < -90)) {
    zKalmanSetAngle(exyaw); //���exyaw����ȷ�ķ�Χ�ڣ��������뿨�����˲���
    compAngleZ = exyaw;
    kalAngleZ = exyaw;
    gyroZangle = exyaw;
		} else{//����ʹ�ÿ������˲����ں����������ݼ���Ƕ�
    kalAngleZ = zgetAngle(exyaw, gyroZrate, dT); //ʹ��kalman����YAW�Ƕ�
		}
#ifdef USE_GYRO
		 /* ����Ƕ�ֻʹ�����������ݣ���������������û��ʹ���˲����˲� */
		gyroXangle += gyroXrate * dT;  
		gyroYangle += gyroYrate * dT;
		gyroZangle += gyroZrate * dT;
#else
		/*ʹ����ƫ�ƿ������˲����˲�������������ݹ���Ƕ�*/
		gyroXangle += xrate * dT; 
		gyroYangle += yrate * dT;
		gyroZangle += zrate * dT;
		
#endif	
		 /* ʹ�û����˲����ں����ݣ�����Ƕ� */
		compAngleX = 0.93 * (compAngleX + gyroXrate * dT) + 0.07 * exroll;
		compAngleY = 0.93 * (compAngleY + gyroYrate * dT) + 0.07 * expitch;
		compAngleZ = 0.93 * (compAngleZ + gyroZrate * dT) + 0.07 * exyaw;

		/* �������ǻ��ֽǶ�ƫ��̫��ʱ��ʹ�ÿ������˲����õ��ĽǶ����������ǻ��ֽǶ� */
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
		//���ʹ��MPU6050���õ�DMP���������̬��
		
		unsigned int currentTime;
		double dT;
		
		idleLoops++;
		currentTime = micros();
		dT = currentTime - lastTime;
		
	  if(dT >=1000 ) //1000usִ��һ��
		{ 
			
//			dT: CPU������ʱ�䣬��λ��us
//			idleLoops �����м���ֵ��1msʱ��Ŀ��м���ֵ�����idleMax����dT��λ��us,����idleLoops��Ҫ����1000��
//			idleLoops  * 1000.0f / dT :����ÿ����Ŀ��м���ֵ
//			idleLoops  * 1000.0f / dT / (float)idleMax ��ÿ����Ŀ��м���ֵ/ÿ���������м���ֵ ���Ǽ�����аٷֱȣ������� 100 ��ת����������
		
			idlePerf =(float)(idleLoops  * 1000.0f / dT / (float)idleMax) *100.0f; 
			idleLoops = 0;
					
			
		
			#if USE_WAY==USE_DMP_WAY //1  �����ʹ��DMP���������̬��
			
			eular_cnt++;
			if(eular_cnt>100){
				eular_cnt=0;
				
				if(mpu_dmp_get_data(&inpitch,&inroll,&inyaw)==0)
				{ 
						sprintf(buf,"pitch:%8.3f  roll:%8.3f  yaw:%8.3f \r\n",inpitch,inroll,inyaw);
						myPrintf(buf);
				}
				
			}
			
			#elif USE_WAY==USE_SOFT_WAY  //2 �����ʹ����������������̬�ǣ�Ŀǰ����û�м����������㷽������������������ʹ����Ԫ��������̬��
			
			soft_cnt++;
			if(soft_cnt>100){
				soft_cnt=0;
				StopWatchLap(&td);
				
				get_Accel_Gyro_Temp(&six_axis);
				get_data_time=StopWatchLap(&td);
				myPrintf("\r\n��ȡMPU6050�������ݺ��¶���ʱ %d us \r\n",get_data_time);
				sprintf(buf,"accel_x:%d\r\naccel_y:%d\r\naccel_z:%d\r\ngyro_x:%d\r\ngyro_y:%d\r\ngyro_z:%d\r\nTemperature:%0.6f\r\n",
				six_axis.accel_x,six_axis.accel_y,six_axis.accel_z,six_axis.gyro_x,six_axis.gyro_y,six_axis.gyro_z,six_axis.Temperature);
				
				myPrintf("\r\n");
				myPrintf(buf);
				myPrintf("\r\n");
			
				
			}
			
			#endif
			
			++count;
			if(count>1000){//��ӡCPUʹ����
				count=0;
				
						myPrintf("                                           CPU ���н���:%8.6f%% ",idlePerf);
						myPrintf("                                                          CPU ʹ���� :%8.6f%% \r\n",100.0f-idlePerf);
		
			}
						
			
			lastTime = currentTime;//����ɵ�ʱ��
	 }
	 
	 
	 
#endif
	}
}

void calcPitchRoll(void)
{
	//����1�ͷ���2����������Ǹ����Ǻͺ���ǵ�������MPU6050��оƬ���������в�ͬ�Ķ�Ӧ��ϵ��ͨ��ʵ�����ݺ���������
		
	#ifdef LIMIT_PITCH //����1
	
	exroll = atan2(six_axis.accel_y, six_axis.accel_z) * RAD_TO_DEG;
	expitch = atan(-six_axis.accel_x / sqrt(six_axis.accel_y * six_axis.accel_y + six_axis.accel_z * six_axis.accel_z)) * RAD_TO_DEG;
	#else
	//����2
	exroll = atan(six_axis.accel_y / sqrt(six_axis.accel_x * six_axis.accel_x + six_axis.accel_z * six_axis.accel_z)) * RAD_TO_DEG;
  expitch = atan2(-six_axis.accel_x , six_axis.accel_z) * RAD_TO_DEG;
	
	#endif
}

void calcYaw(void)//ʹ�������ǿ�����ݺͿ������˲�������õ��ĸ����Ǻͺ���ǹ���ƫ����Yaw
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



