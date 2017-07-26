
static void a_start(void)
{
//ʱ��:ʱ����Ϊ�ߵ�ƽ�������ߴӸߵ�ƽ�����
//�͵�ƽ,Ȼ��ʱ��������ɵ͵�ƽ
	SDA = 1;			// ����I2C����
	SCL = 1;
	delay5us();
	SDA = 0;
	delay5us();
	SCL = 0;
	delay5us();
}

static void a_stop(void)
{
//ʱ��:������Ϊ�͵�ƽ,ʱ��������ɸߵ�ƽ�Ժ������ߴӵ͵�ƽ�����
//�ߵ�ƽ.
	SDA = 0;			// ֹͣI2C�������ݴ���
	SCL = 1;
	delay5us();
	SDA = 1;
	delay5us();
    SCL = 1;

}

static void a_ack(void)
{
//ʱ��:��Ӧ��ʱ��λ���潫���������͡�
	SDA = 0;			// ����Ӧ��λ	
	_nop_();
	_nop_();
	_nop_();
	SCL = 1;
	delay5us();
	SCL = 0;
    SDA = 0;
}

static void a_n_ack(void)
{
//ʱ��:��Ӧ��ʱ��λ���潫��������Ϊ�ߵ�ƽ��
	SDA = 1;			// ���ͷ�Ӧ��λ
	_nop_();
	_nop_();
	_nop_();
	SCL = 1;
	delay5us();
	SCL = 0;
	SDA = 0;
}

static char a_checkack(void)
{ 
//ʱ��:��Ӧ��ʱ��λ���潫��������Ϊ���벢���
//�������Ƿ����������͡�
unsigned short t;
t=2000;             //��ʱ����
SDA = 1;    		// Ӧ��λ��飨��p1.0���ó����룬��������˿�д1��
//delay5us();
SCL = 1;
delay5us();  //��Ҫ
while(SDA&&t)
  {
   delay5us();
   t--;
  }
SCL = 0;
SDA = 0;
//delay5us();
if(t==0)
 {
  return  0;
  }
else
 {
  return  1;
 }
}

static void a_sendbyte(uchar send_data)
{ 
uchar  n = 8;  
while(n--)
{ 
	if(send_data&0x80)    // ��Ҫ���͵��������λΪ1����λ1
		SDA = 1;             // ����λ1
    else
 		SDA = 0;             // ������λ0
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCL = 1;
    _nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	send_data = send_data<<1;    // ��������һλ
	SCL = 0;
 	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
    //SDA = 0;	
	}
}


static unsigned char a_recbyte(void)
{
	uchar  n=8;    // ��SDA���϶�ȡһλ�����ֽڣ���8λ
	uchar  temp = 0;
	while(n--)
	{
	SDA = 1;
	SCL = 1;
	temp = temp<<1;    // ����һλ
    _nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	if(SDA == 1)
		temp = temp|0x01;    // �����յ���λΪ1�������ݵ����һλ��1
	else 
		temp = temp&0xfe;    // �������ݵ����һλ��0
	SCL=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	}
	return temp;
}


void Read_BMP280a()
{
	unsigned char i;

	a_start();
	a_sendbyte(BMP280_I2C_ADDRESS);
	a_checkack();
	a_sendbyte(0x88);
	a_checkack();
	for(i=0;i<1;i++)
	{
		data[0] = a_recbyte();
		//if(i!=3)
		//	a_ack();
		//else
		//	a_n_ack();
	}
			a_n_ack();
	a_stop();
}


// *******************
void Init_BMP280a(void)
{
	//unsigned char i;

	BMP280RES_C = BUF;

	// Read 24 bytes of data from address(0x88)
	Read_BMP280a();
	if( BMP280_readRC == FALSE ) return;
 

	dig_T1 = data[1] * 256 + data[0];
	dig_T2 = data[3] * 256 + data[2];
	dig_T3 = data[5] * 256 + data[4];
	dig_P1 = data[7] * 256 + data[6];
	dig_P2 = data[9] * 256 + data[8];
	dig_P3 = data[11]* 256 + data[10];
	dig_P4 = data[13]* 256 + data[12];
	dig_P5 = data[15]* 256 + data[14];
	dig_P6 = data[17]* 256 + data[16];
	dig_P7 = data[19]* 256 + data[18];
	dig_P8 = data[21]* 256 + data[20];
	dig_P9 = data[23]* 256 + data[22];

	// Select control measurement register(0xF4)
	// Normal mode, temp and pressure over sampling rate = 1(0x27)
	//Single_Write( BMP280_I2C_ADDRESS, 0xF4, 0x27 );

	// Select config register(0xF5)
	// Stand_by time = 1000 ms(0xA0)
	//Single_Write( BMP280_I2C_ADDRESS, 0xF5, 0xA0 );

	
	// Read 8 bytes of data from register(0xF7)
	// pressure msb1, pressure msb, pressure lsb, temp msb1, temp msb, temp lsb, humidity lsb, humidity msb
	//for( i = 0; i < 8; i++ )
	//{
	//	BUF[i] = Single_Read( BMP280_I2C_ADDRESS, 0xF7 ); 
	//	if( BMP280_readRC == FALSE ) return;
	//}
	//Single_Read( BMP280_I2C_ADDRESS, 0xF7 , 8 ); 


}

	 