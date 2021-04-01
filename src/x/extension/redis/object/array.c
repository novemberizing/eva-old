#include <stdlib.h>
#include <string.h>

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