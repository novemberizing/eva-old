#ifndef   __NOVEMBERIZING_X__TIME__H__
#define   __NOVEMBERIZING_X__TIME__H__

#include <x/std.h>

struct xtime;

typedef struct xtime xtime;

#define xtimevoid()     (xtime) { 0, 0 }
#define xtimeinit(s, n) (xtime) { s, n }

struct xtime
{
    xint64 second;
    xint64 nanosecond;
};

extern xtime xtimeget(void);
extern xtime xtimediff(const xtime * x, const xtime * y);
extern xint64 xtimecmp(const xtime * x, const xtime * y);
extern xtime xtimeavg(const xtime * sum, xuint64 n);

#endif // __NOVEMBERIZING_X__TIME__H__
