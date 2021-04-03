#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_STRING__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_STRING__H__

#include <x/extension/redis/object.h>

struct xredisstring;

typedef struct xredisstring xredisstring;

typedef xredisstring * (*xredisstringdestructor)(xredisstring *);
typedef xint64 (*xredisstringserializer)(xredisstring *, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity);

struct xredisstring
{
    /** INHERITED SERIALIZABLE OBJECT */
    xredisstringdestructor rem;
    xredisstringserializer serialize;
    /** INHERITED REDIS OBJECT MEMBER */
    xuint8                 type;
    /** REDIS STRING MEMBER */
    xuint64                size;
    char *                 value;
};

extern xredisstring * xredisstringnew(const char * s);
extern xredisstring * xredisstringrem(xredisstring * o);

extern xint64 xredisstring_predict(xbyte * buffer, xuint64 position, xuint64 size);
extern xint64 xredisstring_complete(xbyte * buffer, xuint64 position, xuint64 size);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_STRING__H__
