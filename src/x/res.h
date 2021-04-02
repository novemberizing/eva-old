#ifndef   __NOVEMBERIZING_X__RES__H__
#define   __NOVEMBERIZING_X__RES__H__

#include <x/std.h>
#include <x/time.h>
#include <x/stream.h>

#define xresponsestatus_void            0x00000000u
#define xresponsestatus_complete        0x00000001u
#define xresponsestatus_exception       0x00000002u
#define xresponsestatus_timeout         0x00000004u

struct xres;
struct xreq;

typedef struct xres xres;
typedef struct xreq xreq;

typedef xres * (*xresdestructor)(xres *);
typedef xint64 (*xresdeserializer)(xres *, xstream *);
typedef xuint64 (*xrespredictor)(xres *, xuint64);

struct xres
{
    xresdestructor   rem;
    xtime            end;
    xreq *           req;
    xuint32          status;
    xresdeserializer deserialize;
    xrespredictor    predict;
};

#define xrescheck_complete(res)     (res->status & xresponsestatus_complete)

#endif // __NOVEMBERIZING_X__RES__H__
