#include "TimeUtils.h"
#include <stdint.h>
#include <stdlib.h>

#include <inttypes.h>
#ifdef __APPLE__
#include <mach/mach_time.h>

#include <mach/mach_time.h>
uint64_t ReadClockTicks( void )
{
    return mach_absolute_time();
}
double  TicksToSeconds( uint64_t delta )
{
    static long double conversion = 0.0L;
    if( 0.0L == conversion )
    {
        // attempt to get conversion to nanoseconds
        mach_timebase_info_data_t info;
        int err = mach_timebase_info( &info );
        if( err )
            return __builtin_nanf("");
        conversion = info.numer / (1e9L * info.denom);
    }

    return (double) (delta * conversion);
}

uint64_t  TicksToNanoSeconds( uint64_t delta )
{
        static long double conversion = 0.0L;
        if( 0.0L == conversion )
        {
                // attempt to get conversion to nanoseconds
                mach_timebase_info_data_t info;
                int err = mach_timebase_info( &info );
                if( err )
                        return __builtin_nanf("");
                conversion = info.numer / info.denom;
        }

        return (delta * conversion);
}
#else
#include <sys/time.h>

uint64_t ReadClockTicks( void )
{
        timespec ts;
        clock_gettime(CLOCK_REALTIME,&ts);

        return 1000000000*ts.tv_sec + ts.tv_nsec;
}
uint64_t TimeToNanoSeconds( uint64_t ticks)
{
	return ticks;
}

double  TicksToSeconds( uint64_t delta )
{
return delta/1e9;
}

#endif

