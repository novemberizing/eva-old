#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "bulk.h"


// extern xredisbulk * xredisbulk_new(const char * s, xuint64 size)
// {
//     xredisbulk * o = (xredisbulk *) calloc(sizeof(xredisbulk), 1);

//     o->type  = xredisobjecttype_bulk;
//     o->rem   = xredisbulk_rem;
//     o->value = xstringdup(s, size);
//     o->size  = size;

//     return o;
// }

// extern xredisbulk * xredisbulk_rem(xredisbulk * o)
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


// extern char * xredisbulk_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisbulk * o)
// {
//     xassertion(index == xnil || capacity == xnil, "");
//     xassertion(*capacity < *index, "");

//     char str[256];
//     xint32 n = snprintf(str, 256, "%d", o->size);
//     str[n] = 0;

//     s = xstringcapacity_set(s, index, capacity, 10 + n);

//     s[(*index)++] = o->type;
//     memcpy(xaddressof(s[*index]), str, n);
//     *index = *index + n;
//     *((xuint32 *) xaddressof(s[*index])) = xredisprotocolend;
//     *index = *index + 2;

//     if(o->size > 0)
//     {
//         memcpy(xaddressof(s[*index]), o->value, o->size);
//         *index = *index + o->size;
//         *((xuint32 *) xaddressof(s[*index])) = xredisprotocolend;
//         *index = *index + 2;
//     }
//     else
//     {
//         *((xuint32 *) xaddressof(s[*index])) = xredisprotocolend;
//         *index = *index + 2;
//     }

//     return s;
// }

// extern xredisbulk * xredisbulk_deserialize(char * s, xuint64 * index, xuint64 limit)
// {
//     xassertion(xtrue, "");

//     return xnil;
// }
