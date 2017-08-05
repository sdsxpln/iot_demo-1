
 //20161126.201824	

#include "reg52.h"
#include "Delay_12M.h"
#include  <INTRINS.H> //Keil library  


/*------------------------------------------------
 晶振24M，1T单片机
------------------------------------------------*/
#if 1
void DelayUs2x(unsigned char t)
{   
	unsigned int i;
	i =t * 1;
	do{
		for( t = 0; t < 5; t++ );
		i--;
	}while(i);
}
#endif


/*------------------------------------------------
 晶振12M，1T单片机
------------------------------------------------*/
#if 0
void DelayUs2x(unsigned char t)
{   
	unsigned int i;
	i =t * 2;
	do{
		//_nop_();	 
		//t++;		t--;
		i--;
	}while(i);
}
#endif


/*------------------------------------------------
 晶振12M，12T单片机   大致延时长度如下 T=tx2+5 uS 
------------------------------------------------*/
#if 0
void DelayUs2x(unsigned char t)
{   
	 while(--t);
}
#endif


/*------------------------------------------------
 晶振33M，1T单片机
------------------------------------------------*/
#if 0
void DelayUs2x(unsigned char t)
{
	unsigned int i = 5 * t;

	while(--i);
}
#endif




//==========================================================



/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs_small(unsigned char t)
{
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}


void DelayMs(unsigned int t)
{
	char i,j;

	i = t / 251;
	j = t % 251;

	while(i--)
	{
		DelayMs_small(251);
	}

	DelayMs_small(j);
}



//作用：秒延时函数 
#if 0
void DelayS(unsigned char t)
{
 while(t--)
 {
	DelayMs(250);
	DelayMs(250);
	DelayMs(250);
	DelayMs(250);
 }
}
#endif


