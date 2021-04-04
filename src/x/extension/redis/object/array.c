#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../../thread.h"
#include "../../../string.h"
#include "array.h"

static void xredisobjectval_rem(xval * val)
{
    if(val)
    {
        xredisobjectrem((xredisobject *) val->p);
    }
}

static xint64 xredisarrayserialize(xredisarray * o, xbyte ** buffer, xuint64 * pos, xuint64 * size, xuint64 * capacity)
{
    char str[256];
    xint32 n = snprintf(str, 256, "%lu", o->objects->size);
    str[n] = 0;

    *buffer = xstringcapacity_set(*buffer, size, capacity, 6 + n);

    (*buffer)[(*size)++] = o->type;
    memcpy(xaddressof((*buffer)[*size]), str, n);
    *size = *size + n;
    *((xuint32 *) xaddressof((*buffer)[*size])) = xredisprotocolend;
    *size = *size + 2;

    for(xlistnode * node = xlistbegin(o->objects); node != xnil; node = xlistnext(node))
    {
        xredisobject * child = (xredisobject *) node->value.p;
        if(child->serialize(child, buffer, pos, size, capacity) != xsuccess)
        {
            return xfail;
        }
    }

    return xsuccess;
}

extern xredisarray * xredisarraynew(void)
{
    xredisarray * o = (xredisarray *) calloc(sizeof(xredisarray), 1);

    o->rem = xredisarrayrem;
    o->serialize = xredisarrayserialize;
    o->type = xredisobjecttype_array;
    o->objects = xlistnew();

    return o;
}

extern xredisarray * xredisarrayrem(xredisarray * o)
{
    if(o)
    {
        o->objects = xlistrem(o->objects, xredisobjectval_rem);
        free(o);
    }
    return xnil;
}

extern void xredisarray_push(xredisarray * o, xredisobject * object)
{
    if(o)
    {
        xlistpushback(o->objects, xvalobject(object));
    }
}

extern xint64 xredisarray_predict(xbyte * buffer, xuint64 position, xuint64 size)
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
                xuint64 totallen = 0;
                xuint64 arraylen = index - position;
                xassertion(arraylen < 3, "");

                xuint64 size = xstringtouint64(xaddressof(buffer[position + 1]), arraylen - 3);

                for(xuint64 i = 0; i < size; i++)
                {
                    xuint64 len = xredisobject_complete(buffer, index, size);
                    if(len == 0)
                    {
                        return xredisobject_predict(buffer, index, size);
                    }
                    index = index + len;
                    totallen = totallen + len;
                }

                return arraylen + totallen;
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

    return 1;   // 타입을 받는다.
}

extern xint64 xredisarray_complete(xbyte * buffer, xuint64 position, xuint64 size)
{
    xassertion(size < position, "");

    if(position + 3 <= size)
    {
        xuint64 index = position;
        char * next = xstringstr_next(xaddressof(buffer[position]), xaddressof(index), size, "\r\n");

        if(next)
        {
            xuint64 totallen = 0;
            xuint64 arraylen = index - position;
            xassertion(arraylen < 3, "");

            xuint64 size = xstringtouint64(xaddressof(buffer[position + 1]), arraylen - 3);

            for(xuint64 i = 0; i < size; i++)
            {
                xuint64 len = xredisobject_complete(buffer, index, size);
                if(len == 0)
                {
                    return 0;
                }
                index = index + len;
                totallen = totallen + len;
            }

            return arraylen + totallen;
        }
    }
    return 0;
}

extern xredisarray * xredisarray_deserialize(xbyte * buffer, xuint64 * position, xuint64 size)
{
    xuint64 index = 0;
    char * next = xstringstr_next(xaddressof(buffer[*position]), xaddressof(index), size, "\r\n");

    xassertion(next == xnil, "");

    xredisarray * o = (xredisarray *) calloc(sizeof(xredisarray), 1);

    o->rem = xredisarrayrem;
    o->serialize = xredisarrayserialize;
    o->type = xredisobjecttype_array;
    o->objects = xlistnew();

    xuint64 n = xstringtoint64(xaddressof(buffer[*position + 1]), index - 3);

    *position = index;

    for(xint64 i = 0; i < n; i++)
    {
        xlistpushback(o->objects, xvalobject(xredisobject_deserialize(buffer, position, size)));
    }

    return o;
}

extern void xredisarray_print(xredisarray * array)
{
    for(xlistnode * node = xlistbegin(array->objects); node != xnil; node = xlistnext(node))
    {
        xredisobject_print((xredisobject *) node->value.p);
    }
}