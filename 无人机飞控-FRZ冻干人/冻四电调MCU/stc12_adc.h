
//2017-02-06

#ifndef __H_STC12_ADC_H
#define __H_STC12_ADC_H


extern void InitADC(unsigned char ch_map);          // 允许的通道列表，用8个位来表示。可以允许多个通道。 

extern unsigned int GetADCResult(unsigned char ch);	// 0至7	共8个通道。一次只能激活一个通道。且必须是初始化时通道列表之中的通道。 

unsigned char GetADCResultU8(unsigned char ch);	// 


#endif
