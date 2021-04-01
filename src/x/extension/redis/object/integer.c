#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "integer.h"

extern xredisinteger * xredisinteger_new(xint64 value)
{
    xredisinteger * o = (xredisinteger *) calloc(sizeof(xredisinteger), 1);

    o->rem   = xredisinteger_rem;
    o->type  = xredisobjecttype_integer;
    o->value = value;
    return o;
}

extern xredisinteger * xredisinteger_rem(xredisinteger * o)
{
    if(o)
    {
        free(o);
    }
    return xnil;
}