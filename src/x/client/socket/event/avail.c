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