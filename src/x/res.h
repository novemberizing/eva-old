#ifndef   __NOVEMBERIZING_X__RES__H__
#define   __NOVEMBERIZING_X__RES__H__

#include <x/std.h>
#include <x/time.h>
#include <x/stream.h>

#define xresponsestatus_void            0x00000000u
#define xresponsestatus_complete        0x00000001u
#define xresponsestatus_exception       0x00000002u
#define xresponsestatus_timeout         0x00000004u
#define xresponsestatus_progress        0x00000008u

struct xreq;
struct xres;

typedef struct xreq xreq;
typedef struct xres xres;

typedef xres * (*xresdestructor)(xres *);
typedef xint64 (*xresserializer)(xres *, xbyte **, xuint64 *, xuint64 *, xuint64 *);
typedef xint64 (*xressizepredictor)(xres *, xbyte *, xuint64, xuint64);
typedef xint64 (*xresdeserializer)(xres *, xbyte *, xuint64, xuint64);

struct xres
{
    /** INHERITED SERIALIZABLE */
    xresdestructor    rem;
    xresserializer    serialize;
    /** RES MEMBER */
    xtime             end;
    xuint32           status;
    xreq *            req;
    xressizepredictor predict;
    xresdeserializer  deserialize;
};

#define xrescheck_complete(res)     (res->status & xresponsestatus_complete)

#endif // __NOVEMBERIZING_X__RES__H__
