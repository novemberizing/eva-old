#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "string.h"

static xuint64 page = 16;

extern char * xstringcpy(char * o, xuint64 * index, xuint64 * capacity, const char * source)
{
    return xstringncpy(o, index, capacity, source, source ? strlen(source) : 0);
}

extern char * xstringncpy(char * o, xuint64 * index, xuint64 * capacity, const char * source, xuint64 n)
{
    xassertion(index == xnil || capacity == xnil, "");
    xassertion(o == xnil && (*index > 0 || *capacity > 0), "");

    if(n > 0)
    {
        xuint64 reserved = ((*index + n + 1) / page + 1) * page;

        if(*capacity < reserved)
        {
            *capacity = reserved;

            if(o)
            {
                o = realloc(o, *capacity);
            }
            else
            {
                o = malloc(*capacity);
            }
        }

        memcpy(xaddressof(o[*index]), source, n);
        *index = *index + n;
        o[*index] = 0;
    }

    return o;
}