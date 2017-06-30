//
#ifndef dataplay_t_H
#define dataplay_t_H

#include "2.h"
#include "manytask_t.h"



class dataplay2_t : public WThrd , public WTcpCells	
{
public:

public:
	dataplay2_t();
	virtual ~dataplay2_t();
	
	virtual int tr_on_user_run();
};


//////////////////////////////////////////////////////////////////////////////

class dataplay_t : public WThrd 
{
public:
	WTcpListener  m_lisn;

public:
	dataplay_t();
	virtual ~dataplay_t();
	
	virtual int tr_on_user_run();
};




#endif



