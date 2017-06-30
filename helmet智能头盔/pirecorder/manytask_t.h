//
#ifndef manytask_t_H
#define manytask_t_H

#include "2.h"



class manytask_t : public WThrd  , public WIdleThrd< std::string >
{
public:

public:
	manytask_t();
	virtual ~manytask_t();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
	virtual void tr_on_post_thrd();
	virtual void OnRunTask( std::string s );

};




#endif



