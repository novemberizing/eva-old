#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "array.h"

static void xredisobjectval_rem(xval * val)
{
    if(val)
    {
        xredisobjectrem((xredisobject *) val->p);
    }
}

static xint64 xredisarrayserialize(xredisarray * o, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity)
{
    char str[256];
    xint32 n = snprintf(str, 256, "%lu", o->objects->size);
    str[n] = 0;

    *buffer = xstringcapacity_set(*buffer, size, capacity, 6 + n);

    printf("%ld\n", *size);

    (*buffer)[(*size)++] = o->type;
    memcpy(xaddressof((*buffer)[*size]), str, n);
    *size = *size + n;
    *((xuint32 *) xaddressof((*buffer)[*size])) = xredisprotocolend;
    *size = *size + 2;

    printf("%ld\n", *size);

    for(xlistnode * node = xlistbegin(o->objects); node != xnil; node = xlistnext(node))
    {
        xredisobject * child = (xredisobject *) node->value.p;
        if(child->serialize(child, buffer, pos, size, capacity) != xsuccess)
        {
            return xfail;
        }
    }

    return xsuccess;
}

extern xredisarray * xredisarraynew(void)
{
    xredisarray * o = (xredisarray *) calloc(sizeof(xredisarray), 1);

    o->rem = xredisarrayrem;
    o->serialize = xredisarrayserialize;
    o->type = xredisobjecttype_array;
    o->objects = xlistnew();

    return o;
}

extern xredisarray * xredisarrayrem(xredisarray * o)
{
    if(o)
    {
        o->objects = xlistrem(o->objects, xredisobjectval_rem);
        free(o);
    }
    return xnil;
}

extern void xredisarray_push(xredisarray * o, xredisobject * object)
{
    if(o)
    {
        xlistpushback(o->objects, xvalobject(object));
    }
}
