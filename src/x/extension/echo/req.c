#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../thread.h"
#include "req.h"
#include "res.h"

static xechores * xechoresgen(xechoreq * req)
{
    return xechoresnew(req);
}

static xint64 xechoreqserialize(xechoreq * req, xstream * stream)
{
    xstreampush(stream, req->data, req->size);

    return req->size;
}

extern xechoreq * xechoreqnew(const char * s)
{
    xechoreq * req = (xechoreq *) calloc(sizeof(xechoreq), 1);

    req->size      = s ? strlen(s) : 0;
    req->data      = xobjectdup(s, req->size);
    req->serialize = xechoreqserialize;
    req->rem       = xechoreqrem;
    req->gen       = xechoresgen;

    return req;
}

extern xechoreq * xechoreqrem(xechoreq * o)
{
    if(o)
    {
        if(o->data)
        {
            free(o->data);
        }
        free(o);
    }

    return xnil;
}