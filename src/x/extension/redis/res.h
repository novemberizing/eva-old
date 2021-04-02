#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_RES__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_RES__H__

#include <x/req.h>
#include <x/res.h>
#include <x/extension/redis/req.h>

struct xredisres;

typedef struct xredisres xredisres;

typedef xredisres * (*xredisresdestructor)(xredisres *);
typedef xint64 (*xredisresdeserializer)(xredisres *, xstream *);
typedef xuint64 (*xredisrespredictor)(xredisres *, xuint64);

struct xredisres
{
    /** INHERITED MEMBER */
    xredisresdestructor   rem;
    xtime                 end;
    xredisreq *           req;
    xuint32               status;
    xredisresdeserializer deserialize;
    xredisrespredictor    predict;
    /** MEMBER */
    xredisobject *        object;
};

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_RES__H__
