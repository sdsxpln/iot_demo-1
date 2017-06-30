
//
#include "2.h"
#include "env_t.h"
#include "gpio_t.h"
#include "soundboy_t.h"
#include "cmdboy_t.h"
#include "databoy_t.h"
#include "dataplay_t.h"




//
int main(int argc, char* argv[])
{
	env_t e;
	gpio_t  gpio;
	soundboy_t  soundboy;

	gp_env = &e;

	WNava &nv( gp_env->m_nvCmdLn );

	nv.InterpCmdLine( argc, argv );

	g_pgpio = &gpio;
	g_psoundboy = &soundboy;

	if( nv.get( "--help" ) != "" || nv.get( "-help" ) != "" || nv.get( "-h" ) != "" )
	{
		printf( "%s %s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
		printf( "%s\n", gp_env->m_strHelp.c_str() );
		
		goto L_MAINEND;
	}

	if(1)
	{
		g_pgpio->beep_off();
		g_pgpio->led_off();
		wl::WThrd::tr_sleep(1);
		g_pgpio->beep_on();
		wl::WThrd::tr_sleep(1);
		g_pgpio->beep_off();

		WFile::run_exe( "sudo amixer sset PCM 100%" );
		WFile::run_exe( "sudo amixer -c 1 cset numid=8 20" );
		WFile::run_exe( "sudo amixer -c 1 cset numid=6 36" );

		//wl::SStrf::newobjptr<cmdboy_t>()->tr_openx();
		//wl::SStrf::newobjptr<databoy_t>()->tr_openx();
		//wl::SStrf::newobjptr<dataplay_t>()->tr_openx();

		while(1)
		{
			WFile f;

			if( g_pgpio->get_button() || g_pgpio->get_miclevel() )
			{
				g_pgpio->led_on();
				g_pgpio->beep_sound( 2 );
				g_pgpio->led_on();

				//begin record
				g_psoundboy->begin_record();
				printf( "%s\n", g_psoundboy->get_md5().c_str() );

				g_pgpio->led_off();
				g_pgpio->beep_sound( 3 );
		
				// get net data
				f.bind( "test3.wav" );
				f.erase();
				WFile::run_exe( "python3 t02post.py" );
				if( f.exists() )
				{
					g_psoundboy->play_back();
				}

			}
			
			//g_pgpio->led_on();
			//g_pgpio->beep_sound( 3 );
			//g_pgpio->led_off();
			//g_pgpio->beep_sound( 3 );

			f.bind( "ter.txt" ); // exit the process
			if( f.exists() )
			{
				g_pgpio->led_on();
				g_pgpio->beep_sound( 1 );
				g_pgpio->led_off();

				f.erase();
				return 0;
			}
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


