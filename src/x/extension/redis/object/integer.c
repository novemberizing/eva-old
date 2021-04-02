#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "integer.h"

// typedef xredisinteger * (*xredisintegerdestructor)(xredisinteger *);


// struct xredisinteger
// {
//     /** INHERITED SERIALIZABLE OBJECT */
//     xredisintegerdestructor rem;
//     xredisintegerserializer serialize;
//     /** INHERITED REDIS OBJECT MEMBER */
//     xuint8                 type;
//     /** REDIS STRING MEMBER */
//     xint64 value;
// };

static xint64 xredisintegerserialize(xredisinteger * o, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity)
{
    char str[256];
    xint32 n = snprintf(str, 256, "%ld", o->value);
    str[n] = 0;

    *buffer = xstringcapacity_set(*buffer, size, capacity, 6 + n);

    (*buffer)[(*size)++] = o->type;
    memcpy(xaddressof((*buffer)[*size]), str, n);
    *size = *size + n;
    *((xuint32 *) xaddressof((*buffer)[*size])) = xredisprotocolend;

    *size = *size + 2;

    return xsuccess;
}

extern xredisinteger * xredisintegernew(xint64 value)
{
    xredisinteger * o = (xredisinteger *) calloc(sizeof(xredisinteger), 1);

    o->rem = xredisintegerrem;
    o->serialize = xredisintegerserialize;
    o->type = xredisobjecttype_integer;
    o->value = value;

    return o;
}

extern xredisinteger * xredisintegerrem(xredisinteger * o)
{
    if(o)
    {
        free(o);
    }
    return xnil;
}


// extern xredisinteger * xredisinteger_new(xint64 value)
// {
//     xredisinteger * o = (xredisinteger *) calloc(sizeof(xredisinteger), 1);

//     o->rem   = xredisinteger_rem;
//     o->type  = xredisobjecttype_integer;
//     o->value = value;
//     return o;
// }

// extern xredisinteger * xredisinteger_rem(xredisinteger * o)
// {
//     if(o)
//     {
//         free(o);
//     }
//     return xnil;
// }


// extern char * xredisinteger_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisinteger * o)
// {
//     xassertion(index == xnil || capacity == xnil, "");
//     xassertion(*capacity < *index, "");

//     char str[256];
//     xint32 n = snprintf(str, 256, "%ld", o->value);
//     str[n] = 0;

//     s = xstringcapacity_set(s, index, capacity, 6 + n);

//     s[(*index)++] = o->type;
//     memcpy(xaddressof(s[*index]), str, n);
//     *index = *index + n;
//     *((xuint32 *) xaddressof(s[*index])) = xredisprotocolend;
//     *index = *index + 2;

//     return s;
// }

// extern xredisinteger * xredisinteger_deserialize(char * s, xuint64 * index, xuint64 limit)
// {
//     xassertion(xtrue, "");

//     return xnil;
// }
