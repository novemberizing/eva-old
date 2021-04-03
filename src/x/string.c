#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "string.h"

static xuint64 page = 16;

extern char * xstringdup(const char * source, xuint64 len)
{
    char * o = xnil;

    if(source && len)
    {
        if(len == -1)
        {
            o = malloc(1);
            o[0] = 0;            
        }
        else
        {
            o = malloc(len + 1);
            memcpy(o, source, len);
            o[len] = 0;
        }
    }
    else
    {
        o = malloc(1);
        o[0] = 0;
    }

    return o;
}

extern char * xstringcpy(char * o, xuint64 * index, xuint64 * capacity, const char * source)
{
    return xstringncpy(o, index, capacity, source, source ? strlen(source) : 0);
}

extern char * xstringncpy(char * o, xuint64 * index, xuint64 * capacity, const char * source, xuint64 n)
{
    xassertion(index == xnil || capacity == xnil, "");
    xassertion(o == xnil && (*index > 0 || *capacity > 0), "");

    if(n > 0)
    {
        xuint64 reserved = ((*index + n + 1) / page + 1) * page;

        if(*capacity < reserved)
        {
            *capacity = reserved;

            if(o)
            {
                o = realloc(o, *capacity);
            }
            else
            {
                o = malloc(*capacity);
            }
        }

        memcpy(xaddressof(o[*index]), source, n);
        *index = *index + n;
        o[*index] = 0;
    }

    return o;
}

extern char * xstringline_next(char * o, xuint64 * index, xuint64 limit)
{
    return xstringchr_next(o, index, limit, '\n');
}

extern char * xstringstr_next(char * o, xuint64 * index, xuint64 limit, const char * s)
{
    xassertion(s == xnil, "");
    xuint64 len = (s ? strlen(s) : 0);
    if(len > 0)
    {
        for(xuint64 i = 0; i + len <= limit; i++)
        {
            if(strncmp(xaddressof(o[i]), s, len) == 0)
            {
                if(index)
                {
                    *index = i + len;
                }

                return xaddressof(o[i + len]);
            }
        }
    }
    

    if(index)
    {
        *index = limit;
    }
    return xnil;
}

extern char * xstringchr_next(char * o, xuint64 * index, xuint64 limit, int c)
{
    for(xuint64 i = 0; i < limit; i++)
    {
        if(o[i] == c)
        {
            if(index)
            {
                *index = i + 1;
            }

            return xaddressof(o[i + 1]);
        }
    }

    if(index)
    {
        *index = limit;
    }
    return xnil;
}

extern xuint64 xstringwhitespace_split(char ** strings, const char * s, xuint64 limit)
{
    if(*strings == xnil)
    {
        *strings = malloc(limit + 1);
    }

    xuint64 count = 0;
    xuint64 index = 0;
    xuint64 prev = 0;
    
    for(xuint64 i = 0; i < limit; i++)
    {
        if(strchr("\r\t \n\v", s[i]))
        {
            (*strings)[index] = 0;
            if(index != prev)
            {
                prev = index;
                count = count + 1;
            }
            for(i = i + 1; i < limit; i++)
            {
                if(strchr("\r\t \n\v", s[i]))
                {
                    continue;
                }
                index = index + 1;
                (*strings)[index] = s[i];
                index = index + 1;
                break;
            }
            continue;
        }
        (*strings)[index] = s[i];
        index = index + 1;
    }
    (*strings)[index] = 0;
    if(index != prev)
    {
        count = count + 1;
    }

    return count;
}

extern char * xstringcapacity_set(char * s, xuint64 * index, xuint64 * capacity, xuint32 n)
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

extern xuint64 xstringtouint64(char * s, xuint64 limit)
{
    xassertion(s == xnil || limit == 0, "");
    xuint64 ret = 0;
    for(xuint64 i = 0; i < limit; i++)
    {
        char c = s[i];
        xassertion(c < 48 || c > 57, "");
        ret = ret * 10 + (c - 48);
    }

    return ret;
}