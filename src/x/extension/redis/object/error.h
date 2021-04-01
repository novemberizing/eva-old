#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ERROR__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ERROR__H__

#include <x/extension/redis/object.h>

struct xrediserror;

typedef struct xrediserror xrediserror;

typedef xrediserror * (*xrediserrordestructor)(xrediserror *);

struct xrediserror
{
    /** INHERITED REDIS OBJECT */
    xrediserrordestructor rem;
    xuint8 type;
    /** REDIS STRING MEMBER */
    xuint64 size;
    char * value;
};

extern xrediserror * xrediserror_new(const char * s);
extern xrediserror * xrediserror_rem(xrediserror * o);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ERROR__H__
