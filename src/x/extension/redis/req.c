#include "req.h"

static xint64 xredisserialize(xredisreq * req, xstream * stream)
{
    xassertion(xtrue, "implement this");

    char * front       = xnil;
    xuint64 * pos      = xnil;
    xuint64 * size     = xnil;
    xuint64 * capacity = xnil;

    xstreambackmem_get(stream, xaddressof(front), xaddressof(pos), xaddressof(size), xaddressof(capacity));

    front = xredisobject_serialize(front, size, capacity, req->object);

    xstreambackmembuffer_set(stream, front);

    return xfail;
}

static xredisres * xredisresgen(xredisreq * req)
{
    xassertion(xtrue, "implement this");
    return xnil;
}

extern xredisreq * xredisreqnew(xredisobject * object)
{
    xredisreq * req = (xredisreq *) calloc(sizeof(xredisreq), 1);

    req->rem       = xredisreqrem;
    req->serialize = xredisserialize;
    req->gen       = xredisresgen;
    req->object    = object;

    return req;
}

extern xredisreq * xredisreqrem(xredisreq * req)
{
    if(req)
    {
        if(req->object)
        {
            req->object = xredisobjectrem(req->object);
        }
        free(req);
    }
    return xnil;
}