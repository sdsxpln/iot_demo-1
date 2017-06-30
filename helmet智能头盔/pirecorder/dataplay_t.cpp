//
#include "2.h"
#include "dataplay_t.h"
#include "soundboy_t.h"


	
//
dataplay2_t::dataplay2_t()	
{
}



//
dataplay2_t::~dataplay2_t()	
{
}



//
int dataplay2_t::tr_on_user_run()
{
	WTcpCells &tcps(*this);
	SCake ck; 
	WFile fl;

	tcps.recv_all( ck );

	fl.bind( "test2.wav" );
	fl.write( ck );
	WFile::run_exe( "sudo aplay test2.wav" );
	//WFile::run_exe( "sudo mpv test2.wav" );

	return 0;
}


//////////////////////////////////////////////////////////////////////////////

//
dataplay_t::dataplay_t()	
{
	m_lisn.Listen( 3024 );
}



//
dataplay_t::~dataplay_t()	
{
}



//
int dataplay_t::tr_on_user_run()
{
	WThrd::tr_sleepu( 0.3 );

	dataplay2_t  *p;
	
	p = new dataplay2_t();

	p->Conn( this->m_lisn );
	
	p->tr_openx();

	return 1;
}




