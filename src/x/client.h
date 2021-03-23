#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/std.h>
#include <x/io.h>
#include <x/stream.h>

struct xclient;

typedef struct xclient xclient;

typedef xint64 (*xclientobserver)(xclient *, xuint32, xdescriptorparam, xint64);

typedef xclient * (*xclientfactory)(xclientpool *);
typedef void (*xclientreleaser)(xclient *);

struct xclient
{
    xclientsocket * descriptor;
    xclientobserver on;
};

extern xclient * xclientnew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xclientobserver on, xuint64 size);
extern xclient * xclientrem(xclient * client);

extern xint64 xclientconnect(xclient * client);

extern xint64 xclientread(xclient * client);
extern xint64 xclientwrite(xclient * client);
extern xint64 xclientclose(xclient * client);

#endif // __NOVEMBERIZING_X__CLIENT__H__
