//
#ifndef databoy_t_H
#define databoy_t_H

#include "2.h"
#include "manytask_t.h"



class databoy2_t : public WThrd , public WTcpCells	
{
public:

public:
	databoy2_t();
	virtual ~databoy2_t();
	
	virtual int tr_on_user_run();
};


//////////////////////////////////////////////////////////////////////////////

class databoy_t : public WThrd 
{
public:
	WTcpListener  m_lisn;

public:
	databoy_t();
	virtual ~databoy_t();
	
	virtual int tr_on_user_run();
};




#endif



