#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT__H__

#include <x/std.h>

#define xredisobjecttype_string         '+'
#define xredisobjecttype_error          '-'
#define xredisobjecttype_integer        ':'
#define xredisobjecttype_bulk           '$'
#define xredisobjecttype_array          '*'

#define xredisprotocolend               0x00000A0Du

struct xredisobject;

typedef struct xredisobject xredisobject;

typedef xredisobject * (*xredisobjectdestructor)(xredisobject *);

struct xredisobject
{
    xredisobjectdestructor rem;
    xuint8 type;
};

extern xredisobject * xredisobjectrem(xredisobject * o);

extern char * xredisobject_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisobject * o);
extern xredisobject * xredisobject_deserialize(char * s, xuint64 * index, xuint64 limit);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT__H__
