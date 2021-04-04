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

extern xredisreq * xredisreqgen_set(const char * key, const char * value)
{
    xassertion(key == xnil, "");

    xuint64 keylen = key ? strlen(key) : 0;

    if(keylen > 0)
    {
        xredisreq * req = xredisreqnew(xnil);
        xuint64 total = 13 + xuint64decimalstringlen(keylen) + 3 + keylen + 2;

        if(value)
        {
            xuint64 valuelen = value ? strlen(value) : 0;
            if(valuelen > 0)
            {
                total = total + xuint64decimalstringlen(valuelen) + 3 + valuelen + 2;                
                req->packet.data = malloc(total + 1);
                req->packet.size = snprintf(req->packet.data, total, "*3\r\n$3\r\nset\r\n$%lu\r\n%s\r\n$%lu\r\n%s\r\n",
                                                                     keylen,
                                                                     key,
                                                                     valuelen,
                                                                     value);
            }
            else
            {
                total = total + 6;
                req->packet.data = malloc(total + 1);
                req->packet.size = snprintf(req->packet.data, total, "*3\r\n$3\r\nset\r\n$%lu\r\n%s\r\n$0\r\n\r\n",
                                                                     keylen,
                                                                     key);
            }
        }
        else
        {
            total = total + 5;
            req->packet.data = malloc(total + 1);
            req->packet.size = snprintf(req->packet.data, total, "*3\r\n$3\r\nset\r\n$%lu\r\n%s\r\n$-1\r\n",
                                                                 keylen,
                                                                 key);
        }

        return req;
    }

    return xnil;
}
