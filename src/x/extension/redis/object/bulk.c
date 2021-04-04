#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "bulk.h"

static xint64 xredisbulkserialize(xredisbulk * o, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity)
{
    char str[256];
    xint32 n = snprintf(str, 256, "%d", o->size);
    str[n] = 0;

    *buffer = xstringcapacity_set(*buffer, size, capacity, 16 + n);

    (*buffer)[(*size)++] = o->type;
    memcpy(xaddressof((*buffer)[*size]), str, n);
    *size = *size + n;
    *((xuint32 *) xaddressof((*buffer)[*size])) = xredisprotocolend;
    *size = *size + 2;

    if(o->size > 0)
    {
        memcpy(xaddressof((*buffer)[*size]), o->value, o->size);
        *size = *size + o->size;
    }

    *((xuint32 *) xaddressof((*buffer)[*size])) = xredisprotocolend;
    *size = *size + 2;

    return xsuccess;
}

extern xredisbulk * xredisbulknew(const char * s, xint32 n)
{
    xredisbulk * o = (xredisbulk *) calloc(sizeof(xredisbulk), 1);

    o->rem       = xredisbulkrem;
    o->serialize = xredisbulkserialize;
    o->type      = xredisobjecttype_bulk;
    o->size      = n;
    o->value     = xobjectdup(s, n);

    return o;
}

extern xredisbulk * xredisbulkfrom_int64(xint64 value)
{
    char s[256];
    int n = snprintf(s, 256, "%ld", value);
    return xredisbulknew(s, n);
}

extern xredisbulk * xredisbulkrem(xredisbulk * o)
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

extern xint64 xredisbulk_predict(xbyte * buffer, xuint64 position, xuint64 size)
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
                xuint64 sizelen = index - position;
                xassertion(sizelen < 3, "");

                // 잘못된 프로토콜을 받으면 어떻게 해야 하는가?
                xuint64 size = xstringtouint64(xaddressof(buffer[position + 1]), sizelen - 3);

                xuint64 packetlen = size - position;

                return sizelen + size + 2 <= packetlen ? 0 : packetlen - (sizelen + size + 2);
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

    return 1;   // 타입을 받는다.
}

extern xint64 xredisbulk_complete(xbyte * buffer, xuint64 position, xuint64 size)
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
                xuint64 sizelen = index - position;
                xassertion(sizelen < 3, "");

                // 잘못된 프로토콜을 받으면 어떻게 해야 하는가?
                xuint64 size = xstringtouint64(xaddressof(buffer[position + 1]), sizelen - 3);

                xuint64 packetlen = size - position;

                return sizelen + size + 2 <= packetlen ? sizelen + size + 2 : 0;
            }
        }
    }

    return 0;
}

extern xredisbulk * xredisbulk_deserialize(xbyte * buffer, xuint64 * position, xuint64 size)
{
    xuint64 index = 0;
    char * next = xstringstr_next(xaddressof(buffer[*position]), xaddressof(index), size, "\r\n");

    xassertion(next == xnil, "");

    xredisbulk * o = (xredisbulk *) calloc(sizeof(xredisbulk), 1);

    o->rem       = xredisbulkrem;
    o->serialize = xredisbulkserialize;
    o->type      = xredisobjecttype_bulk;
    o->size      = xstringtoint64(xaddressof(buffer[*position + 1]), index - 3);
    o->value     = xstringdup(xaddressof(buffer[index]), o->size);

    *position = index + o->size + 2;

    return o;

}

extern void xredisbulk_print(xredisbulk * bulk)
{
    printf("%.*s\n", bulk->size, bulk->value);
}