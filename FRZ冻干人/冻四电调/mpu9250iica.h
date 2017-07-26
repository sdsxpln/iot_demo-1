
#ifndef __MPU9250IICA_H
#define __MPU9250IICA_H

//2017-06-06


extern char MPU9250_readRC; //读执行正确错误
extern float *MPU9250RES_F; 
extern int   *MPU9250RES_I; 
extern char  MPU9250RES_TYPE; //0=默认，浮点型。 1=整数型。		



extern void Init_MPU9250( void );
extern void READ_MPU9250_ACCEL(void);
extern void READ_MPU9250_GYRO(void);
extern void READ_MPU9250_MAG(void);






#endif


