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
    o->size  = s != xnil ? strlen(s) : 0;
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


extern char * xrediserror_serialize(char * s, xuint64 * index, xuint64 * capacity, xrediserror * o)
{
    xassertion(index == xnil || capacity == xnil, "");
    xassertion(*capacity < *index, "");

    s = xstringcapacity_set(s, index, capacity, 6 + o->size);

    s[(*index)++] = o->type;
    memcpy(xaddressof(s[*index]), o->value, o->size);
    *index = *index + o->size;
    *((xuint32 *) xaddressof(s[*index])) = xredisprotocolend;
    *index = *index + 2;
    
    return s;
}

extern xrediserror * xrediserror_deserialize(char * s, xuint64 * index, xuint64 limit)
{
    xassertion(xtrue, "");

    return xnil;
}
