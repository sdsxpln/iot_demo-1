
 //	2017-02-06			

#include "reg52.h"
#include  <INTRINS.H> //Keil library  
#include "Delay_12M.h"
#include "stc12_adc.h"


/*Declare SFR associated with the ADC */
sfr ADC_CONTR   =   0xBC;      	//ADC control register 
sfr ADC_RES     =   0xBD;       //ADC high 8-bit result register 
sfr ADC_LOW2    =   0xBE;        //ADC low 2-bit result register 
sfr P1ASF       =   0x9D;     	//P1 secondary function control register

/*Define ADC operation const for ADC_CONTR*/	
#define ADC_POWER	0x80	//ADC power control bit
#define ADC_FLAG	0x10	//ADC complete flag
#define ADC_START	0x08	//ADC start control bit
#define ADC_SPEEDLL 0x00	//540 clocks
#define ADC_SPEEDL	0x20	//360 clocks
#define ADC_SPEEDH	0x40	//180 clocks
#define ADC_SPEEDHH 0x60	//90 clocks

#define ADC_MY_SPEED	ADC_SPEEDLL





/*----------------------------Initial ADC sfr----------------------------*/ 
void InitADC(unsigned char ch_map) 
{    
	P1ASF = ch_map;             
	ADC_RES = 0;
	ADC_LOW2= 0;
	ADC_CONTR = ADC_POWER | ADC_MY_SPEED;  
	DelayMs(2);                //ADC power-on and delay 
}





/*----------------------------Get ADC result----------------------------*/ 
unsigned int GetADCResult(unsigned char ch)
{
	unsigned int j;

	ADC_CONTR = ADC_POWER | ADC_MY_SPEED | ch | ADC_START;   
	
	//Must wait before inquiry   
	_nop_();   	_nop_();  
	_nop_();  	_nop_(); 

	while (!(ADC_CONTR & ADC_FLAG));	//Wait complete flag  

	ADC_CONTR &= ~ADC_FLAG;  //Close ADC

	j = ADC_RES;
	j <<= 2;
	j |= ADC_LOW2;

	return j;        //Return ADC result    
}




#if 0
/*----------------------------Get ADC result   1×Ö½Ú½á¹û----------------------------*/ 
unsigned char GetADCResultU8(unsigned char ch)
{
	ADC_CONTR = ADC_POWER | ADC_MY_SPEED | ch | ADC_START;   
	
	//Must wait before inquiry   
	_nop_();   	_nop_();  
	_nop_();  	_nop_(); 

	while (!(ADC_CONTR & ADC_FLAG));	//Wait complete flag  

	ADC_CONTR &= ~ADC_FLAG;  //Close ADC

	return ADC_RES;
}
#endif


