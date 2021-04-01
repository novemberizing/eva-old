#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_INTEGER__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_INTEGER__H__

#include <x/extension/redis/object.h>

struct xredisinteger;

typedef struct xredisinteger xredisinteger;

typedef xredisinteger * (*xredisintegerdestructor)(xredisinteger *);

struct xredisinteger
{
    /** INHERITED REDIS OBJECT */
    xredisintegerdestructor rem;
    xuint8 type;
    /** REDIS STRING MEMBER */
    xint64 value;
};

extern xredisinteger * xredisinteger_new(xint64 value);
extern xredisinteger * xredisinteger_rem(xredisinteger * o);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_INTEGER__H__
