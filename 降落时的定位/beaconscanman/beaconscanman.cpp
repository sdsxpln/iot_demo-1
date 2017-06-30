
//
#include "2.h"
#include "env_t.h"
#include "gfunc_md5.h"




//
int main(int argc, char* argv[])
{
	env_t e;

	gp_env = &e;

	WNava &nv( gp_env->m_nvCmdLn );

	nv.InterpCmdLine( argc, argv );


	if( nv.get( "--help" ) != "" || nv.get( "-help" ) != "" || nv.get( "-h" ) != "" )
	{
		printf( "%s %s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
		printf( "%s\n", gp_env->m_strHelp.c_str() );
		
		goto L_MAINEND;
	}

	if(1)
	{
		std::string  addrInfo;
		std::string  addrData;
		std::string  addrPlbk;
		std::string  strMd5old = "aa";
		std::string  strMd5 = "abc";

		addrInfo = "10.12.73.13:3022";
		addrData = "10.12.73.13:3023";
		addrPlbk = "10.12.73.13:3024";
		
		if( nv.get( "-ip" ) != "" )
		{
			wl::SStrf::sreplstr( addrInfo, "10.12.73.13", nv.get( "-ip" ) );
			wl::SStrf::sreplstr( addrData, "10.12.73.13", nv.get( "-ip" ) );
			wl::SStrf::sreplstr( addrPlbk, "10.12.73.13", nv.get( "-ip" ) );
		}

		while(1)
		{
			if( !IsOsWin() )
			{
				WFile::run_exe( "amixer sset PCM 100%" );
			}
			WThrd::tr_sleepu( 0.9 );
				 
			WTcpCellc  tcpcInfo;
			WTcpCellc  tcpcData;
			SCake ck;
		
			tcpcInfo.killer_up( 9 );
			//tcpcData.killer_up( 9 );

			if( !tcpcInfo.Conn( addrInfo ) )
			{
				WThrd::tr_sleepu( 0.06 );
			
				continue;
			}

			printf( "begin.\t" );

			tcpcInfo.send_str( "get_md5\n" );
			tcpcInfo.recv_ln( ck );
			tcpcInfo.DisConn();

			if( ck.len() == 0 )
			{
				continue;
			}

			printf( "i after get_md5.\t" );
		
			strMd5 = ck.mk_str();

			if( strMd5old == strMd5 )
			{
				if( !tcpcInfo.Conn( addrInfo ) )
				{
					WThrd::tr_sleepu( 0.06 );
					
					continue;
				}

				tcpcInfo.send_str( "del\n" );
				tcpcInfo.recv_ln( ck );
				tcpcInfo.DisConn();
				
				continue;
			}
			
			strMd5old = strMd5;
			
			if( !tcpcData.Conn( addrData ) )
			{
				WThrd::tr_sleepu( 0.06 );
			
				continue;
			}
			
			tcpcData.recv_all_f( ck );
			tcpcData.DisConn();
		 
			WFile fl;

			fl.bind( "test.wav" );
			fl.write( ck );
			//WFile::run_exe( "sudo aplay test.wav" );

			WTcpCellc  tcpcPlbk;
	
			if( !tcpcPlbk.Conn( addrPlbk ) )
			{
				WThrd::tr_sleepu( 0.06 );
		
				printf( "i Conn.\n" );
			
				continue;
			}
		
			printf( "i send_bin ck.\n" );

			tcpcPlbk.send_bin( ck );
			tcpcPlbk.DisConn();

		}
	}

	//show error msg, 不能解释的命令行参数。	 
	printf( "%s %s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
	printf( "i cannot explain command line.\n" );


L_MAINEND:
	if( IsOsWin() )
	{
		int i;
		//system("pause");
		i = WFile::run_exe("pause");
	}
	return 0;
}


