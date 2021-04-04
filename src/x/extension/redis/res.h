#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_RES__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_RES__H__

#include <x/req.h>
#include <x/res.h>
#include <x/extension/redis/req.h>

struct xredisreq;
struct xredisres;

typedef struct xredisreq xredisreq;
typedef struct xredisres xredisres;

typedef xredisres * (*xredisresdestructor)(xredisres *);
typedef xint64 (*xredisresserializer)(xredisres *, xbyte **, xuint64 *, xuint64 *, xuint64 *);
typedef xint64 (*xredisressizepredictor)(xredisres *, xbyte *, xuint64, xuint64);
typedef xint64 (*xredisresdeserializer)(xredisres *, xbyte *, xuint64, xuint64);

struct xredisres
{
    /** INHERITED SERIALIZABLE */
    xredisresdestructor    rem;
    xredisresserializer    serialize;
    /** INHERITED RES MEMBER */
    xtime                  end;
    xuint32                status;
    xredisreq *            req;
    xredisressizepredictor predict;
    xredisresdeserializer  deserialize;
    /** REDIS RES MEMBER */
    xredisobject *         object;
};

extern xredisres * xredisresnew(xredisreq * req);
extern xredisres * xredisresrem(xredisres * o);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_RES__H__
