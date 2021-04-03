#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ARRAY__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ARRAY__H__

#include <x/list.h>
#include <x/extension/redis/object.h>

struct xredisarray;

typedef struct xredisarray xredisarray;

typedef xredisarray * (*xredisarraydestructor)(xredisarray *);
typedef xint64 (*xredisarrayserializer)(xredisarray *, xbyte **, xuint64 *, xuint64 *, xuint64 *);

struct xredisarray
{
    /** INHERITED SERIALIZABLE OBJECT */
    xredisarraydestructor rem;
    xredisarrayserializer serialize;
    /** INHERITED REDIS OBJECT */
    xuint8                type;
    /** REDIS BULK MEMBER */
    xlist *               objects;
};

extern xredisarray * xredisarraynew(void);
extern xredisarray * xredisarrayrem(xredisarray * o);
extern void xredisarray_push(xredisarray * o, xredisobject * object);

// struct xredisarray;

// typedef struct xredisarray xredisarray;

// typedef xredisarray * (*xredisarraydestructor)(xredisarray *);

// struct xredisarray
// {
//     /** INHERITED REDIS OBJECT */
//     xredisarraydestructor   rem;
//     xuint8                  type;
//     /** REDIS MEMBER */
//     xlist *                 values;
// };

// extern xredisarray * xredisarray_new(void);
// extern xredisarray * xredisarray_rem(xredisarray * o);
// extern void xredisarray_push(xredisarray * array, xredisobject * o);
// extern xuint64 xredisarray_size(xredisarray * array);
// extern xlistnode * xredisarray_front(xredisarray * array);
// extern xlistnode * xredisarray_next(xlistnode * node);

// extern char * xredisarray_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisarray * o);
// extern xredisarray * xredisarray_deserialize(char * s, xuint64 * index, xuint64 limit);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ARRAY__H__
