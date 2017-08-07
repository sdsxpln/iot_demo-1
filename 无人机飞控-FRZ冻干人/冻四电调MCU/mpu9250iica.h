
#ifndef __MPU9250IICA_H
#define __MPU9250IICA_H

//2017-06-06


extern char MPU9250_readRC; //��ִ����ȷ����
extern float *MPU9250RES_F; 
extern int   *MPU9250RES_I; 
extern char  MPU9250RES_TYPE; //0=Ĭ�ϣ������͡� 1=�����͡�		



extern void Init_MPU9250( void );
extern void READ_MPU9250_ACCEL(void);
extern void READ_MPU9250_GYRO(void);
extern void READ_MPU9250_MAG(void);






#endif


