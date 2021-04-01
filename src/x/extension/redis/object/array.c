#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "array.h"

static void xredisobjectarrayitem_rem(xval * value)
{
    xredisobjectrem((xredisobject *) value->p);
}

typedef void (*xvalfunc)(xval *);

extern xredisarray * xredisarray_new(void)
{
    xredisarray * o = (xredisarray *) calloc(sizeof(xredisarray), 1);

    o->rem = xredisarray_rem;
    o->type = xredisobjecttype_array;
    o->values = xlistnew();

    return o;
}

extern xredisarray * xredisarray_rem(xredisarray * o)
{
    if(o)
    {
        if(o->values)
        {
            o->values = xlistrem(o->values, xredisobjectarrayitem_rem);
        }
        free(o);
    }
    return xnil;
}

extern void xredisarray_push(xredisarray * array, xredisobject * o)
{
    xassertion(array == xnil, "");

    xlistpushback(array->values, xvalobject(o));
}

extern xuint64 xredisarray_size(xredisarray * array)
{
    xassertion(array == xnil || array->values == xnil, "");
    
    return array->values->size;
}

extern xlistnode * xredisarray_front(xredisarray * array)
{
    xassertion(array == xnil || array->values == xnil, "");

    return array->values->head;
}

extern xlistnode * xredisarray_next(xlistnode * node)
{
    xassertion(node == xnil, "");

    return node ? node->next : xnil;
}


extern char * xredisarray_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisarray * o)
{
    xassertion(index == xnil || capacity == xnil, "");
    xassertion(*capacity < *index, "");


    char str[256];
    xint32 n = snprintf(str, 256, "%lu", o->values->size);
    str[n] = 0;

    s = xstringcapacity_set(s, index, capacity, 6 + n);


    s[(*index)++] = o->type;
    memcpy(xaddressof(s[*index]), str, n);
    *index = *index + n;
    *((xuint32 *) xaddressof(s[*index])) = xredisprotocolend;
    *index = *index + 2;

    for(xlistnode * node = xredisarray_front(o); node != xnil; node = xredisarray_next(node))
    {
        s = xredisobject_serialize(s, index, capacity, (xredisobject *) node->value.p);
    }

    return s;
}

extern xredisarray * xredisarray_deserialize(char * s, xuint64 * index, xuint64 limit)
{
    xassertion(xtrue, "");

    return xnil;
}