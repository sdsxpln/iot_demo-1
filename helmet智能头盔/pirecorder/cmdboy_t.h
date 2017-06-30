//
#ifndef cmdboy_t_H
#define cmdboy_t_H

#include "2.h"
#include "manytask_t.h"




class cmdboy2_t : public WThrd , public WTcpCells	
{
public:

public:
	cmdboy2_t();
	virtual ~cmdboy2_t();
	
	virtual int tr_on_user_run();
};



//////////////////////////////////////////////////////////////////////////////////////



class cmdboy_t : public WThrd
{
public:
	WTcpListener  m_lisn;

public:
	cmdboy_t();
	virtual ~cmdboy_t();
	
	virtual int tr_on_user_run();
};




#endif



