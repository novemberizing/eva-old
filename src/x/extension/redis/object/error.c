#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "error.h"

static xint64 xrediserrorserialize(xrediserror * o, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity)
{
    xassertion(buffer == xnil || pos == xnil || size == xnil || capacity == xnil || o == xnil, "");

    *buffer = xstringcapacity_set(*buffer, size, capacity, 6 + o->size);

    (*buffer)[(*size)++] = o->type;
    memcpy(xaddressof((*buffer)[*size]), o->value, o->size);
    *size = *size + o->size;

    *((xuint32 *) xaddressof((*buffer)[*size])) = xredisprotocolend;

    *size = *size + 2;

    return xsuccess;
}

extern xrediserror * xrediserrornew(const char * s)
{
    xrediserror * o = (xrediserror *) calloc(sizeof(xrediserror), 1);

    o->rem       = xrediserrorrem;
    o->serialize = xrediserrorserialize;
    o->type      = xredisobjecttype_error;
    o->size      = s ? strlen(s) : 0;
    o->value     = xstringdup(s, o->size);

    return o;
}

extern xrediserror * xrediserrorrem(xrediserror * o)
{
    if(o)
    {
        if(o->value)
        {
            free(o->value);
        }
        free(o);
    }
    return xnil;
}

extern xint64 xrediserror_predict(xbyte * buffer, xuint64 position, xuint64 size)
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

extern xint64 xrediserror_complete(xbyte * buffer, xuint64 position, xuint64 size)
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

extern xrediserror * xrediserror_deserialize(xbyte * buffer, xuint64 * position, xuint64 size)
{
    xuint64 index = 0;
    char * next = xstringstr_next(xaddressof(buffer[*position]), xaddressof(index), size, "\r\n");

    xassertion(next == xnil, "");

    xrediserror * o = (xrediserror *) calloc(sizeof(xrediserror), 1);

    o->rem       = xrediserrorrem;
    o->serialize = xrediserrorserialize;
    o->type      = xredisobjecttype_error;
    o->size      = index - 3;
    o->value     = xstringdup(xaddressof(buffer[*position + 1]), o->size);

    *position = index;

    return o;
}

extern void xrediserror_print(xrediserror * error)  // 디버
{
    printf("%s\n", error->value);
}