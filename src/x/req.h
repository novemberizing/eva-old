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
typedef xint64 (*xreqserializer)(xreq *, xbyte **, xuint64 *, xuint64 *, xuint64 *);
typedef xres * (*xresgenerator)(xreq *);

struct xreq
{
    /** INHERITED SERIALIZABLE */
    xreqdestructor rem;
    xreqserializer serialize;
    /** REQ MEMBER */
    xtime          start;
    xtime          end;
    xresgenerator  gen;
};

#define xreqrem(req)    (req->rem(req))

#endif // __NOVEMBERIZING_X__REQ__H__
