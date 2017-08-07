
//2017-01-13

//#include "reg52.h"
#include "a_ll1func.h"




struct ll1_ws_t  ll1_ws0;

struct ll1_ws_t *ll1_pws = &ll1_ws0;


#define    t   ll1_pws



/*------------------------------------------------
  
------------------------------------------------*/
#if 1
void ll1_reset( unsigned char * psenbuf , unsigned int senbuflen )
{
	ll1_pws = &ll1_ws0;

	t->m_sen_buf = psenbuf;
	t->m_sen_buflen = senbuflen;
	t->m_sen_bufidx = 0;
	t->m_rc = 0;
	t->m_c = 0;
	t->m_stack_bufidx = 0;
}
#endif



/*------------------------------------------------
  
------------------------------------------------*/
#if 1
void ll1_eat1()
{   
	if( t->m_sen_bufidx >= t->m_sen_buflen )
	{
		t->m_rc = 0;
		t->m_c = 0;
		return;
	}

	t->m_rc = 1;
	t->m_c = (t->m_sen_buf)[t->m_sen_bufidx];
	t->m_sen_bufidx++;
}
#endif




/*------------------------------------------------
  
------------------------------------------------*/
#if 1
void ll1_back1()
{   
	if( t->m_sen_bufidx <= 0 )
	{
		t->m_rc = 0;
		t->m_c = 0;
		return;
	}

	t->m_rc = 1;
	t->m_sen_bufidx--;
	t->m_c = (t->m_sen_buf)[t->m_sen_bufidx];
}
#endif




/*------------------------------------------------
  
------------------------------------------------*/
#if 0
void ll1_eat_binvt( unsigned char *p, unsigned int len )
{
	unsigned int j;

	for( j = 0; j < len; j++ )
	{
		ll1_eat1();

		if( t->m_rc == 0 )
		{
			return;
		}

		if( t->m_c != p[j] )
		{
			ll1_back1();
			t->m_rc = 0;
			t->m_c = 0;
			return;
		}
	}
}
#endif



/*------------------------------------------------
  
------------------------------------------------*/
#if 1
void ll1_eat_szvt( unsigned char *sz )
{
	unsigned int j;

	for( j = 0; sz[j]; j++ )
	{
		//if( sz[j] == 0 ) break;

		ll1_eat1();

		if( t->m_rc == 0 )
		{
			return;
		}

		if( t->m_c != sz[j] )
		{
			ll1_back1();
			t->m_rc = 0;
			t->m_c = 0;
			return;
		}
	}
}
#endif




/*------------------------------------------------
  
------------------------------------------------*/
#if 1
unsigned long ll1_eat_uint()
{
	unsigned int j;
	unsigned long u = 0;

	for( j = 0; ; j++ )
	{
		ll1_eat1();
	
		//if( t->m_rc == 0 ) break; 因为rc为0时返回必非数字型

		if( t->m_c >= '0' && t->m_c <= '9' )
		{
			u *= 10;
			u += t->m_c - '0';
		}
		else
		{
			ll1_back1();
			break;
		}
	}

	return u;
}
#endif





/*------------------------------------------------
  
------------------------------------------------*/
#if 0
unsigned int ll1_eat_str_blackvt( unsigned char *blackvtset , unsigned char HaveEof ) 
{
	unsigned int beginindex;
	unsigned int x;

	beginindex = t->m_sen_bufidx;

	for(;;)
	{
		ll1_eat1();
		
		if( t->m_rc == 0 )
		{
			if( HaveEof ) t->m_rc = 1; // Eof在follow集的情况	
			break;	
		}

		for( x = 0; blackvtset[x]; x++ )
		{
			if( t->m_c == blackvtset[x] )
			{
				ll1_back1();
				return beginindex;
			}
		}
	}

	return beginindex;
}
#endif




/*------------------------------------------------
  
------------------------------------------------*/
#if 1
unsigned int ll1_eat_str_whitevt( unsigned char *whitevtset ) 
{
	unsigned int beginindex;
	unsigned int x;

	beginindex = t->m_sen_bufidx;

	for(;;)
	{
		ll1_eat1();
		
		if( t->m_rc == 0 )
			break;	
	 
		for( x = 0; whitevtset[x]; x++ )
		{
			if( t->m_c == whitevtset[x] )
				break;	
		}

		if( whitevtset[x] == 0 )
		{
			ll1_back1();
			break;
		}
	}

	return beginindex;
}
#endif





/*------------------------------------------------
  
------------------------------------------------*/
#if 1
void ll1_push()
{ 
	(t->m_stack_buf)[t->m_stack_bufidx] = t->m_sen_bufidx;
	t->m_stack_bufidx++;
}
#endif



/*------------------------------------------------
  
------------------------------------------------*/
#if 1
void ll1_pop()
{ 
	t->m_stack_bufidx--;
	t->m_sen_bufidx = (t->m_stack_buf)[t->m_stack_bufidx];
}
#endif









