#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "server.h"
#include "server/socket.h"
#include "server/socket/event/avail.h"

#include "session/socket.h"
#include "session/socket/event/avail.h"

static xint64 xserverobserve(xserver * server, xuint32 event, xdescriptorparam param, xint64 result);

extern xsession * xsessionsimple_factory(xint32 domain, xint32 type, xint32 protocol);
extern void xsessionsimple_releaser(xsession * session);

extern xserver * xservernew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xsessionobserver on, xuint64 size)
{
    xassertion(on == xnil || size < sizeof(xserver), "");

    xserver * server        = (xserver *) calloc(size, 1);

    server->descriptor      = xserversocket_new(server, domain, type, protocol, addr, addrlen);
    server->on              = xserverobserve;

    server->session.on      = on;
    server->session.create  = xsessionsimple_factory;
    server->session.release = xsessionsimple_releaser;

    return server;
}

extern xserver * xserverrem(xserver * server)
{
    if(server)
    {
        xassertion(xserversocketeventavail_rem(server->descriptor) == xfalse, "");

        server->descriptor = xserversocket_rem(server->descriptor);

        free(server);
    }
    return xnil;
}

static xint64 xserverobserve(xserver * server, xuint32 event, xdescriptorparam param, xint64 result)
{
    return result;
}

extern xsession * xsessionsimple_factory(xint32 domain, xint32 type, xint32 protocol)
{
    xsession * session = calloc(sizeof(xsession), 1);
    session->descriptor = xsessionsocket_new(domain, type, protocol);
    return session;
}

extern void xsessionsimple_releaser(xsession * session)
{
    if(session)
    {
        xassertion(xsessionsocketeventavail_rem(session->descriptor) == xfalse, "");

        session->descriptor = session->descriptor->rem(session->descriptor);
        free(session);
    }
}