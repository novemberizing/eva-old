#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../thread.h"

#include "req.h"
#include "res.h"

static xint64 xredisreqserialize(xredisreq * req, xbyte ** buffer, xuint64 * position, xuint64 * size, xuint64 * capacity)
{
    xassertion(req == xnil || buffer == xnil || position == xnil || size == xnil || capacity == xnil, "%p, %p, %p, %p, %p", req, buffer, position, size, capacity);

    if(req->packet.size > 0)
    {
        *buffer = xstringcapacity_set(*buffer, size, capacity, req->packet.size);

        memcpy(xaddressof((*buffer)[*size]), req->packet.data, req->packet.size);

        *size = *size + req->packet.size;

        return req->packet.size;
    }

    xassertion(req->object == xnil, "");

    return req->object->serialize(req->object, buffer, position, size, capacity);
}

static xredisres * xredisresgen(xredisreq * req)
{
    return xredisresnew(req);
}

extern xredisreq * xredisreqnew(xredisobject * object)
{
    xredisreq * o = (xredisreq *) calloc(sizeof(xredisreq), 1);

    o->rem        = xredisreqrem;
    o->serialize  = xredisreqserialize;
    o->gen        = xredisresgen;
    o->object     = object;

    return o;
}

extern xredisreq * xredisreqrem(xredisreq * o)
{
    if(o)
    {
        if(o->object)
        {
            o->object = xreqrem(o->object);
        }
        if(o->packet.data)
        {
            free(o->packet.data);
        }
        free(o);   
    }
    return xnil;
}

static char * xredisreqformat(char * value, xuint64 * index, xuint64 * capacity, const char * format, xuint64 limit, va_list ap)
{
    xuint64 start = 0;
    register const char * c = format;
    register xuint64 i = 0;
//     printf(">> %c <<\n", *c);
    
    for(; i < limit; i++)
    {
        if(*(c + i) == '%')
        {
            xuint64 len = i - start;
            if(len > 0)
            {
                printf("==========================> copy\n");
                xuint64 n = 5 + len + xuint64decimalstringlen(len) + 4;
                value = xstringcapacity_set(value, index, capacity, n);
                xint32 size = snprintf(xaddressof(value[*index]), n, "$%lu  ", len);
                *index = *index + size;
                memcpy(xaddressof(value[*index]), xaddressof(format[start]), len);
                *index = *index + len;
                value[*index]= ' ';
                value[(*index) + 1]= ' ';
                // *((xuint32 *) xaddressof(value[*index])) = xredisprotocolend;
                *index = *index + 2;
                value[*index] = 0;
                start = i;
            }
            // find str
            for(i = i + 1; i < limit; i++)
            {
                // char * specifier = strchr("diouxXeEfFgGaAcspnm%", *(c + i));
                // if(specifier)
                // {
                //     if(specifier == 's')
                //     {

                //     }
                //     else
                //     {
                //         char form[256];
                //         strncpy(form, )
                //         char str[256];
                //         snprintf(str, 256, )
                //     }
                // }
            }
        }
    }

    if(start < i)
    {
        xuint64 len = i - start;
        if(len > 0)
        {
            xuint64 n = 5 + len + xuint64decimalstringlen(len) + 4;
            value = xstringcapacity_set(value, index, capacity, n);
            xint32 size = snprintf(xaddressof(value[*index]), n, "$%lu  ", len);
            *index = *index + size;
            memcpy(xaddressof(value[*index]), xaddressof(format[start]), len);
            *index = *index + len;
            value[*index]= ' ';
            value[(*index) + 1]= ' ';
            // *((xuint32 *) xaddressof(value[*index])) = xredisprotocolend;
            *index = *index + 2;
            value[*index] = 0;
            start = i;
        }
    }

    printf("=> %s\n", value);

    return value;
}

extern xredisreq * xredisreqfrom_format(const char * format, ...)
{
    xassertion(format == xnil, "");

    printf("%s\n", format);

    xredisreq * req = xredisreqnew(xnil);
    xuint64 formatlen = strlen(format);
    xstring packet = { 0, 0, xnil };

    packet.capacity = formatlen * 2;
    packet.value = malloc(packet.capacity);

    xuint64 start = 0;

    va_list ap;
    va_start(ap, format);

    for(xuint64 i = 0; i < formatlen; i++)
    {
        register xuint64 index = i;
        
        while(strchr(" \t\r\n", format[index]) != xnil) { index++; }

        xuint64 start = index;

        if(format[index] == '\"' || format[index] == '\'')
        {
            xassertion(formatlen <= index + 1, "");

            char * next = xnil;
            xuint64 n = 0;

            do {
                next = strchr(xaddressof(format[start + 1 + n]), format[start]);
                xassertion(next == xnil, "");
                n = next - xaddressof(format[start + 1 + n]) + 1;
            } while(*(next - 1) == '\\');

            xuint64 len = next - xaddressof(format[start + 1]);

            packet.value = xredisreqformat(packet.value, xaddressof(packet.size), xaddressof(packet.capacity), xaddressof(format[start + 1]), len, ap);

            // xredisformatv()
            // xstringset(xaddressof(sentence), xaddressof(format[start + 1]), len);
            // printf(">> %s <<\n", sentence.value);

            index = index + len + 1;
        }
        else
        {
            while(strchr(" \t\r\n", format[index]) == xnil && index < formatlen) { index++; }

            packet.value = xredisreqformat(packet.value, xaddressof(packet.size), xaddressof(packet.capacity), xaddressof(format[start]), index - start, ap);

            // xstringset(xaddressof(sentence), xaddressof(format[start]), index - start);
            // printf(">> %s <<\n", sentence.value);
        }

        i = index;
    }

    va_end(ap);

    req->packet.data = packet.value;
    //packet.value = xobjectrem(sentence.value);

    return req;
}
