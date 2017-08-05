
#ifndef __H_COMFUNC_H_H
#define __H_COMFUNC_H_H

// 2016-10-02	



extern unsigned char  Com1_TI_flag;

extern void Com1SendU8( unsigned char c ); 
extern void Com1SendU8ss( unsigned char * s );
extern void Com1SendU8is( unsigned long i, unsigned char * buf );



extern unsigned char  Com1Recv_rc;
extern unsigned char  Com1Recv_c; 
extern unsigned int  Com1Recv_TimeOutLmt;

extern void Com1Recv();




extern unsigned char Com2_TI_flag;

extern void Com2SendU8( unsigned char c ); 
extern void Com2SendU8ss( unsigned char * s );
extern void Com2SendU8is( unsigned long i, unsigned char * buf );





#endif












