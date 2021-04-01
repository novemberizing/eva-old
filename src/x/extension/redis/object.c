#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../thread.h"
#include "../../string.h"

#include "object.h"
#include "object/string.h"
#include "object/error.h"
#include "object/integer.h"
#include "object/bulk.h"
#include "object/array.h"

static const xuint64 page = 64;

extern xredisobject * xredisobjectrem(xredisobject * o)
{
    return o ? o->rem(o) : xnil;
}

extern char * xredisobject_serialize(char * s, xuint64 * index, xuint64 * capacity, xredisobject * o)
{
    xassertion(index == xnil || capacity == xnil, "");
    xassertion(*capacity < *index, "");

    switch(o->type)
    {
        case xredisobjecttype_string:       return xredisstring_serialize(s, index, capacity, (xredisstring *) o);
        case xredisobjecttype_error:        return xrediserror_serialize(s, index, capacity, (xrediserror *) o);
        case xredisobjecttype_integer:      return xredisinteger_serialize(s, index, capacity, (xredisinteger *) o);
        case xredisobjecttype_bulk:         return xredisbulk_serialize(s, index, capacity, (xredisbulk *) o);
        case xredisobjecttype_array:        return xredisarray_serialize(s, index, capacity, (xredisarray *) o);
        default: xassertion(xtrue, "");     break;
    }

    return s;
}

extern xredisobject * xredisobject_deserialize(char * s, xuint64 * index, xuint64 limit)
{
    switch(s[*index])
    {
        case xredisobjecttype_string:       return (xredisobject *) xredisstring_deserialize(s, index, limit);
        case xredisobjecttype_error:        return (xredisobject *) xrediserror_deserialize(s, index, limit);
        case xredisobjecttype_integer:      return (xredisobject *) xredisinteger_deserialize(s, index, limit);
        case xredisobjecttype_bulk:         return (xredisobject *) xredisbulk_deserialize(s, index, limit);
        case xredisobjecttype_array:        return (xredisobject *) xredisarray_deserialize(s, index, limit);
        default: xassertion(xtrue, "");     break;
    }

    return xnil;
}
