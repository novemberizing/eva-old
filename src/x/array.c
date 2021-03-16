#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread.h"
#include "array.h"

extern xarray * xarraynew(xuint64 n)
{
    xarray * array = (xarray *) calloc(sizeof(xarray), 1);

    array->values = (xval *) calloc(sizeof(xval), n);

    return array;
}

extern xarray * xarrayrem(xarray * array)
{
    if(array)
    {
        array->values = xobjectrem(array->values);
        free(array);
    }
    return xnil;
}

extern void xarrayresize(xarray * array, xuint64 n)
{
    if(array->values)
    {
        if(n > 0)
        {
            array->values = (xval *) realloc(array->values, n);
            if(array->size < n)
            {
                memset(xaddressof(array->values[array->size]), 0, n - array->size);
            }
        }
        else
        {
            array->values = xobjectrem(array->values);
        }
    }
    else
    {
        if(n > 0)
        {
            array->values = (xval *) calloc(sizeof(xval), n);
        }
    }
    array->size = n;
}

extern xval xarrayget(xarray * array, xuint64 index)
{
    xassertion(array->size <= index, "");
    return array->values[index];
}

extern xval xarrayset(xarray * array, xuint64 index, xval value)
{
    xassertion(array->size <= index, "");
    xval ret = array->values[index];
    array->values[index] = value;
    return ret;
}