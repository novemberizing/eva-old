#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"
#include "format.h"

static xuint64 page = 16;

const char * specifiers = "diouxXeEfFgGaAcspnm% ";

static char * xstringcapacity_set(char * s, xuint64 * index, xuint64 * capacity, xuint32 n)
{
    xassertion(index == xnil || capacity == xnil, "");
    xassertion(s == xnil && (*index > 0 || *capacity > 0), "");

    if(n > 0)
    {
        xuint64 reserved = ((*index  + n) / page + 1) * page;
        if(*capacity < reserved)
        {
            *capacity = reserved;

            if(s)
            {
                s = realloc(s, *capacity);
            }
            else
            {
                s = malloc(*capacity);
            }
        }
    }

    return s;
}

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

static char * xstringserialize(char * s, xuint64 * index, xuint64 * capacity, xint32 specifier, const char * format, va_list ap)
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
    s = xstringformatv(s, index, capacity, xstringserialize, format, ap);
    va_end(ap);
    return s;
}

extern char * xvsprintf(char * s, xuint64 * index, xuint64 * capacity, const char * format, va_list ap)
{
    return xstringformatv(s, index, capacity, xstringserialize, format, ap);
}

// // stream ... string ...

// const char * specifiers = "diouxXeEfFgGaAcspnm% ";

// static xstring * xstringserialize_str(xstring * s, const char * form, const char * str)
// {
//     return xstringncat(s, str ? str : "(nil)", str ? strlen(str) : 5);
// }

// static xstring * xstringserialize_integer(xstring * s, const char * form, va_list ap)
// {
//     char str[128];
//     int n = vsnprintf(str, 128, form, ap);
//     return xstringncat(s, str, n);
// }

// static xstring * xstringserialize_percent(xstring * s, const char * form)
// {
//     return xstringncat(s, "%", 1);
// }

// static xstring * xstringserialize(xstring * s, int c, const char * form, va_list ap)
// {
//     switch(c)
//     {
//         case 's': return xstringserialize_str(s, form, va_arg(ap, const char *));
//         case 'd': return xstringserialize_integer(s, form, ap);
//         case 'i': return xstringserialize_integer(s, form, ap);
//         case '%': return xstringserialize_percent(s, form);
//         default:  xassertion(xtrue, "");
//     }
//     return s;
//     // 'd', 'i',
//     // 'o', 'u', 'x', 'X',
//     // 'e', 'E',
//     // 'f', 'F',
//     // 'g', 'G',
//     // 'a', 'A',
//     // 'c',
//     // 'C', 'S'.
//     // 'p', 'n',
//     // 'm', '%'

//     return s;
// }

// extern xstring * xsprintf(xstring * o, const char * format, ...)
// {
//     va_list ap;
//     va_start(ap, format);
//     xstring * ret = xstringformatv(xstringclr(o), xstringserialize, format, ap);
//     va_end(ap);
//     return ret;
// }

// extern xstring * xvsprtinf(xstring * o, const char * format, va_list ap)
// {
//     return xstringformatv(xstringclr(o), xstringserialize, format, ap);
// }

// extern xstring * xstringformat(xstring * o, xstringserializer serializer, const char * format, ...)
// {
//     va_list ap;
//     va_start(ap, format);
//     xstring * ret = xstringformatv(o, serializer, format, ap);
//     va_end(ap);
//     return ret;
// }

// extern xstring * xstringformatv(xstring * o, xstringserializer serializer, const char * format, va_list ap)
// {
//     xuint64 formatlen = format ? strlen(format) : 0;

//     if(formatlen > 0)
//     {
//         for(xuint64 i = 0; i < formatlen; i++)
//         {
//             char * found = strstr(xaddressof(format[i]), "%");
//             if(found)
//             {
//                 o = xstringncat(o, xaddressof(format[i]), found - xaddressof(format[i]));
//                 xuint64 n = found - xaddressof(format[i]);
//                 if(i + n + 1 < formatlen)
//                 {
//                     xuint64 start = i + n;
//                     for(i = i + n + 1; i < formatlen; i++)
//                     {
//                         if(strchr(specifiers, format[i]) != xnil)
//                         {
//                             if(format[i] == ' ')
//                             {
//                                 o = xstringncat(o, xaddressof(format[start]), formatlen - i);
//                                 xassertion(xtrue, "");
//                             }
//                             else
//                             {
//                                 char form[16];
//                                 strncpy(form, xaddressof(format[start]), i - start + 1);
//                                 form[i - start + 1] = 0;
//                                 o = serializer(o, format[i], form, ap);
//                             }
//                             break;
//                         }
//                         else if(i + 1 == formatlen)
//                         {
//                             o = xstringncat(o, xaddressof(format[start]), formatlen - start);
//                             xassertion(xtrue, "");
//                             i = i + 1;
//                             break;
//                         }
//                     }
//                 }
//                 else
//                 {
//                     xstringncat(o, "%", 1);
//                     i = i + n + 1;
//                 }
//                 continue;
//             }
//             o = xstringncat(o, xaddressof(format[i]), formatlen - i);
//             break;
//         }
//     }
    
//     return o;
// }