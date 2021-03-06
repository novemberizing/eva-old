#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/io.h>


struct xclient;

typedef struct xclient xclient;

typedef xint64 (*xclientsubscriber)(xclient *, xuint64, void *, xint64);

struct xclient
{
    xsocket * descriptor;
    xclientsubscriber on;
};

#endif // __NOVEMBERIZING_X__CLIENT__H__
