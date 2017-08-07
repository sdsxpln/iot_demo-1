
 //	2017-07-26

//#include "reg52.h"
#include "string.h"
#include "a_strfunc.h"
#include "a_timerfunc.h"


//比如stc89c52为0xe7，stc125a60s2为0xc7; 

sfr IAP_CONTR=0xc7;



#if 1



// e.g.
//struct	TM_t	tm_grind1;
//struct	TM_t	tm_pause1;
//struct	TM_t	tm_dim;
//struct	TM_t	tm_total;




/* 支持的优先级是：在timer中走tk， 在main中rst
	或在main中走tk和rst	*/



//0=在timer中走tk， 在main中rst
//1=在main中走tk和rst
#define TM_PRIORITY_MODE  0



//0=tk频繁，rst不频繁
//1=tk缓慢，rst频繁
#define TM_OFTEN_MODE  0





//
void tm_init( struct TM_t *t )
{
	//t->rst_cmd = 0;
	//t->rst_value = 0;
	//t->inter_counter = 0;
	//t->overflow_flag = 0;
	//t->pause_cmd = 0;
	//t->ex_is_busy0 = 0;
	//t->ex_is_busy1 = 0;
	//t->ex_is_hot0 = 0;
	//t->ex_is_hot1 = 0;
	//t->ex_counter0 = 0;
	//t->ex_counter1 = 0;
	//t->ex_counter2 = 0;


	memset( t, 0, sizeof(struct TM_t) );		
	
	t->overflow_flag = 1;
}



//每个tk触发一次减1
void tm_tk( struct TM_t *t )
{
	if( t->rst_cmd ) 
	{
		t->inter_counter = t->rst_value;

		t->overflow_flag = 0;
 

#if TM_PRIORITY_MODE == 0  
		t->rst_cmd = 0;
#else 
 
	//如果tk频繁则tk中应该--，如果rst频繁则tk中应该直接清0
	#if TM_OFTEN_MODE == 0
			t->rst_cmd --;
	#else 
			t->rst_cmd = 0;
	#endif
   
#endif

	}


	do{

		if( t->inter_counter == 0 )
		{
			t->overflow_flag = 1;
			break;
		}

		if( t->pause_cmd ) break;

		t->inter_counter --;
	
		if( t->inter_counter == 0 )
		{
			t->overflow_flag = 1;
			break;
		}

	}while(0);

	if( !t->ex_is_busy0 )
	{
		t->ex_counter0 = t->inter_counter;
		t->ex_is_hot0 = 1;
	}

	if( !t->ex_is_busy1 )
	{
		t->ex_counter1 = t->inter_counter;
		t->ex_is_hot1 = 1;
	}
}




#if 1
//每次触发可能经过n个tk，要减n
void tm_tk_n( struct TM_t *t, unsigned char t1, unsigned char t2 )
{
	for( ; t1 != t2 ; t1++ )
		tm_tk( t );
}
#endif




#if 0
//
void tm_mainfollow( struct TM_t *t )
{
	t->ex_is_busy0 = 1;
	if( t->ex_is_hot0 )
	{
		t->ex_counter2 = t->ex_counter0;
	}
	t->ex_is_hot0 = 0;
	t->ex_is_busy0 = 0;

	t->ex_is_busy1 = 1;
	if( t->ex_is_hot1 )
	{
		t->ex_counter2 = t->ex_counter1;
	}
	t->ex_is_hot1 = 0;
	t->ex_is_busy1 = 0;
}
#endif






//频繁rst允许，但代价是 不能影响到初始值。	
//如果tk频繁则tk中应该--，如果rst频繁则tk中应该直接清0
void tm_rst( struct TM_t *t, U32 rst_value ) 
{
	//rst_cmd本身就是一种busy flag可以在外部判断busy_flag，进来时必须已经不busy_flag。或者完全不看busy_flag标记。

#if TM_PRIORITY_MODE == 0  
	if( t->rst_cmd ) return;
#else              
	if( t->rst_cmd > 200 ) return;
#endif

	t->rst_value = rst_value;//先有value后有cmd则可防同步问题

	if( rst_value != 0 ) t->overflow_flag = 0; else t->overflow_flag = 1;


#if TM_PRIORITY_MODE == 0  
		t->rst_cmd = 1;
#else              
		if( t->rst_cmd < 200 ) t->rst_cmd ++;
#endif
}


#endif








#if 1

void tm_rst1( struct TM_t *t, U32 rst_value )
{
#if TM_PRIORITY_MODE == 0  
	if( t->rst_cmd ) return;
#else              
	if( t->rst_cmd > 200 ) return;
#endif

	t->rst_value = rst_value;// 	

	if( rst_value != 0 ) t->overflow_flag = 0; else t->overflow_flag = 1;

#if TM_PRIORITY_MODE == 0  
		t->rst_cmd = 1;
#else              
		if( t->rst_cmd < 200 ) t->rst_cmd ++;
#endif
}

#endif






#if 0

void tm_rst2( struct TM_t *t, U32 rst_value )
{
#if TM_PRIORITY_MODE == 0  
	if( t->rst_cmd ) return;
#else              
	if( t->rst_cmd > 200 ) return;
#endif

	t->rst_value = rst_value;// 	

	if( rst_value != 0 ) t->overflow_flag = 0; else t->overflow_flag = 1;	

#if TM_PRIORITY_MODE == 0  
		t->rst_cmd = 1;
#else              
		if( t->rst_cmd < 200 ) t->rst_cmd ++;
#endif
}

#endif











//============= tk 类型，统一登记制度	

#if 0


struct TMRTKALL_t
{
	struct TM_t		*m_ptm;		
};


static struct TMRTKALL_t  tmrtkall_ws[4];
static	U8				  tmrtkall_end = 0; //相当于stl中的end，是无效元素			



void tmtkall_reg( struct TM_t *t ) 		//登记和初始化
{
	if( tmrtkall_end >= 4 )
	{
		IAP_CONTR |= 1<<5; 

		IAP_CONTR = 0x60; /////////////////总量和上面的数组长度一致////
	}

	tmrtkall_ws[tmrtkall_end].m_ptm = t;

	tm_init( t ); //先初始化再宣布它的存在，不让tk 出问题。
	//tm_rst( t, 0 );

	tmrtkall_end++; // 再宣布它的存在	
}


void tmtkall_tk()
{
	U8 i;
	for( i = 0; i < tmrtkall_end; i++ )
	{
		tm_tk( tmrtkall_ws[i].m_ptm );
	}
}


void tmtkall_mainfollow()
{
	U8 i;
	for( i = 0; i < tmrtkall_end; i++ )
	{
		tm_mainfollow( tmrtkall_ws[i].m_ptm );
	}
}




#endif



