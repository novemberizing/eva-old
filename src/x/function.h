#ifndef   __NOVEMBERIZING_X__FUNCTION__H__
#define   __NOVEMBERIZING_X__FUNCTION__H__

#include <x/std.h>

struct xfunction;

typedef struct xfunction xfunction;

typedef void (*xfunctionexec)(xfunction * o);

struct xfunction
{
    xfunctionexec call;
};

#define xfunctioncall(o)    (o->call(o))

#endif // __NOVEMBERIZING_X__FUNCTION__H__
