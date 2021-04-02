#ifndef   __NOVEMBERIZING_X__REQ__H__
#define   __NOVEMBERIZING_X__REQ__H__

#include <x/std.h>
#include <x/time.h>
#include <x/stream.h>

struct xreq;
struct xres;

typedef struct xreq xreq;
typedef struct xres xres;

typedef xreq * (*xreqdestructor)(xreq *);
typedef xint64 (*xreqserializer)(xreq *, xstream *);
typedef xres * (*xresgenerator)(xreq *);

struct xreq
{
    xreqdestructor rem;
    xtime          start;
    xtime          end;
    xreqserializer serialize;
    xresgenerator  gen;
};

#endif // __NOVEMBERIZING_X__REQ__H__
