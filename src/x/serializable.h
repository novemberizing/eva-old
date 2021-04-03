#ifndef   __NOVEMBERIZING_X__SERIALIZABLE__H__
#define   __NOVEMBERIZING_X__SERIALIZABLE__H__

#include <x/std.h>

struct xserializable;

typedef struct xserializable xserializable;

typedef xserializable * (*xserializabledestructor)(xserializable *);
typedef xint64 (*xserializableserializer)(xserializable *, xbyte **, xuint64 *, xuint64 *, xuint64 *);
typedef xserializable * (*xserializabledeserializer)(const xbyte *, xuint64, xuint64, xuint64 *);

struct xserializable
{
    xserializabledestructor rem;
    xserializableserializer serialize;
};

#endif // __NOVEMBERIZING_X__SERIALIZABLE__H__
