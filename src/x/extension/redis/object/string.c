#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "string.h"

static xint64 xredisstringserialize(xredisstring * o, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity)
{
    xassertion(buffer == xnil || pos == xnil || size == xnil || capacity == xnil || o == xnil, "");

    *buffer = xstringcapacity_set(*buffer, size, capacity, 6 + o->size);

    (*buffer)[(*size)++] = o->type;
    memcpy(xaddressof((*buffer)[*size]), o->value, o->size);
    *size = *size + o->size;

    *((xuint32 *) xaddressof((*buffer)[*size])) = xredisprotocolend;

    *size = *size + 2;

    return xsuccess;
}

extern xredisstring * xredisstringnew(const char * s)
{
    xredisstring * o = (xredisstring *) calloc(sizeof(xredisstring), 1);

    o->rem       = xredisstringrem;
    o->serialize = xredisstringserialize;
    o->type      = xredisobjecttype_string;
    o->size      = s ? strlen(s) : 0;
    o->value     = xstringdup(s, o->size);

    return o;
}

extern xredisstring * xredisstringrem(xredisstring * o)
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

extern xint64 xredisstring_predict(xbyte * buffer, xuint64 position, xuint64 size)
{
    xassertion(size < position, "");

    if(position < size)
    {
        if(position + 3 <= size)
        {
            xuint64 index = position;
            char * next = xstringstr_next(xaddressof(buffer[position]), xaddressof(index), size, "\r\n");
            if(next)
            {
                return 0;
            }
        }

        if(position + 1 == size)
        {
            return 2;
        }
        else
        {
            if(buffer[size - 1] == '\r')
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }

    return 3;   // 타입은 1 바이트이다.
}

extern xint64 xredisstring_complete(xbyte * buffer, xuint64 position, xuint64 size)
{
    xassertion(size < position, "");

    if(position < size)
    {
        if(position + 3 <= size)
        {
            xuint64 index = position;
            char * next = xstringstr_next(xaddressof(buffer[position]), xaddressof(index), size, "\r\n");
            if(next)
            {
                return index - position;
            }
        }
    }
    return 0;
}



// extern xredisstring * xredisstring_new(const char * s)
// {
//     xredisstring * o = (xredisstring *) calloc(sizeof(xredisstring), 1);

//     o->rem   = xredisstring_rem;
//     o->type  = xredisobjecttype_string;
//     o->size  = s != xnil ? strlen(s) : 0;
//     o->value = xstringdup(s, o->size);

//     return o;
// }

// extern xredisstring * xredisstring_rem(xredisstring * o)
// {
//     if(o)
//     {
//         if(o->value)
//         {
//             free(o->value);
//         }

//         free(o);
//     }

//     return xnil;
// }

// extern char * xredisstring_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisstring * o)
// {
//     xassertion(index == xnil || capacity == xnil, "");
//     xassertion(*capacity < *index, "");

//     s = xstringcapacity_set(s, index, capacity, 6 + o->size);

//     s[(*index)++] = o->type;
//     memcpy(xaddressof(s[*index]), o->value, o->size);
//     *index = *index + o->size;
//     *((xuint32 *) xaddressof(s[*index])) = xredisprotocolend;
//     *index = *index + 2;
    
//     return s;
// }

// extern xredisstring * xredisstring_deserialize(char * s, xuint64 * index, xuint64 limit)
// {
//     xassertion(index == xnil, "");
//     xassertion(s[*index] != xredisobjecttype_string, "");

//     if(s[*index] == xredisobjecttype_string)
//     {
//         *index = *index + 1;
//         xuint64 start = *index;
//         char * next = xstringline_next(s, index, limit);
//         if(start + 2 < *index)
//         {
//             xuint64 size = (*index - start) - 2;

//             xredisstring * o = (xredisstring *) calloc(sizeof(xredisstring), 1);

//             o->rem   = xredisstring_rem;
//             o->type  = xredisobjecttype_string;
//             o->size  = size;
//             o->value = xstringdup(xaddressof(s[start]), o->size);

//             return o;
//         }
//         else if(start + 2 == *index)
//         {
//             return xredisstring_new("");
//         }
//         else
//         {
//             xassertion(xtrue, "");
//         }
        
//     }

//     return xnil;
// }
