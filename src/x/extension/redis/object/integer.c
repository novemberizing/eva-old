#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "integer.h"

// typedef xredisinteger * (*xredisintegerdestructor)(xredisinteger *);


// struct xredisinteger
// {
//     /** INHERITED SERIALIZABLE OBJECT */
//     xredisintegerdestructor rem;
//     xredisintegerserializer serialize;
//     /** INHERITED REDIS OBJECT MEMBER */
//     xuint8                 type;
//     /** REDIS STRING MEMBER */
//     xint64 value;
// };

static xint64 xredisintegerserialize(xredisinteger * o, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity)
{
    char str[256];
    xint32 n = snprintf(str, 256, "%ld", o->value);
    str[n] = 0;

    *buffer = xstringcapacity_set(*buffer, size, capacity, 6 + n);

    (*buffer)[(*size)++] = o->type;
    memcpy(xaddressof((*buffer)[*size]), str, n);
    *size = *size + n;
    *((xuint32 *) xaddressof((*buffer)[*size])) = xredisprotocolend;

    *size = *size + 2;

    return xsuccess;
}

extern xredisinteger * xredisintegernew(xint64 value)
{
    xredisinteger * o = (xredisinteger *) calloc(sizeof(xredisinteger), 1);

    o->rem = xredisintegerrem;
    o->serialize = xredisintegerserialize;
    o->type = xredisobjecttype_integer;
    o->value = value;

    return o;
}

extern xredisinteger * xredisintegerrem(xredisinteger * o)
{
    if(o)
    {
        free(o);
    }
    return xnil;
}

extern xint64 xredisinteger_predict(xbyte * buffer, xuint64 position, xuint64 size)
{
    xassertion(size < position, "");

    if(position < size)
    {
        if(position + 3 <= size)
        {
            xuint64 index = position;
            char * next = xstringstr_next(xaddressof(buffer[position]), xaddressof(index), size, "\r\n");
            if(next)
            {
                return 0;
            }
        }

        if(position + 1 == size)
        {
            return 2;
        }
        else
        {
            if(buffer[size - 1] == '\r')
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }

    return 3;   // 타입은 1 바이트이다.
}

extern xint64 xredisinteger_complete(xbyte * buffer, xuint64 position, xuint64 size)
{
    xassertion(size < position, "");

    if(position < size)
    {
        if(position + 3 <= size)
        {
            xuint64 index = position;
            char * next = xstringstr_next(xaddressof(buffer[position]), xaddressof(index), size, "\r\n");
            if(next)
            {
                return index - position;
            }
        }
    }
    return 0;
}

extern xredisinteger * xredisinteger_deserialize(xbyte * buffer, xuint64 * position, xuint64 size)
{
    xuint64 index = 0;
    char * next = xstringstr_next(xaddressof(buffer[*position]), xaddressof(index), size, "\r\n");

    xassertion(next == xnil, "");

    xredisinteger * o = (xredisinteger *) calloc(sizeof(xredisinteger), 1);

    o->rem = xredisintegerrem;
    o->serialize = xredisintegerserialize;
    o->type = xredisobjecttype_integer;
    o->value = xstringtoint64(xaddressof(buffer[*position + 1]), index - 3);

    *position = index;

    return o;
}

extern void xredisinteger_print(xredisinteger * integer)
{
    printf("%ld\n", integer->value);
}
