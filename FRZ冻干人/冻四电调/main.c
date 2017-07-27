/*******************/
//#include <reg52.h>
#include "STDIO.H"
#include "STDLIB.H"
#include "INTRINS.H"
#include "STRING.H"
#include "Delay_12M.h"
#include "UNIQ_ID.h"
#include "a_strfunc.h"
#include "a_comfunc.h"
#include "a_timerfunc.h"
//#include "lcd_12864.h"
#include "mainioport.h"
#include "EEPROM.h"
#include "stc12_adc.h"
#include "a_ll1func.h"
//#include "ds1302.h"
#include "mpu9250iica.h"
#include "bmp180.h"
#include "bmp280iica.h"


unsigned char idata g_ctrl_timer[2];
unsigned int idata * idata g_p_ctrl_timer;


#define    FIRMWAREVER   "V1.00"


#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

#define S2_S0 0x01              //P_SW2.0


#include "main1.xpp"
#include "main2.xpp"




void Timer0Init(void)		//5����@24.000MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xF0;		//���ö�ʱ��ֵ
	TH0 = 0xD8;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer1Init(void)		//5����@24.000MHz
{
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xF0;		//���ö�ʱ��ֵ
	TH1 = 0xD8;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}

void Timer3Init(void)		//5����@24.000MHz
{
	T4T3M &= 0xFD;		//��ʱ��ʱ��12Tģʽ
	T3L = 0xF0;		//���ö�ʱ��ֵ
	T3H = 0xD8;		//���ö�ʱ��ֵ
	T4T3M |= 0x08;		//��ʱ��3��ʼ��ʱ
}

void Timer4Init(void)		//5����@24.000MHz
{
	T4T3M &= 0xDF;		//��ʱ��ʱ��12Tģʽ
	T4L = 0xF0;		//���ö�ʱ��ֵ
	T4H = 0xD8;		//���ö�ʱ��ֵ
	T4T3M |= 0x80;		//��ʱ��4��ʼ��ʱ
}



// ʹ�ö�ʱ��2
void Uart1Init(void)		//9600bps@24.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR &= 0xFB;		//��ʱ��2ʱ��ΪFosc/12,��12T
	T2L = 0xCC;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
}

void Uart2Init(void)		//9600bps@24.000MHz
{
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xFB;		//��ʱ��2ʱ��ΪFosc/12,��12T
	T2L = 0xCC;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
}


char flag2;


//
//������ ��ں���:
void main()
{
	g_p_ctrl_timer = (unsigned int*)g_ctrl_timer;
	*g_p_ctrl_timer = 65535L - 59999;
	
	//��ʼ��
	EA=0;		// ���ж�
 
	Timer0Init();
	Timer1Init();
	Timer3Init();
	Timer4Init();
	ET0=1;		//������ʱ��0�ж�
	ET1 = 1;                        //ʹ�ܶ�ʱ��
	//IE2 |= 0x04;                    //����ʱ��2�ж�
	IE2 |= 0x20;                    //����ʱ��3�ж�
	IE2 |= 0x40;                    //����ʱ��4�ж�


	Uart1Init();
  //ACC = P_SW1;
  //ACC &= ~(S1_S0 | S1_S1);    //S1_S0=1 S1_S1=0
  //ACC |= S1_S0;               //(P3.6/RxD_2, P3.7/TxD_2)
  //P_SW1 = ACC;  
	ES = 1;                     //ʹ�ܴ����ж�

	Uart2Init();
  P_SW2 |= S2_S0;             //S2_S0=1 (P4.6/RxD2_2, P4.7/TxD2_2)
	IE2 = 0x01;                 //ʹ�ܴ���2�ж�
	
	//�л����ȼ�
	//PT0 = 0;
	//PS = 1;
	//IP2 |= 1;


	//Com2SendU8ss( "AT+BOUD3" );Ӧ����ʹ��֮���ٷ�����
	//DelayMs(300);


	//�û���ʼ�� 
	mainioport_init();

	M1Conf_t_default( &M1 );
	M5Runtime_t_default( &M5 );
	M12Pwm_t_default( M12 + 0 );
	M12Pwm_t_default( M12 + 1 );
	M12Pwm_t_default( M12 + 2 );
	M12Pwm_t_default( M12 + 3 );
	M22ATbuf_t_default( M22 + 0 );
	M22ATbuf_t_default( M22 + 1 );
	
	Init_MPU9250();
	Init_BMP085();
	//Reset_BMP280();

	tm_init( &ta1comrecv_tm );
	tm_init( &ta71beeplong_tm );
	tm_init( &ta72beepshort_tm );

	LET_BEEP1_OFF;
	LET_LED1_OFF;
	LET_LED2_OFF;

	DelayMs(300);
	EA  = 1;          //�����ж� 

	  

	while(EA)
	{
		 
		DelayMs(333);
	
		//M2Work.m_hi_tta = 900;
		//M2Work.m_hi_ttb = 900;
		//M2Work.m_hi_ttc = 900;
		//M2Work.m_hi_ttd = 900;

		//sharedata_main_ready( &M2[0] , &M2[1] , &M2[2] , sizeof( struct M12Pwm_t ) );
		
		Get_BMP280();

		sprintf( printbuf, "%f, %f\r\n", BMP280_Pressure, BMP280_Temperature );
		//		sprintf( printbuf, "OK. %ld,%ld\r\n",   g_bmp085_pressure, g_bmp085_temperature	);
		Com1SendU8ss( printbuf );

		READ_MPU9250_ACCEL();
		sprintf( printbuf, "%f, %f,%f\r\n", MPU9250RES_F[0], MPU9250RES_F[1], MPU9250RES_F[2] );
		Com1SendU8ss( printbuf );

		//READ_MPU9250_GYRO();
		//READ_MPU9250_MAG();

		//if( flag2 )
		//{
		//	flag2 = 0;

		//	for( M2Work.m_hi_tta = 0; M2Work.m_hi_tta < 24; M2Work.m_hi_tta++ )
		//	{
		//		Com2SendU8( BMP280RES_C[M2Work.m_hi_tta] );
		//	}
		//	
		//	//Com1SendU8( 0xFe );
		//	//Com1SendU8( 0xFe );
		//	Com2SendU8( 0xAe );
		//}

		//M3.m_lightadc = GetADCResult( 0 );

		//Com1SendU8is( GET_KEY1, ds1302_table );
		//Com1SendU8ss( "," );
		//Com1SendU8is( GET_KEYMODE, ds1302_table );
		//Com1SendU8ss( "," );
		//Com1SendU8is( GET_KEYSWT, ds1302_table );
		//Com1SendU8ss( "\n" );
	}


	M5.m_beepshort = 1;

	while(1)
	{
		ta3postcmd( &ta3postcmd_state );

		ta62readdata( &ta62readdata_state );

		tm_tk_n( &ta1comrecv_tm, M5.m_tk_old, M5.m_tk );
		tm_tk_n( &ta71beeplong_tm, M5.m_tk_old, M5.m_tk );
		tm_tk_n( &ta72beepshort_tm, M5.m_tk_old, M5.m_tk );
		M5.m_tk_old = M5.m_tk;

		ta71beeplong( &ta71beeplong_state );
		ta72beepshort( &ta72beepshort_state );

	}
		 
}	


	
//
void timer0_routine() interrupt 1  
{
	//TH0 = ctrl_timer[0];
	//TL0 = ctrl_timer[1];

	tta( &tta_state );
}

	
//
void timer1_routine() interrupt 3  
{
	ttb( &ttb_state );
}

//
void timer3_routine() interrupt 19  
{
	ttc( &ttc_state );
}

//
void timer4_routine() interrupt 20  
{
	//TH0 = g_ctrl_timer[0];
	//TL0 = g_ctrl_timer[1];

	ttd( &ttd_state );
}



		 
		  

/*------------------------------------------------
�����жϳ���
------------------------------------------------*/
void UART_SER() interrupt 4 //�����жϷ������
{
	if(RI)      //�ж��ǽ����жϲ���
	{
		RI=0;     //��־λ����

		ta1comrecv( &ta1comrecv_state );
	}

	if(TI)    //����Ƿ��ͱ�־λ������
	{
		TI=0;
		Com1_TI_flag = 1; //�������ڷ���û��������һ��flag
	}
}
		

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1

/*----------------------------
UART2 �жϷ������
-----------------------------*/
void UART2_SER() interrupt 8  
{
    if (S2CON & S2RI)      //�ж��ǽ����жϲ���
    {
        S2CON &= ~S2RI;         //���S2RIλ

		//ta1comrecv( &ta1comrecv_state );
		flag2 = 1;
    }

    if (S2CON & S2TI)    //����Ƿ��ͱ�־λ������
    {
        S2CON &= ~S2TI;         //���S2TIλ 
		Com2_TI_flag = 1; //�������ڷ���û��������һ��flag
    }
		
}

