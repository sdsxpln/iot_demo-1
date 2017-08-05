
#ifndef __H_TIMERFUNC_H_H
#define __H_TIMERFUNC_H_H

 //	2017-07-26	




struct TM_t
{
	U8	rst_cmd	;//1	reset command	0	t->rst_cmd = 0;		
	U32	rst_value	;//2	reset value	0	t->rst_value = 0;		
	U32	inter_counter	;//3	internal counter	0	t->inter_counter = 0;		
	U8	overflow_flag	;//4	time over flag	0	t->overflow_flag = 0;		
	U8	pause_cmd	;//5	pause command	0	t->pause_cmd = 0;		
	U8	ex_is_busy0	;//6	外部计数	0	t->ex_is_busy0 = 0;		
	U8	ex_is_busy1	;//7		0	t->ex_is_busy1 = 0;		
	U8	ex_is_hot0	;//8		0	t->ex_is_hot0 = 0;		
	U8	ex_is_hot1	;//9		0	t->ex_is_hot1 = 0;		
	U32	ex_counter0	;//10		0	t->ex_counter0 = 0;		
	U32	ex_counter1	;//11		0	t->ex_counter1 = 0;		
	U32	ex_counter2	;//12	外部跟踪值。只有main能读。别的级只能读各标志	0	t->ex_counter2 = 0;		

};





extern void tm_init( struct TM_t *t );	//初始化
extern void tm_tk( struct TM_t *t );	//走时函数
extern void tm_tk_n( struct TM_t *t, unsigned char t1, unsigned char t2 );		//多次走时函数
extern void tm_mainfollow( struct TM_t *t );			//内部计数器查询支撑函数
extern void tm_rst( struct TM_t *t, U32 rst_value );	//重置定时器函数

void tm_rst1( struct TM_t *t, U32 rst_value );
void tm_rst2( struct TM_t *t, U32 rst_value );



void tmtkall_reg( struct TM_t *t );	//登记和初始化
void tmtkall_tk();			//统一走时
void tmtkall_mainfollow();	//统一追平






#endif












