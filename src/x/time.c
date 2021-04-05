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

extern xint64 xtimecmp(const xtime * x, const xtime * y)
{
    xint64 ret = x->second - y->second;
    if(ret == 0)
    {
        return x->nanosecond - y->nanosecond;
    }
    return ret;
}

extern xtime xtimeavg(const xtime * sum, xuint64 n)
{
    xtime ret = { sum->second / n, sum->nanosecond / n };

    if(ret.nanosecond > 1000000000)
    {
        ret.second = ret.second + ret.nanosecond / 1000000000; 
        ret.nanosecond = ret.nanosecond - ret.nanosecond / 1000000000;
    }

    return ret;
}