#ifndef _HMC5883L_H
#define _HMC5883L_H

#include "i2c.h"

#define HMC5883L_ADR 0x3c

//#define DUBUG_MAG

#define CalThreshold 0
#define MagnetcDeclination 4.43 //笔者所在地磁偏角，请根据情况自行百度
#define PI 3.141592653f

void updateHMC5883L(void);

void Init_Hmc5883(void);
void calibrateMag(void) ;
void get_offset(void);
int calculateHeading(int* x ,int* y,int* z)  ;
void printf_Heading_angle(void);
int _abs( int p);

extern int16_t magX,magY,magZ;
extern float magGain[3];
extern int16_t offsetX , offsetY , offsetZ ;


#endif
