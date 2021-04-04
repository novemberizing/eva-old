#ifndef   __NOVEMBERIZING_X__REDIS__REQ__H__
#define   __NOVEMBERIZING_X__REDIS__REQ__H__

#include <x/req.h>
#include <x/res.h>
#include <x/extension/redis/object.h>

struct xredisreq;
struct xredisres;

typedef struct xredisreq xredisreq;
typedef struct xredisres xredisres;

typedef xredisreq * (*xredisreqdestructor)(xredisreq *);
typedef xint64 (*xredisreqserializer)(xredisreq *, xbyte **, xuint64 *, xuint64 *, xuint64 *);
typedef xredisres * (*xredisresgenerator)(xredisreq *);

struct xredisreq
{
    /** INHERITED SERIALIZABLE */
    xredisreqdestructor     rem;
    xredisreqserializer     serialize;
    /** INHERITED REQ MEMBER */
    xtime                   start;
    xtime                   end;
    xredisresgenerator      gen;
    /** REDIS REQ MEMBER */
    xredisobject *          object;
    struct { xuint64 size;
             char * data; } packet;
};

extern xredisreq * xredisreqnew(xredisobject * object);
extern xredisreq * xredisreqrem(xredisreq * o);

extern xredisreq * xredisreqgen_set(const char * key, const char * value);

#endif // __NOVEMBERIZING_X__REDIS__REQ__H__
