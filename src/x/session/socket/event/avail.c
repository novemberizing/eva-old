#include "avail.h"

extern xint32 xsessionsocketeventavail_rem(xsessionsocket * o)
{
    if(o->subscription == xnil || o->subscription->enginenode.engine == xnil)
    {
        return xtrue;
    }
    return xfalse;
}