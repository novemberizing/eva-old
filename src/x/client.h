#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/std.h>
#include <x/io.h>

struct xclient;

typedef struct xclient xclient;

typedef xint64 (*xclientsubscriber)(xclient *, xuint64, void *, xint64);

struct xclient
{
    xclientsocket * descriptor;
    xclientsubscriber on;
};

extern xclient * xclientnew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xclientsubscriber on, xuint64 size);

/**
 * 내부에서 사용하는 것과 외부에서 사용하는 것을 분리하자.
 * 내부에서는 오픈을 수행한다.
 */
extern xint64 xclientconnect(xclient * client);

#endif // __NOVEMBERIZING_X__CLIENT__H__
