#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "error.h"

extern xrediserror * xrediserror_new(const char * s)
{
    xrediserror * o = (xrediserror *) calloc(sizeof(xrediserror), 1);

    o->rem   = xrediserror_rem;
    o->type  = xredisobjecttype_error;
    o->size  = s != xnil ? strlen(s) + 1 : 0;
    o->value = xstringdup(s, o->size);

    return o;
}

extern xrediserror * xrediserror_rem(xrediserror * o)
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