#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ARRAY__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ARRAY__H__

#include <x/list.h>
#include <x/extension/redis/object.h>

struct xredisarray;

typedef struct xredisarray xredisarray;

typedef xredisarray * (*xredisarraydestructor)(xredisarray *);

struct xredisarray
{
    /** INHERITED REDIS OBJECT */
    xredisarraydestructor   rem;
    xuint8                  type;
    /** REDIS MEMBER */
    xlist *                 values;
};

extern xredisarray * xredisarray_new(void);
extern xredisarray * xredisarray_rem(xredisarray * o);
extern void xredisarray_push(xredisarray * array, xredisobject * o);
extern xuint64 xredisarray_size(xredisarray * array);
extern xlistnode * xredisarray_front(xredisarray * array);
extern xlistnode * xredisarray_next(xlistnode * node);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ARRAY__H__
