#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../thread.h"

#include "req.h"
#include "res.h"

static xint64 xredisreqserialize(xredisreq * req, xbyte ** buffer, xuint64 * position, xuint64 * size, xuint64 * capacity)
{
    xassertion(req == xnil || buffer == xnil || position == xnil || size == xnil || capacity == xnil, "%p, %p, %p, %p, %p", req, buffer, position, size, capacity);

    if(req->packet.size > 0)
    {
        *buffer = xstringcapacity_set(*buffer, size, capacity, req->packet.size);

        memcpy(xaddressof((*buffer)[*size]), req->packet.data, req->packet.size);

        *size = *size + req->packet.size;

        return req->packet.size;
    }

    xassertion(req->object == xnil, "");

    return req->object->serialize(req->object, buffer, position, size, capacity);
}

static xredisres * xredisresgen(xredisreq * req)
{
    return xredisresnew(req);
}

extern xredisreq * xredisreqnew(xredisobject * object)
{
    xredisreq * o = (xredisreq *) calloc(sizeof(xredisreq), 1);

    o->rem        = xredisreqrem;
    o->serialize  = xredisreqserialize;
    o->gen        = xredisresgen;
    o->object     = object;

    return o;
}

extern xredisreq * xredisreqrem(xredisreq * o)
{
    if(o)
    {
        if(o->object)
        {
            o->object = xreqrem(o->object);
        }
        if(o->packet.data)
        {
            free(o->packet.data);
        }
        free(o);   
    }
    return xnil;
}

extern xredisreq * xredisreqfrom_format(const char * format, ...)
{
    xassertion(format == xnil, "");

    xredisreq * req = xredisreqnew(xnil);

    xuint64 capacity = 0;
    xuint64 index = 0;
    xuint64 formatlen = strlen(format);

    req->packet.data = xstringcapacity_set(req->packet.data, xaddressof(index), xaddressof(capacity), strlen(format));

    for(xuint64 i = 0; i < formatlen; i++)
    {
        if(strchr(" \r\n\t", format[i]))
        {

        }
    }
    // x::redis::req()
    // req->packet.data = malloc(capacity);

    return req;
}
