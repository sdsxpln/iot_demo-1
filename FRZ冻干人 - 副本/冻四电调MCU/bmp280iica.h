
#ifndef __BMP280IICA_H
#define __BMP280IICA_H

//2017-06-06


extern char BMP280_readRC; //¶ÁÖ´ÐÐÕýÈ·´íÎó
extern char   *BMP280RES_C; 
extern float BMP280_Temperature; 
extern float BMP280_Pressure; 


extern void Reset_BMP280( void );
extern void Get_BMP280( void );






#endif


