
// 2016-10-02	

#include "a_strfunc.h"
#include "UNIQ_ID.h"

#include "a_comfunc.h"

 

//=====================================COM1	

#if 1
unsigned char Com1_TI_flag = 1;
#endif



#if 1
void Com1SendU8( unsigned char c )
{
	while(!Com1_TI_flag); Com1_TI_flag = 0; 
	SBUF = c;
}
#endif



#if 1
void Com1SendU8ss( unsigned char * s )
{
	for(;;)
	{
		if( *s == 0 ) break;
		Com1SendU8( *s ); 
		s++;
	}
}
#endif



#if 0
void Com1SendU8is( unsigned long i, unsigned char * buf )
{
	myltoa( buf, i, 0x00 );
	Com1SendU8ss( buf );
}
#endif

//
//void send_struct( unsigned char * buf, unsigned char iBufLen )
//{
//	U8 i; 
//	
//	for( i = 0; i < iBufLen; i++ )
//	{
//		Com1SendU8( buf[i] );
//	}
//}
		//	//send_struct( M2do.m_buf[0], 18 );
		//	//send_struct( M2do.m_buf[1], 18 );





// Com1 接收 
#if 0

U8  Com1Recv_rc;
U8  Com1Recv_c;

U16	Com1Recv_TimeOutLmt = 2345;
static U16 Com1Recv_TimeOutCounter;

void Com1Recv()
{
	Com1Recv_TimeOutCounter = 0;
	while(1)
	{
		if(RI) 
		{ 
			RI=0; 
			Com1Recv_c = SBUF;
			Com1Recv_rc = 1;
			return;
		} 
		else 
		{ 
			Com1Recv_TimeOutCounter++; 
			if( Com1Recv_TimeOutCounter > Com1Recv_TimeOutLmt ) 
			{ 
				Com1Recv_rc = 0;
				return;
			} 
		} 
	}
}
#endif







//=====================================COM2	


#if 1
unsigned char Com2_TI_flag = 1;
#endif



#if 1
void Com2SendU8( unsigned char c )
{
	while(!Com2_TI_flag); Com2_TI_flag = 0; 
	S2BUF = c;
}
#endif



#if 1
void Com2SendU8ss( unsigned char * s )
{
	for(;;)
	{
		if( *s == 0 ) break;
		Com2SendU8( *s ); 
		s++;
	}
}
#endif



#if 0
void Com2SendU8is( unsigned long i, unsigned char * buf )
{
	myltoa( buf, i, 0x00 );
	Com2SendU8ss( buf );
}
#endif








//===============================程序例子：
#if 0 

/*------------------------------------------------
串口中断程序
------------------------------------------------*/
void UART_SER() interrupt 4 //串行中断服务程序
{
	if(RI)      //判断是接收中断产生
	{
		RI=0;     //标志位清零

		ta63com1( &ta63com1_state );
	}

	if(TI)    //如果是发送标志位，清零
	{
		TI=0;
		Com1_TI_flag = 1; //这样等于发送没做，另找一个flag
	}
}
		

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1

/*----------------------------
UART2 中断服务程序
-----------------------------*/
void Uart2() interrupt 8  
{
    if (S2CON & S2RI)      //判断是接收中断产生
    {
        S2CON &= ~S2RI;         //清除S2RI位
        //P0 = S2BUF;             //P0显示串口数据
        //P2 = (S2CON & S2RB8);   //P2.2显示校验位

    }

    if (S2CON & S2TI)    //如果是发送标志位，清零
    {
        S2CON &= ~S2TI;         //清除S2TI位 
		Com2_TI_flag = 1; //这样等于发送没做，另找一个flag
    }
		
}






/*------------------------------------------------
串口中断程序
------------------------------------------------*/
void UART_SER() interrupt 4 //串行中断服务程序
{
	if(RI)      //判断是接收中断产生
	{
		RI=0;     //标志位清零
		
		ta33com1( &ta33com1_state );
	}

	if(TI)    //如果是发送标志位，清零
	{
		TI=0;
		Com1_TI_flag = 1; //这样等于发送没做，另找一个flag
	}
}
		

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1

/*----------------------------
UART2 中断服务程序
-----------------------------*/
void Uart2() interrupt 8  
{
    if (S2CON & S2RI)      //判断是接收中断产生
    {
        S2CON &= ~S2RI;         //清除S2RI位
	
		ta32com2( &ta32com2_state );
    }

    if (S2CON & S2TI)    //如果是发送标志位，清零
    {
        S2CON &= ~S2TI;         //清除S2TI位 
		Com2_TI_flag = 1; //这样等于发送没做，另找一个flag
    }
		
}



#endif






