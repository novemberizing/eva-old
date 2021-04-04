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

#include "../../serializable.h"

extern xint64 xredisobjectto_stream(xredisobject * o, xstream * stream)
{
    return xstreampush_serializable(stream, (xserializable *) o);
}

extern xredisobject * xredisobjectrem(xredisobject * o)
{
    return o ? o->rem(o) : xnil;
}

extern xint64 xredisobject_predict(xbyte * buffer, xuint64 position, xuint64 size)
{
    xassertion(size < position, "");

    if(position < size)
    {
        switch(buffer[position])
        {
            case xredisobjecttype_string:       return xredisstring_predict(buffer, position, size);
            case xredisobjecttype_error:        return xrediserror_predict(buffer, position, size);
            case xredisobjecttype_integer:      return xredisinteger_predict(buffer, position, size);
            case xredisobjecttype_bulk:         return xredisbulk_predict(buffer, position, size);
            case xredisobjecttype_array:        return xredisarray_predict(buffer, position, size);
            default: xassertion(xtrue, "");     return xfail;
        }
    }
    return 1;   // 타입을 체크해야 한다.
}

extern xint64 xredisobject_complete(xbyte * buffer, xuint64 position, xuint64 size)
{
    xassertion(size < position, "");

    if(position < size)
    {
        switch(buffer[position])
        {
            case xredisobjecttype_string:       return xredisstring_complete(buffer, position, size);
            case xredisobjecttype_error:        return xrediserror_complete(buffer, position, size);
            case xredisobjecttype_integer:      return xredisinteger_complete(buffer, position, size);
            case xredisobjecttype_bulk:         return xredisbulk_complete(buffer, position, size);
            case xredisobjecttype_array:        return xredisarray_complete(buffer, position, size);
            default: xassertion(xtrue, "");     return xfail;
        }
    }
    return 0;   // 비정상이다.
}

/**
 * 이 함수의 호출은 이미 데이터를 다 받았음을 의미한다.
 * 그래서 if(xredisobject_complete(buffer, position, size) != 0) 함수는 호출되면 안된다.
 */
extern xredisobject * xredisobject_deserialize(xbyte * buffer, xuint64 * position, xuint64 size)
{
    switch(buffer[*position])
    {
        case xredisobjecttype_string:       return (xredisobject *) xredisstring_deserialize(buffer, position, size);
        case xredisobjecttype_error:        return (xredisobject *) xrediserror_deserialize(buffer, position, size);
        case xredisobjecttype_integer:      return (xredisobject *) xredisinteger_deserialize(buffer, position, size);
        case xredisobjecttype_bulk:         return (xredisobject *) xredisbulk_deserialize(buffer, position, size);
        case xredisobjecttype_array:        return (xredisobject *) xredisarray_deserialize(buffer, position, size);
        default: xassertion(xtrue, "");     return xnil;
    }
//    xassertion(xtrue, "implement this");
}

extern void xredisobject_print(xredisobject * o)
{
    switch(o->type)
    {
        case xredisobjecttype_string:       xredisstring_print((xredisstring *) o); break;
        case xredisobjecttype_error:        xrediserror_print((xrediserror *) o); break;
        case xredisobjecttype_integer:      xredisinteger_print((xredisinteger *) o); break;
        case xredisobjecttype_bulk:         xredisbulk_print((xredisbulk *) o); break;
        case xredisobjecttype_array:        xredisarray_print((xredisarray *) o); break;
        default: xassertion(xtrue, "");     break;
    }
}
