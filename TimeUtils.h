#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include "btIntDefines.h"

uint64_t	ReadClockTicks();
uint64_t	TicksToNanoSeconds(uint64_t ticks);
double		TicksToSeconds(uint64_t ticks);

#endif
