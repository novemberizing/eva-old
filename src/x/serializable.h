#ifndef   __NOVEMBERIZING_X__SERIALIZABLE__H__
#define   __NOVEMBERIZING_X__SERIALIZABLE__H__

#include <x/std.h>

struct xserializable;

typedef struct xserializable xserializable;

typedef xserializable * (*xserializabledestructor)(xserializable *);
typedef xint64 (*xserializableserializer)(xserializable *, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity);


struct xserializable
{
    xserializabledestructor rem;
    xserializableserializer serialize;
};

#endif // __NOVEMBERIZING_X__SERIALIZABLE__H__
