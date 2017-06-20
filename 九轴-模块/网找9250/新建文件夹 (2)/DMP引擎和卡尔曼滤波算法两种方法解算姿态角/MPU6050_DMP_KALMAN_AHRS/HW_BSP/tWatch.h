#ifndef __TWATCH_H_
#define __TWATCH_H_

#include "stm32f10x.h"
#include "systick.h"

typedef struct
{
    unsigned int tFirst;
    unsigned int tLast;
} tWatch;
extern tWatch td;
unsigned int StopWatchInit(tWatch *sw);
unsigned int StopWatchNow(tWatch *sw);
unsigned int StopWatchLap(tWatch *sw);
unsigned int StopWatchTotal(tWatch *sw);
#endif
