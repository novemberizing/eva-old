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


extern char * xredisinteger_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisinteger * o)
{
    xassertion(index == xnil || capacity == xnil, "");
    xassertion(*capacity < *index, "");

    char str[256];
    xint32 n = snprintf(str, 256, "%ld", o->value);
    str[n] = 0;

    s = xstringcapacity_set(s, index, capacity, 6 + n);

    s[(*index)++] = o->type;
    memcpy(xaddressof(s[*index]), str, n);
    *index = *index + n;
    *((xuint32 *) xaddressof(s[*index])) = xredisprotocolend;
    *index = *index + 2;

    return s;
}

extern xredisinteger * xredisinteger_deserialize(char * s, xuint64 * index, xuint64 limit)
{
    xassertion(xtrue, "");

    return xnil;
}
