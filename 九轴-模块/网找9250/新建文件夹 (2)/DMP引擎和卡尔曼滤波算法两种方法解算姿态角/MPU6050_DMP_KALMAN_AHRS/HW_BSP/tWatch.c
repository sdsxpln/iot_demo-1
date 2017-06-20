#include "twatch.h"

tWatch td;

unsigned int StopWatchInit(tWatch *sw)
{
    sw->tFirst = micros();
    sw->tLast = sw->tFirst;
    return sw->tLast;
}

unsigned int StopWatchNow(tWatch *sw)
{
    return sw->tLast;
}


unsigned int StopWatchLap(tWatch *sw)
{
    unsigned int tNow = micros();
    unsigned int tDelta = tNow - sw->tLast;
    sw->tLast = tNow;
    return tDelta;
}


unsigned int StopWatchTotal(tWatch *sw)
{
    return sw->tLast - sw->tFirst;
}
