#include "req.h"
#include "res.h"

static xint64 xredisreqserialize(xredisreq * req, xbyte ** buffer, xuint64 * position, xuint64 * size, xuint64 * capacity)
{
    xassertion(req == xnil || buffer == xnil || position == xnil || size == xnil || capacity == xnil || req->object == xnil, "");

    if(req->packet.size > 0)
    {
        *buffer = xstringcapacity_set(*buffer, size, capacity, req->packet.size);

        memcpy(xaddressof((*buffer)[*size]), req->packet.data, req->packet.size);

        *size = *size + req->packet.size;
    }

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
        free(o);   
    }
    return xnil;
}

extern xredisreq * xredisreq_set(const char * key, const char * value)
{
    xassertion(xtrue, "implement this");

    xuint64 keylen = key ? strlen(key) : 0;
    xuint64 valuelen = value ? strlen(value) : 0;

    xassertion(keylen == 0, "");

    xredisreq * req = xredisreqnew(xnil);
    xuint64 total = 0;

    char keylenstr[256];
    snprintf(keylenstr, 256, "%lu", keylen);

    char valuelenstr[256];

    if(valuelen > 0)
    {
        snprintf(valuelenstr, 256, "%lu", valuelen);
        req->packet.size = snprintf(req->packet.data, total, "*3\r\n$3\r\nset\r\n$%lu\r\n%s\r\n$%lu\r\n%s\r\n",
                                                             keylenstr,
                                                             key,
                                                             valuelenstr,
                                                             value);
    }
    else
    {
        if(value)
        {
            snprintf(valuelenstr, 256, "0");
        }
        else
        {
            snprintf(valuelenstr, 256, "-1");
        }
    }
    

    // req->packet.size = keylen

}
