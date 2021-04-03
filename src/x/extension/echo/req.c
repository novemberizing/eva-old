#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../thread.h"
#include "req.h"
#include "res.h"

static xint64 xechoreqserialize(xechoreq * req, xbyte ** buffer, xuint64 * position, xuint64 * size, xuint64 * capacity)
{
    xassertion(req == xnil || buffer == xnil || position == xnil || size == xnil || capacity == xnil, "");

    *buffer = xstringcapacity_set(*buffer, size, capacity, req->size);

    if(req->size > 0)
    {
        memcpy(*buffer, req->value, req->size);
        *size = *size + req->size;
    }
    
    return req->size;
}

static xechores * xechoresgen(xechoreq * req)
{
    return xechoresnew(req);
}

extern xechoreq * xechoreqnew(const char * s)
{
    xechoreq * o = (xechoreq *) calloc(sizeof(xechoreq), 1);

    o->rem       = xechoreqrem;
    o->serialize = xechoreqserialize;
    o->gen       = xechoresgen;
    o->size      = s ? strlen(s) : 0;
    o->value     = xstringdup(s, o->size);

    return o;
}

extern xechoreq * xechoreqrem(xechoreq * o)
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
