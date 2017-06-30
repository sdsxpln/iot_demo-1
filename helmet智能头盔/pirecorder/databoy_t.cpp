//
#include "2.h"
#include "databoy_t.h"
#include "soundboy_t.h"


	
//
databoy2_t::databoy2_t()	
{
}



//
databoy2_t::~databoy2_t()	
{
}



//
int databoy2_t::tr_on_user_run()
{
	WTcpCells &tcps(*this);
	SCake ck; 

	if( g_psoundboy->get_data( ck ) )
	{
		tcps.send_bin( ck );
	
		return 0;
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////

//
databoy_t::databoy_t()	
{
	m_lisn.Listen( 3023 );
}



//
databoy_t::~databoy_t()	
{
}



//
int databoy_t::tr_on_user_run()
{
	WThrd::tr_sleepu( 0.3 );

	databoy2_t  *p;
	
	p = new databoy2_t();

	p->Conn( this->m_lisn );
	
	p->tr_openx();

	return 1;
}




