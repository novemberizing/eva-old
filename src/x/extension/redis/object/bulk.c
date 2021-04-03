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

    *buffer = xstringcapacity_set(*buffer, size, capacity, 10 + n);

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
