//
#include "2.h"
#include "soundboy_t.h"
#include "gfunc_md5.h"




soundboy_t  *g_psoundboy;


//
soundboy_t::soundboy_t()	
{
}



//
soundboy_t::~soundboy_t()	
{
}



//
void soundboy_t::begin_record()
{
	MYAUTOLOCK( this->m_lck );

	//WFile::run_exe( "sudo arecord -d 5 -D plughw:1 test.wav" );
	//WFile::run_exe( "sudo arecord -d 5 -D plughw:1 -f S16_LE test.wav" );
	//WFile::run_exe( "sudo arecord -d 5 -D plughw:1 -f S16_LE -t raw test.wav" );
		
	WFile f;

	f.bind( "test.wav" );
	f.erase();
	f.bind( "test.opus" );
	f.erase();
	f.bind( "test.mp3" );
	f.erase();

	WFile::run_exe( "sudo arecord -d 4 -D plughw:1 -f S16_LE -c1 -r16000 test.wav" );
	//WFile::run_exe( "sudo opusenc test.wav test.opus" );
	//WFile::run_exe( "sudo avconv -i test.wav test.mp3" );
}
	 


//
void soundboy_t::play_back()
{
	MYAUTOLOCK( this->m_lck );
			
	WFile::run_exe( "sudo aplay -D plughw:1 test3.wav" );
}
	 
	 

//
std::string soundboy_t::get_md5()
{
	MYAUTOLOCK( this->m_lck );
			
	return md5str_file( "test.wav" );
}
	 
	 
	
//
bool soundboy_t::get_data( SCake &ckOut )
{
	MYAUTOLOCK( this->m_lck );
	WFile fl;
			
	fl.bind( "test.wav" );

	return !!fl.read( ckOut );
}
	
	 

