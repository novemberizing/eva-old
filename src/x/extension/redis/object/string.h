#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_STRING__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_STRING__H__

#include <x/extension/redis/object.h>

struct xredisstring;

typedef struct xredisstring xredisstring;

typedef xredisstring * (*xredisstringdestructor)(xredisstring *);

struct xredisstring
{
    /** INHERITED REDIS OBJECT */
    xredisstringdestructor rem;
    xuint8 type;
    /** REDIS STRING MEMBER */
    xuint64 size;
    char * value;
};

extern xredisstring * xredisstring_new(const char * s);
extern xredisstring * xredisstring_rem(xredisstring * o);

extern char * xredisstring_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisstring * o);

extern xredisstring * xredisstring_deserialize(char * s, xuint64 * index, xuint64 limit);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_STRING__H__
