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

    // TODO: ENGINE NODE OR GENERATOR NODE ... 
    xeventengine * engine;
};

extern xclientpool * xclientpool_new(xclientfactory factory, xclientreleaser * releaser, int domain, int type, int protocol, void * addr, xuint32 addrlen, xclientpoolsubscriber on, xuint32 total);
extern xclientpool * xclientpool_rem(xclientpool * pool);

extern void xclientpool_client_bulk_create(xclientpool * pool, xuint64 total);
extern xclient * xclientpool_client_create(xclientpool * pool);
extern void xclientpool_client_release(xclientpool * pool, xclient * client);

extern xclient * xclientpool_pop(xclientpool * pool);
extern xclient * xclientpool_del(xclientpool * pool, xclient * client);

#endif // __NOVEMBERIZING_X__CLIENT_POOL__H__
