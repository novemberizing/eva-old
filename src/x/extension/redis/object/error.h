#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ERROR__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ERROR__H__

#include <x/extension/redis/object.h>

struct xrediserror;

typedef struct xrediserror xrediserror;

typedef xrediserror * (*xrediserrordestructor)(xrediserror *);
typedef xint64 (*xrediserrorserializer)(xrediserror *, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity);

struct xrediserror
{
    /** INHERITED SERIALIZABLE OBJECT */
    xrediserrordestructor rem;
    xrediserrorserializer serialize;
    /** INHERITED REDIS OBJECT MEMBER */
    xuint8                type;
    /** REDIS ERROR MEMBER */
    xuint64               size;
    char *                value;
};

extern xrediserror * xrediserrornew(const char * s);
extern xrediserror * xrediserrorrem(xrediserror * o);

extern xint64 xrediserror_predict(xbyte * buffer, xuint64 position, xuint64 size);
extern xint64 xrediserror_complete(xbyte * buffer, xuint64 position, xuint64 size);


#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_ERROR__H__
