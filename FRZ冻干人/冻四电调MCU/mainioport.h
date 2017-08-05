
#ifndef ___MAINIO_H_H
#define ___MAINIO_H_H



sbit OUTtta = P0 ^ 6;	
sbit OUTttb = P0 ^ 7;	
sbit OUTttc = P1 ^ 3;	
sbit OUTttd = P1 ^ 2;	 

sbit LED1 = P1 ^ 5;	 
sbit LED2 = P1 ^ 4;	 
sbit BEEP1 = P1 ^ 6;	 

sbit BUTT1 = P0 ^ 2;	 



extern void mainioport_init(void);


#define  _OUTtta_low_value	    	1 
#define  _OUTtta_high_value	    	0 


#define LET_OUTtta_HIGH	    	OUTtta = _OUTtta_high_value 
#define LET_OUTtta_LOW			OUTtta = _OUTtta_low_value 

#define LET_OUTttb_HIGH	    	OUTttb = _OUTtta_high_value 
#define LET_OUTttb_LOW			OUTttb = _OUTtta_low_value 

#define LET_OUTttc_HIGH	    	OUTttc = _OUTtta_high_value 
#define LET_OUTttc_LOW			OUTttc = _OUTtta_low_value 

#define LET_OUTttd_HIGH	    	OUTttd = _OUTtta_high_value 
#define LET_OUTttd_LOW			OUTttd = _OUTtta_low_value 



#define LET_LED1_ON	    		LED1 = 1 
#define LET_LED1_OFF	    	LED1 = 0 


#define LET_LED2_ON	    		LED2 = 1 
#define LET_LED2_OFF	    	LED2 = 0 


#define LET_BEEP1_ON	    	BEEP1 = 1 
#define LET_BEEP1_OFF	    	BEEP1 = 0 


#define GET_BUTT1	    	( BUTT1 == 0 ? 1 : 0 ) 



#endif




