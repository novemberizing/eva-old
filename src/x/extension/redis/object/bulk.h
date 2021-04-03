#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_BULK__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_BULK__H__

#include <x/extension/redis/object.h>

struct xredisbulk;

typedef struct xredisbulk xredisbulk;

typedef xredisbulk * (*xredisbulkdestructor)(xredisbulk *);
typedef xint64 (*xredisbulkserializer)(xredisbulk *, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity);

struct xredisbulk
{
    /** INHERITED SERIALIZABLE OBJECT */
    xredisbulkdestructor rem;
    xredisbulkserializer serialize;
    /** INHERITED REDIS OBJECT */
    xuint8               type;
    /** REDIS BULK MEMBER */
    xint32               size;
    char *               value;
};

extern xredisbulk * xredisbulknew(const char * s, xint32 n);
extern xredisbulk * xredisbulkrem(xredisbulk * o);

extern xint64 xredisbulk_predict(xbyte * buffer, xuint64 position, xuint64 size);
extern xint64 xredisbulk_complete(xbyte * buffer, xuint64 position, xuint64 size);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_OBJECT_BULK__H__
