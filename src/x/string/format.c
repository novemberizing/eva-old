#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"
#include "format.h"

static xuint64 page = 16;

const char * specifiers = "diouxXeEfFgGaAcspnm% ";

static char * xstringserialize_str(char * s, xuint64 * index, xuint64 * capacity, const char * format, va_list ap)
{
    char * str = va_arg(ap, char *);
    return xstringncpy(s, index, capacity, str ? str : "(nil)", str ? strlen(str) : 5);
}

static char * xstringserialize_simple(char * s, xuint64 * index, xuint64 * capacity, const char * format, va_list ap)
{
    char str[256];
    xuint64 n = vsnprintf(str, 256, format, ap);
    return xstringncpy(s, index, capacity, str, n);
}

extern char * xstringformatserialize(char * s, xuint64 * index, xuint64 * capacity, xint32 specifier, const char * format, va_list ap)
{
    switch(specifier)
    {
        case 'd': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'i': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'o': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'u': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'x': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'X': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'e': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'E': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'f': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'F': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'g': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'G': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'a': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'A': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'c': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'p': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'n': return xstringserialize_simple(s, index, capacity, format, ap);
        case 'm': return xstringserialize_simple(s, index, capacity, format, ap);
        case '%': return xstringncpy(s, index, capacity, "%", 1);
        case 's': return xstringserialize_str(s, index, capacity, format, ap);
        default: xassertion(xtrue, "");
    }
    return s;
}

extern char * xstringformat(char * s, xuint64 * index, xuint64 * capacity, xstringserializer serializer, const char * format, ...)
{
    va_list ap;
    va_start(ap, format);
    s = xstringformatv(s, index, capacity, serializer, format, ap);
    va_end(ap);
    return s;
}

extern char * xstringformatv(char * s, xuint64 * index, xuint64 * capacity, xstringserializer serializer, const char * format, va_list ap)
{
    xuint64 formatlen = format ? strlen(format) : 0;

    if(formatlen > 0)
    {
        xassertion(serializer == xnil, "");

        s = xstringcapacity_set(s, index, capacity, formatlen * 2);

        for(xuint64 i = 0; i < formatlen; i++)
        {
            char * found = strchr(xaddressof(format[i]), '%');
            char space = 0;
            if(found)
            {
                xuint64 n = found - xaddressof(format[i]);
                s = xstringncpy(s, index, capacity, xaddressof(format[i]), n);
                if(i + n + 1 < formatlen)
                {
                    xuint64 start = i + n;
                    for(i = start + 1; i < formatlen; i++)
                    {
                        if(strchr(specifiers, format[i]) != xnil)
                        {
                            if(format[i] == ' ')
                            {
                                if(space == 0)
                                {
                                    space = format[i];
                                }
                                else
                                {
                                    s = xstringncpy(s, index, capacity, xaddressof(format[start]), i - start + 1);
                                }
                            }
                            else
                            {
                                char form[16];
                                strncpy(form, xaddressof(format[start]), i - start + 1);
                                form[i - start + 1] = 0;
                                s = serializer(s, index, capacity, format[i], form, ap);
                            }
                            break;
                        }
                        else if(i + 1 == formatlen)
                        {
                            s = xstringncpy(s, index, capacity, xaddressof(format[start]), formatlen - start);
                            i = i + 1;
                            break;
                        }
                    }
                }
                else
                {
                    s = xstringncpy(s, index, capacity, xaddressof(format[i]), formatlen - i);
                    break;
                }
            }
            else
            {
                s = xstringncpy(s, index, capacity, xaddressof(format[i]), formatlen - i);
                break;
            }
        }
    }

    return s;
}

extern char * xsprintf(char * s, xuint64 * index, xuint64 * capacity, const char * format, ...)
{
    va_list ap;
    va_start(ap, format);
    s = xstringformatv(s, index, capacity, xstringformatserialize, format, ap);
    va_end(ap);
    return s;
}

extern char * xvsprintf(char * s, xuint64 * index, xuint64 * capacity, const char * format, va_list ap)
{
    return xstringformatv(s, index, capacity, xstringformatserialize, format, ap);
}
