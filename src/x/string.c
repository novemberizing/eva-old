#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "string.h"

extern char * xstringline_dup(char * output, const char * s, const char * next)
{
    xuint64 len = (next ? next - s : strlen(s));
    if(len > 1)
    {
        if(s[len - 1] == '\r')
        {
            len = len - 1;
        }
        len = len - 1;
    }
    return xstringdup(output, s, len);
}

extern char * xstringdup(char * output, const char * s, xuint64 n)
{
    if(s && n)
    {
        if(output == xnil)
        {
            output = (char *) malloc(n + 1);
        }
        return strncpy(output, s, n);
    }
    if(s == xnil)
    {
        if(output)
        {
            output[0] = 0;
        }
    }
    else
    {
        if(output == xnil)
        {
            output = (char *) malloc(1);
        }
        output[0] = 0;
        return output;
    }
    return output;
}

extern const char * xstringline_get(const char * s, xstringfunc callback)
{
    if(s != xnil)
    {
        char * ret = strchr(s, '\n');
        if(ret != xnil)
        {
            xint64 len = ret - s;
            if(len > 1)
            {
                if(s[len - 1] == '\r')
                {
                    if(callback != xnil)
                    {
                        callback(s, len - 1);
                    }
                    return ret + 1;
                }
            }
            if(callback != xnil)
            {
                callback(s, len);
            }
            return ret + 1;
        }
        else
        {
            if(callback != xnil)
            {
                callback(s, strlen(s));
            }
            return xnil;
        }
    }

    return s;
}

extern char * xstringcharcontinue_str(const char * s, const char * needle)
{
    char * ret = xnil;
    for(xuint64 i = 0; s[i] != 0; i++)
    {
        if(strchr(needle, s[i]))
        {
            ret = (char *) xaddressof(s[i]);
            if(s[i+1] == 0)
            {
                return xnil;
            }
        }
        else if(ret)
        {
            break;
        }
    }

    return ret;
}

extern char * xstringchar_str(const char * s, const char * needle)
{
    for(xuint64 i = 0; s[i] != 0; i++)
    {
        if(strchr(needle, s[i]))
        {
            return (char *) xaddressof(s[i]);
        }
    }

    return xnil;
}

extern char * xchrchr_str(int c, const char * needle){ return strchr(needle, c); }

extern const char * xstringword_get(const char * s, xstringfunc callback)
{
    if(s != xnil)
    {
        char * ret = xstringcharcontinue_str(s, "\r\n \t\v");
        if(ret != xnil)
        {
            xint64 len = ret - s;
            if(len > 1)
            {
                if(s[len - 1] == '\r')
                {
                    if(callback != xnil)
                    {
                        callback(s, len - 1);
                    }
                    return ret + 1;
                }
            }
            if(callback != xnil)
            {
                callback(s, len);
            }
            return ret + 1;
        }
        else
        {
            if(callback != xnil)
            {
                callback(s, strlen(s));
            }
            return xnil;
        }
    }

    return s;
}

extern char * xstringword_dup(char * output, const char * s, const char * next)
{
    xuint64 len = (next ? next - s : strlen(s));
    if(len > 0)
    {
        len = len - 1;
        while(len > 0 && xchrchr_str(s[len - 1], "\r\n \t\v")){ len = len - 1; }
    }

    return xstringdup(output, s, len);
}
