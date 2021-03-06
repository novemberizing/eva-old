#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "server.h"
#include "server/socket.h"
#include "session/socket.h"

extern xserver * xservernew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xsessionsubscriber on, xuint64 size)
{
    xassertion(on == xnil || size < sizeof(xserver), "");

    xserver * server        = (xserver *) calloc(size, 1);

    server->descriptor      = xserversocket_new(server, domain, type, protocol, addr, addrlen);
    server->on              = xserversubscriber_default;

    server->session.on      = on;

    server->session.create  = xsessionfactory_default;
    server->session.release = xsessionreleaser_default;

    return server;
}

extern xserver * xserverrem(xserver * server)
{
    if(server)
    {
        xassertion(server->session.alive.size > 0, "");
        xassertion(xserversocketcheck_rem(server->descriptor), "");

        server->descriptor = xserversocket_rem(server->descriptor);

        free(server);
    }
    return xnil;
}

extern xint64 xserversubscriber_default(xserver * server, xuint64 event, void * data, xint64 result)
{
    return result;
}

extern xsession * xsessionfactory_default(xint32 domain, xint32 type, xint32 protocol)
{
    xsession * session = calloc(sizeof(xsession), 1);

    session->descriptor = xsessionsocket_new(domain, type, protocol);

    return session;
}

extern void xsessionreleaser_default(xsession * session)
{
    if(session)
    {
        session->descriptor = session->descriptor->rem(session->descriptor);
        free(session);
    }
}
