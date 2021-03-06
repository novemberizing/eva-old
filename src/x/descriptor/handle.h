#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__HANDLE__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__HANDLE__H__

#include <x/std.h>

union xdescriptorhandle;

typedef union xdescriptorhandle xdescriptorhandle;

union xdescriptorhandle
{
    xint32 f;
    xhandle v;
};

#define xdescriptorhandle_invalid ((xdescriptorhandle) { .f = xinvalid })

#endif // __NOVEMBERIZING_X__DESCRIPTOR__HANDLE__H__
