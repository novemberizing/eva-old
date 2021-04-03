#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT__H__

#include <x/std.h>
#include <x/stream.h>

#define xredisobjecttype_string         '+'
#define xredisobjecttype_error          '-'
#define xredisobjecttype_integer        ':'
#define xredisobjecttype_bulk           '$'
#define xredisobjecttype_array          '*'

#define xredisprotocolend               0x00000A0Du

struct xredisobject;

typedef struct xredisobject xredisobject;

typedef xredisobject * (*xredisobjectdestructor)(xredisobject *);
typedef xint64 (*xredisobjectserializer)(xredisobject *, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity);

struct xredisobject
{
    /** INHERITED SERIALIZABLE OBJECT */
    xredisobjectdestructor rem;
    xredisobjectserializer serialize;
    /** REDIS OBJECT MEMBER */
    xuint8                 type;
};

extern xredisobject * xredisobjectrem(xredisobject * o);

extern xint64 xredisobjectto_stream(xredisobject * o, xstream * stream);

extern xint64 xredisobject_predict(xbyte * buffer, xuint64 position, xuint64 size);
extern xint64 xredisobject_complete(xbyte * buffer, xuint64 position, xuint64 size);

extern xredisobject * xredisresdeserialize(const xbyte * buffer, xuint64 position, xuint64 size);

// static xint64 xredisressizepredict(xredisres * res, const xbyte * buffer, xuint64 position, xuint64 size);
// static xint64 xredisresdeserialize(xredisres * res, const xbyte * buffer, xuint64 position, xuint64 size);

#include <x/extension/redis/object/string.h>
#include <x/extension/redis/object/error.h>
#include <x/extension/redis/object/integer.h>
#include <x/extension/redis/object/bulk.h>
#include <x/extension/redis/object/array.h>

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT__H__
