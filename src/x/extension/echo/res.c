#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../thread.h"
#include "res.h"

static xuint64 xechorespredict(xechores * res, xuint64 len)
{
    if(res->status & xresponsestatus_complete)
    {
        return 0;
    }

    return res->req->size <= len ? 0 : (res->req->size - len);
}

static xint64 xechoresdeserialize(xechores * res, xstream * stream)
{

    if(res->req->size > 0)
    {
        if(res->req->size <= xstreamlen(stream))
        {
            if(res->data == xnil)
            {
                free(res->data);
            }
            res->data = malloc(res->req->size);
            res->size = res->req->size;
            memcpy(res->data, xstreamfront(stream), res->size);
            
            res->end = xtimeget();

            res->status |= xresponsestatus_complete;

            return res->req->size;
        }
    }
    else
    {
        res->status |= xresponsestatus_complete;
    }

    return 0;
}

extern xechores * xechoresnew(xechoreq * req)
{
    xechores * o  = (xechores *) calloc(sizeof(xechores), 1);

    o->rem        = xechoresrem;
    o->req        = req;
    o->deserialze = xechoresdeserialize;
    o->predict    = xechorespredict;

    return o;
}

extern xechores * xechoresrem(xechores * res)
{
    if(res)
    {
        if(res->req)
        {
            res->req = res->req->rem(res->req);
        }
        if(res->data)
        {
            free(res->data);
        }
        free(res);
    }
    return res;
}