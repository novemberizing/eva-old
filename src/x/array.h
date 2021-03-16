#ifndef   __NOVEMBERIZING_X__ARRAY__H__
#define   __NOVEMBERIZING_X__ARRAY__H__

#include <x/std.h>

struct xarray;

typedef struct xarray xarray;

typedef xarray * (*xarraydestructor)(xarray *);

struct xarray
{
    xarraydestructor rem;
    xval *           values;
    xuint64          size;
    xsync *          sync;
};

extern xarray * xarraynew(xuint64 n);
extern xarray * xarrayrem(xarray * array);
extern void xarrayresize(xarray * array, xuint64 n);
extern xval xarrayget(xarray * array, xuint64 index);
extern xval xarrayset(xarray * array, xuint64 index, xval value);

#endif // __NOVEMBERIZING_X__ARRAY__H__
