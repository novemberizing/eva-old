#include "res.h"

static xint64 xredisresserialize(xredisres * res, xbyte ** buffer, xuint64 * position, xuint64 * size, xuint64 * capacity)
{
    xassertion(res == xnil || buffer == xnil || position == xnil || size == xnil || capacity == xnil || res->object == xnil, "");

    return res->object->serialize(res->object, buffer, position, size, capacity);
}

static xint64 xredisressizepredict(xredisres * res, const xbyte * buffer, xuint64 position, xuint64 size)
{
    xint64 n = xredisobject_predict(buffer, position, size);
    if(n > 0)
    {
        return n;
    }
    return n;
}

/**
 * 이 함수가 호출되었다는 것은 이미 COMPLETED 상태란 의미이다.
 * 그렇게 로직을 만들어야 한다. 그래야 작은 작업이지만 두번 이상 수행하지 않는다.
 */
static xint64 xredisresdeserialize(xredisres * res, const xbyte * buffer, xuint64 position, xuint64 size)
{
    if(res->object == xnil)
    {
        xuint64 index = position;

        res->object = xredisobject_deserialize(buffer, xaddressof(index), size);

        xassertion(res->object == xnil, "");

        return res->object ? index - position : 0;
    }

    return 0;
}

extern xredisres * xredisresnew(xredisreq * req)
{
    xredisres * o = (xredisres *) calloc(sizeof(xredisres), 1);
    
    o->rem = xredisresrem;
    o->serialize = xredisresserialize;
    o->req = req;
    o->predict = xredisressizepredict;
    o->deserialize = xredisresdeserialize;

    return o;
}

extern xredisres * xredisresrem(xredisres * o)
{
    if(o)
    {
        if(o->req)
        {
            o->req = xredisreqrem(o->req);
        }
        if(o->object)
        {
            o->object = xredisobjectrem(o->object);
        }
        free(o);
    }
    return xnil;
}