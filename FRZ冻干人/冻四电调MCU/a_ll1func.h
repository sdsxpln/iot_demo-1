
#ifndef __H_LL1FUNC_C_H
#define __H_LL1FUNC_C_H


//2017-01-13


struct ll1_ws_t
{
	unsigned char * m_sen_buf; 
	unsigned int    m_sen_buflen; 
	unsigned int    m_sen_bufidx; 

	unsigned char m_rc; 
	unsigned char m_c; 
	
	unsigned int	m_stack_buf[5]; 
	unsigned char   m_stack_bufidx; 
};



//extern struct ll1_ws_t  ll1_ws0;
extern struct ll1_ws_t *ll1_pws;





extern void ll1_reset( unsigned char * psenbuf , unsigned int senbuflen ); 
extern void ll1_eat1(); 
extern void ll1_back1(); 
extern void ll1_eat_binvt( unsigned char *p, unsigned int len ); 
extern void ll1_eat_szvt( unsigned char *sz ); 
extern unsigned long ll1_eat_uint(); 
extern unsigned int ll1_eat_str_blackvt( unsigned char *blackvtset , unsigned char HaveEof ); // 返回起始sen_index
extern unsigned int ll1_eat_str_whitevt( unsigned char *whitevtset ); // 返回起始sen_index
extern void ll1_push(); 
extern void ll1_pop();






#endif


