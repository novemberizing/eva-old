#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_INTEGER__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_INTEGER__H__

#include <x/extension/redis/object.h>

struct xredisinteger;

typedef struct xredisinteger xredisinteger;

typedef xredisinteger * (*xredisintegerdestructor)(xredisinteger *);
typedef xint64 (*xredisintegerserializer)(xredisinteger *, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity);

struct xredisinteger
{
    /** INHERITED SERIALIZABLE OBJECT */
    xredisintegerdestructor rem;
    xredisintegerserializer serialize;
    /** INHERITED REDIS OBJECT MEMBER */
    xuint8                  type;
    /** REDIS INTEGER MEMBER */
    xint64                  value;
};

extern xredisinteger * xredisintegernew(xint64 value);
extern xredisinteger * xredisintegerrem(xredisinteger * o);

extern xint64 xredisinteger_predict(xbyte * buffer, xuint64 position, xuint64 size);
extern xint64 xredisinteger_complete(xbyte * buffer, xuint64 position, xuint64 size);
extern xredisinteger * xredisinteger_deserialize(xbyte * buffer, xuint64 * position, xuint64 size);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_INTEGER__H__
