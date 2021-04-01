#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_BULK__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_BULK__H__

#include <x/extension/redis/object.h>

struct xredisbulk;

typedef struct xredisbulk xredisbulk;

typedef xredisbulk * (*xredisbulkdestructor)(xredisbulk *);

struct xredisbulk
{
    /** INHERITED REDIS OBJECT */
    xredisbulkdestructor    rem;
    xuint8                  type;
    /** REDIS MEMBER */
    xint32                  size;
    char *                  value;
};

extern xredisbulk * xredisbulk_new(const char * s, xuint64 size);
extern xredisbulk * xredisbulk_rem(xredisbulk * o);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_BULK__H__
