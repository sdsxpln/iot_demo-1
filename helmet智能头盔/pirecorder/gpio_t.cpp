//
#include "2.h"
#include "gpio_t.h"




gpio_t  *g_pgpio;


//
gpio_t::gpio_t()	
{
}



//
gpio_t::~gpio_t()	
{
}



//
void gpio_t::beep_on()
{
	MYAUTOLOCK( this->m_lck );
	wl::WFile::run_exe( "python3 beep_on.py" );
}
	 
	 

//
void gpio_t::beep_off()
{
	MYAUTOLOCK( this->m_lck );
	wl::WFile::run_exe( "python3 beep_off.py" );
}
	 

//
void gpio_t::beep_sound( int i )
{
	for( int j = 0; j < i; j++ )
	{
		beep_on();
		wl::WThrd::tr_sleepu( 0.06 );
		beep_off();
		if( j != (i-1) ) wl::WThrd::tr_sleepu( 0.06 );
	}
}




//
void gpio_t::led_on()
{
	MYAUTOLOCK( this->m_lck );
	wl::WFile::run_exe( "python3 led_on.py" );
}
	 
	 

//
void gpio_t::led_off()
{
	MYAUTOLOCK( this->m_lck );
	wl::WFile::run_exe( "python3 led_off.py" );
}
	 




//
int gpio_t::get_button()
{
	MYAUTOLOCK( this->m_lck );

	WFile fl;
	std::string str;
	
	WFile::run_exe( "python3 get_button.py" );

	fl.bind( "get_button_status" );
	fl.read_str( str );

	return (int)SStrf::satol( str );
}




//
int gpio_t::get_miclevel()
{
	MYAUTOLOCK( this->m_lck );

	WFile fl;
	std::string str;
	
	WFile::run_exe( "python3 get_miclevel.py" );

	fl.bind( "get_miclevel_status" );
	fl.read_str( str );

	return (int)SStrf::satol( str );
}



