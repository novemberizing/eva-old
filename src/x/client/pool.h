#ifndef   __NOVEMBERIZING_X__CLIENT_POOL__H__
#define   __NOVEMBERIZING_X__CLIENT_POOL__H__

#include <x/client.h>

struct xclientpool;

typedef struct xclientpool xclientpool;

typedef xint64 (*xclientpoolsubscriber)(xclientpool *, xclient *, xuint64, void *, xint64);

/**
 * 
 */
struct xclientpool
{
    xclient * head;
    xclient * tail;
    xuint64 size;
    xsync * sync;

    xint32 domain;
    xint32 type;
    xint32 protocol;

    void * addr;
    xuint32 addrlen;

    xclientpoolsubscriber on;

    xclientfactory create;
    xclientreleaser release;
};

extern xclientpool * xclientpool_new(xclientfactory factory, xclientreleaser * releaser, xclientpoolsubscriber on, xuint32 total);
extern xclientpool * xclientpool_rem(xclientpool * pool);

#endif // __NOVEMBERIZING_X__CLIENT_POOL__H__
