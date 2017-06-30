//
#include "2.h"
#include "cmdboy_t.h"
#include "soundboy_t.h"


	
//
cmdboy2_t::cmdboy2_t()	
{
}



//
cmdboy2_t::~cmdboy2_t()	
{
}



//
int cmdboy2_t::tr_on_user_run()
{
	WTcpCells &tcps(*this);
	SCake ck;
	std::string strCmd;
	WFile fl;
	
	fl.bind( "test.wav" );

	tcps.recv_ln( ck );
	strCmd = ck.mk_str();
	SStrf::strim( strCmd );

	if( strCmd == "get_md5" )
	{
		if( !fl.exists() )
		{
			WThrd::tr_sleepu( 3 );
		}
		else
		{
			tcps.send_str( g_psoundboy->get_md5() );
			tcps.send_str( "\n" );
		}

		return 0;
	}


 	if( strCmd == "del" )
	{
		fl.erase();
		tcps.send_str( "ok\n" );
	
		return 0;
	}

	tcps.send_str( "i cannot explain the command.`" + strCmd + "`\n" );

	return 0;
}




//////////////////////////////////////////////////////////////////////////////////////

//
cmdboy_t::cmdboy_t()	
{
	m_lisn.Listen( 3022 );
}



//
cmdboy_t::~cmdboy_t()	
{
}



//
int cmdboy_t::tr_on_user_run()
{
	WThrd::tr_sleepu( 0.3 );

	cmdboy2_t  *ptcps;

	ptcps = new cmdboy2_t();
	ptcps->Conn( this->m_lisn );
	ptcps->tr_openx();	 

	return 1;
}



