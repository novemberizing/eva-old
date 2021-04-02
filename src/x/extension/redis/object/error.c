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
