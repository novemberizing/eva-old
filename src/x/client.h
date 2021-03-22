#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/std.h>
#include <x/io.h>
#include <x/stream.h>

struct xclient;

typedef struct xclient xclient;

typedef xint64 (*xclientsubscriber)(xclient *, xuint32, void *, xint64);

typedef xclient * (*xclientfactory)(xclientpool *);
typedef void (*xclientreleaser)(xclient *);

struct xclient
{
    xclientsocket * descriptor;
    xclientsubscriber on;           // 사용자에게 오픈되지만, 

    xclient * prev;
    xclient * next;
    xclientpool * cntr;
};

extern xclient * xclientnew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xclientsubscriber on, xuint64 size);
extern xclient * xclientrem(xclient * client);

#endif // __NOVEMBERIZING_X__CLIENT__H__
