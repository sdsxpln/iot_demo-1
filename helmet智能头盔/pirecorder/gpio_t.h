//
#ifndef gpio_t_H
#define gpio_t_H

#include "2.h"



class gpio_t 
{
public:
	wl::WCrsc  m_lck;

public:
	gpio_t();
	virtual ~gpio_t();
	
	virtual void beep_on();
	virtual void beep_off();
	virtual void beep_sound( int i );
	virtual void led_on();
	virtual void led_off();
	virtual int get_button();
	virtual int get_miclevel();

};



extern gpio_t  *g_pgpio;



#endif



