#ifndef   __NOVEMBERIZING_X__REDIS__REQ__H__
#define   __NOVEMBERIZING_X__REDIS__REQ__H__

#include <x/req.h>
#include <x/res.h>
#include <x/extension/redis/object.h>

struct xredisreq;
struct xredisres;

typedef struct xredisreq xredisreq;
typedef struct xredisres xredisres;

typedef xredisreq * (*xredisresdestructor)(xredisreq *);
typedef xint64 (*xredisserializer)(xredisreq *, xstream *);
typedef xredisres * (*xredisresgenerator)(xredisreq *);

struct xredisreq
{
    /** INHERITED REQ */
    xredisresdestructor rem;
    xtime               start;
    xtime               end;
    xredisserializer    serialize;
    xredisresgenerator  gen;
    /** ECHO REQ MEMBER */
    xredisobject *      object;
};

extern xredisreq * xredisreqnew(xredisobject * object);
extern xredisreq * xredisreqrem(xredisreq * req);

#endif // __NOVEMBERIZING_X__REDIS__REQ__H__
