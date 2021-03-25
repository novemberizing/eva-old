#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "thread.h"
#include "time.h"

extern xtime xtimeget(void)
{
    xtime o = { 0,  0 };

    if(clock_gettime(CLOCK_REALTIME, (struct timespec *) xaddressof(o)) != xsuccess)
    {
        xassertion(xtrue, "clock_gettime (...) => %d", errno);
    }

    return o;
}

extern xtime xtimediff(const xtime * x, const xtime * y)
{
    xtime o = { x->second - y->second, x->nanosecond - y->nanosecond };

    if(o.nanosecond < 0)
    {
        o.second = o.second - 1;
        o.nanosecond = 1000000000 + o.nanosecond;
    }

    return o;
}