#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "bulk.h"

extern xredisbulk * xredisbulk_new(const char * s, xuint64 size)
{
    xredisbulk * o = (xredisbulk *) calloc(sizeof(xredisbulk), 1);

    o->type  = xredisobjecttype_bulk;
    o->rem   = xredisbulk_rem;
    o->value = xstringdup(s, size);
    o->size  = size;

    return o;
}

extern xredisbulk * xredisbulk_rem(xredisbulk * o)
{
    if(o)
    {
        if(o->value)
        {
            free(o->value);
        }
        free(o);
    }
    return xnil;
}