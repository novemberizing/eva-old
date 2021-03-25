#include <stdio.h>
#include <stdlib.h>

#include "../../../thread.h"
#include "avail.h"

extern xint32 xclientsocketeventavail_rem(xclientsocket * o)
{
    if(o->subscription)
    {
        xassertion(o->subscription, "");
    }

    return xtrue;
}

extern xint32 xclientsocketeventavail_open(xclientsocket * o)
{
    if(o->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception))
    {
        return xfalse;
    }
    if(o->status & xdescriptorstatus_connecting)
    {
        return xtrue;
    }
    return (o->status & xdescriptorstatus_connect) == xdescriptorstatus_void;
}