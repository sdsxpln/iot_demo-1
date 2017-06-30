//
#ifndef soundboy_t_H
#define soundboy_t_H

#include "2.h"



class soundboy_t 
{
public:
	wl::WCrsc  m_lck;

public:
	soundboy_t();
	virtual ~soundboy_t();
	
	virtual void begin_record();
	virtual void play_back(); 
	std::string get_md5();
	bool get_data( SCake &ckOut );
};



extern soundboy_t  *g_psoundboy;



#endif



