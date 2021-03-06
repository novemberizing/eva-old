#ifndef   __NOVEMBERIZING_X__SERVER__H__
#define   __NOVEMBERIZING_X__SERVER__H__

#include <x/io.h>
#include <x/session/list.h>
#include <x/session.h>

struct xserver;
struct xserversocket;

typedef struct xserver xserver;
typedef struct xserversocket xserversocket;

typedef xint64 (*xserversubscriber)(xserver *, xuint64, void *, xint64);

// typedef xsession * (*xsessionfactory)(xint32 domain, xint32 type, xint32 protocol);
// typedef void (*xsessionreleaser)(xsession *);

struct xserver
{
    xserversocket *                      descriptor;
    xserversubscriber                    on;

    struct { xsessionlist alive;
             xsessionsubscriber on;
             xsessionfactory create;
             xsessionreleaser release; } session;
};

extern xserver * xservernew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xsessionsubscriber on, xuint64 size);
extern xserver * xserverrem(xserver * server);

extern xint64 xserversubscriber_default(xserver * server, xuint64 event, void * data, xint64 result);
extern xsession * xsessionfactory_default(xint32 domain, xint32 type, xint32 protocol);
extern void xsessionreleaser_default(xsession *);

#endif // __NOVEMBERIZING_X__SERVER__H__
