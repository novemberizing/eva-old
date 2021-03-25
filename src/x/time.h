#ifndef   __NOVEMBERIZING_X__TIME__H__
#define   __NOVEMBERIZING_X__TIME__H__

#include <x/std.h>

struct xtime;

typedef struct xtime xtime;

struct xtime
{
    xint64 second;
    xint64 nanosecond;
};

extern xtime xtimeget(void);
extern xtime xtimediff(const xtime * x, const xtime * y);

#endif // __NOVEMBERIZING_X__TIME__H__
