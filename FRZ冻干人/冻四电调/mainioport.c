
#include "UNIQ_ID.h"
#include "mainioport.h"




void mainioport_init(void)
{
	// 4 ÐýÒí
	SET_PORT_POWER_1( P0, 6 );
	SET_PORT_POWER_1( P0, 7 );
	SET_PORT_POWER_1( P1, 3 );
	SET_PORT_POWER_1( P1, 2 );
	

	SET_PORT_POWER_1( P1, 5 );	//LED1
	SET_PORT_POWER_1( P1, 4 );	//LED2
	SET_PORT_POWER_1( P1, 6 );	//BEEP1


	SET_PORT_POWER_0( P0, 2 );	//BUTT1	


	//bmp180
	SET_PORT_POWER_0( P2, 0 );	 
	SET_PORT_POWER_0( P4, 4 );	 


	//mpu9250iica
	SET_PORT_POWER_0( P4, 3 );	 
	SET_PORT_POWER_0( P4, 2 );	 


}




