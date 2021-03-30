#include "avail.h"

extern xint32 xserversocketeventavail_rem(xserversocket * o)
{
    if(o->subscription == xnil || o->subscription->enginenode.engine == xnil)
    {
        return xtrue;
    }
    return xfalse;
}

extern xint32 xserversocketeventavail_open(xserversocket * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse && (o->status & xdescriptorstatus_open))
    {
        return xtrue;
    }
    
    return xfalse;
}
