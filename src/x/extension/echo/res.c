#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../thread.h"
#include "res.h"
#include "req.h"

static xint64 xechoresserialize(xechores * res, xbyte ** buffer, xuint64 * position, xuint64 * size, xuint64 * capacity)
{
    xassertion(res == xnil || buffer == xnil || position == xnil || size == xnil || capacity == xnil, "");

    *buffer = xstringcapacity_set(*buffer, size, capacity, res->size);

    if(res->size > 0)
    {
        memcpy(*buffer, res->value, res->size);
        *size = *size + res->size;
    }
    
    return res->size;
}

static xint64 xechoressizepredict(xechores * res, xbyte * buffer, xuint64 position, xuint64 size)
{
    if((res->status & xresponsestatus_complete) == xresponsestatus_void)
    {
        return res->req->size;
    }
    return 0;
}

static xint64 xechoresdeserialize(xechores * res, xbyte * buffer, xuint64 position, xuint64 size)
{
    if((res->status & xresponsestatus_complete) == xresponsestatus_void)
    {
        xassertion(size < position, "");

        xuint64 len = size - position;
        if(res->req->size <= len)
        {
            if(res->value)
            {
                free(res->value);
            }
            res->value = xobjectdup(xaddressof(buffer[position]), res->req->size);
            res->size  = res->req->size;
            res->status |= xresponsestatus_complete;
            res->end = xtimeget();

            return res->size;
        }
        // TODO: NEED MORE BYTES
        return 0;
    }
    return 0;
}

extern xechores * xechoresnew(xechoreq * req)
{
    xechores * o   = (xechores *) calloc(sizeof(xechores), 1);

    o->rem         = xechoresrem;
    o->serialize   = xechoresserialize;
    o->req         = req;
    o->predict     = xechoressizepredict;
    o->deserialize = xechoresdeserialize;

    return o;
}

extern xechores * xechoresrem(xechores * o)
{
    if(o)
    {
        if(o->value)
        {
            free(o->value);
        }
        if(o->req)
        {
            o->req = xreqrem(o->req);
        }
        free(o);
    }
    return xnil;
}
