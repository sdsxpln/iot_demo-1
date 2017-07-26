
#ifndef __H_STRFUNC_H_H
#define __H_STRFUNC_H_H
 
// 2017-01-12


//typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  无符号8位整型变量  */
//typedef signed   char  S8;       /* defined for signed 8-bits integer variable		  有符号8位整型变量  */
//typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	  无符号16位整型变量 */
//typedef signed   int   S16;      /* defined for signed 16-bits integer variable 	  有符号16位整型变量 */
//typedef unsigned long  U32;      /* defined for unsigned 32-bits integer variable 	  无符号32位整型变量 */
//typedef signed   long  S32;      /* defined for signed 32-bits integer variable 	  有符号32位整型变量 */
//typedef float          F32;      /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
//typedef double         F64;      /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */



typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  无符号8位整型变量  */
typedef signed   char  I8;       /* defined for signed 8-bits integer variable		  有符号8位整型变量  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	  无符号16位整型变量 */
typedef signed   int   I16;      /* defined for signed 16-bits integer variable 	  有符号16位整型变量 */
typedef unsigned long  U32;      /* defined for unsigned 32-bits integer variable 	  无符号32位整型变量 */
typedef signed   long  I32;      /* defined for signed 32-bits integer variable 	  有符号32位整型变量 */ 



typedef		char					tint8;
typedef		unsigned char			tuint8;
typedef		int						tint16;
typedef		unsigned int			tuint16;
typedef		long					tint32;
typedef		unsigned long			tuint32;



extern void myltoa( unsigned char * szOut, unsigned long i, unsigned char NumNum );


void sharedata_interrupt_ready( void *tWork, void *t0, void *t1, int len );
void sharedata_main_followrefresh( void *t0, void *t1, void *t2, int len );

void sharedata_main_ready( void *tWork, void *t0, void *t1, int len );
void sharedata_interrupt_followrefresh( void *t0, void *t1, void *t2, int len );



U16 buf_del_head( U8 *p, U16 qlen, U16 headlen );


void		  bs_9_A( unsigned char c, unsigned char *p_dest );
unsigned char bs_A_9( unsigned char *p_src );
unsigned int bs_decode( unsigned char *p_src_dest );



U8 *pick_strarr2( U8 idx, U8 *s0, U8 *s1 );



extern GetLED( unsigned char s );



extern void mk_busycode( unsigned char src, unsigned char *pDest );	//起始符=多个32	结束符=33	
extern unsigned char chk_busycode( unsigned char *p );




//extern signed char mycompare( unsigned char *a1, unsigned char *a2 ) reentrant;

//typedef signed char (*pf_compare_t)( unsigned char *a1, unsigned char *a2 ) reentrant;
//extern void a_sortf( unsigned char *x, int datablocknum, int datablocklen, pf_compare_t pf_comp );
//




extern void mk_chksumU8( unsigned char * sz1, unsigned int iLen );
extern unsigned char chk_chksumU8( unsigned char * sz1, unsigned int iLen );


extern void mk_chk2sumU8( unsigned char * sz1, unsigned int iLen );
extern unsigned char chk_chk2sumU8( unsigned char * sz1, unsigned int iLen );


extern void mk_chk3sumU8( unsigned char * sz1, unsigned int iLen );
extern unsigned char chk_chk3sumU8( unsigned char * sz1, unsigned int iLen );


extern void mk_chk4sumU8( unsigned char * sz1, unsigned int iBufLen, unsigned char iChkLen );
extern unsigned char chk_chk4sumU8( unsigned char * sz1, unsigned int iBufLen, unsigned char iChkLen );


extern void mk_chk5sumU8( unsigned char * sz1, unsigned int iBufLen, unsigned char iChkLen );
extern unsigned char chk_chk5sumU8( unsigned char * sz1, unsigned int iBufLen, unsigned char iChkLen );




#endif












