#include "avail.h"

extern xint32 xserversocketeventavail_rem(xserversocket * o)
{
    if(o->subscription == xnil || o->subscription->enginenode.engine == xnil)
    {
        return xtrue;
    }
    return xfalse;
}