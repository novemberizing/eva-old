#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "string.h"

extern xredisstring * xredisstring_new(const char * s)
{
    xredisstring * o = (xredisstring *) calloc(sizeof(xredisstring), 1);

    o->rem   = xredisstring_rem;
    o->type  = xredisobjecttype_string;
    o->size  = s != xnil ? strlen(s) : 0;
    o->value = xstringdup(s, o->size);

    return o;
}

extern xredisstring * xredisstring_rem(xredisstring * o)
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
