#include "req.h"
#include "res.h"

static xint64 xredisreqserialize(xredisreq * req, xbyte ** buffer, xuint64 * position, xuint64 * size, xuint64 * capacity)
{
    xassertion(req == xnil || buffer == xnil || position == xnil || size == xnil || capacity == xnil || req->object == xnil, "");

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

// static xint64 xredisserialize(xredisreq * req, xstream * stream)
// {
//     xassertion(xtrue, "implement this");

//     char * front       = xnil;
//     xuint64 * pos      = xnil;
//     xuint64 * size     = xnil;
//     xuint64 * capacity = xnil;

//     xstreambackmem_get(stream, xaddressof(front), xaddressof(pos), xaddressof(size), xaddressof(capacity));

//     front = xredisobject_serialize(front, size, capacity, req->object);

//     xstreambackmembuffer_set(stream, front);

//     return xfail;
// }

// static xredisres * xredisresgen(xredisreq * req)
// {
//     xassertion(xtrue, "implement this");
//     return xnil;
// }

// extern xredisreq * xredisreqnew(xredisobject * object)
// {
//     xredisreq * req = (xredisreq *) calloc(sizeof(xredisreq), 1);

//     req->rem       = xredisreqrem;
//     req->serialize = xredisserialize;
//     req->gen       = xredisresgen;
//     req->object    = object;

//     return req;
// }

// extern xredisreq * xredisreqrem(xredisreq * req)
// {
//     if(req)
//     {
//         if(req->object)
//         {
//             req->object = xredisobjectrem(req->object);
//         }
//         free(req);
//     }
//     return xnil;
// }