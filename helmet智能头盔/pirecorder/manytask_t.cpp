//
#include "2.h"
#include "manytask_t.h"


	
//
manytask_t::manytask_t()	
{
}



//
manytask_t::~manytask_t()	
{
}



//
void manytask_t::tr_on_pre_thrd()
{
	//printf( "C-%s\t", this->GetRemoteIPAddress().c_str() );
}



//
int manytask_t::tr_on_user_run()
{

	WThrd::tr_sleep( 3 );
 
	return 0;
}



//
void manytask_t::tr_on_post_thrd()
{
}



//
void manytask_t::OnRunTask( std::string s )
{
	 
}



