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

extern char * xredisstring_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisstring * o)
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

extern xredisstring * xredisstring_deserialize(char * s, xuint64 * index, xuint64 limit)
{
    xassertion(index == xnil, "");
    xassertion(s[*index] != xredisobjecttype_string, "");

    if(s[*index] == xredisobjecttype_string)
    {
        *index = *index + 1;
        xuint64 start = *index;
        char * next = xstringline_next(s, index, limit);
        if(start + 2 < *index)
        {
            xuint64 size = (*index - start) - 2;

            xredisstring * o = (xredisstring *) calloc(sizeof(xredisstring), 1);

            o->rem   = xredisstring_rem;
            o->type  = xredisobjecttype_string;
            o->size  = size;
            o->value = xstringdup(xaddressof(s[start]), o->size);

            return o;
        }
        else if(start + 2 == *index)
        {
            return xredisstring_new("");
        }
        else
        {
            xassertion(xtrue, "");
        }
        
    }

    return xnil;
}
