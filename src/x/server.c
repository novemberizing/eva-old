#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "server.h"
#include "server/socket.h"
#include "session/socket.h"

extern xserver * xservernew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xsessionsubscriber on, xuint64 size)
{
    xlogfunction_start("%s(%d, %d, %d, %p, %u, %p, %lu)", __func__, domain, type, protocol, addr, addrlen, on, size);

    xassertion(on == xnil || size < sizeof(xserver), "");

    xserver * server        = (xserver *) calloc(size, 1);

    server->descriptor      = xserversocket_new(server, domain, type, protocol, addr, addrlen);
    server->on              = xserversubscriber_default;

    server->session.on      = on;

    server->session.create  = xsessionfactory_default;
    server->session.release = xsessionreleaser_default;

    xlogfunction_end("%s(...) => %p", __func__, server);
    return server;
}

extern xserver * xserverrem(xserver * server)
{
    xlogfunction_start("%s(%p)", __func__, server);

    if(server)
    {
        xassertion(server->session.alive.size > 0, "");
        xassertion(xserversocketcheck_rem(server->descriptor), "");

        server->descriptor = xserversocket_rem(server->descriptor);

        free(server);
    }

    xlogfunction_end("%s(...) => %p", __func__, server);
    return xnil;
}

extern xint64 xserversubscriber_default(xserver * server, xuint64 event, void * data, xint64 result)
{
    xlogfunction_start("%s(%p, %lu, %p, %lu)", __func__, server, event, data, result);
    xlogfunction_end("%s(...) => %ld", __func__, result);
    return result;
}

extern xsession * xsessionfactory_default(xint32 domain, xint32 type, xint32 protocol)
{
    xlogfunction_start("%s(%d, %d, %d)", __func__, domain, type, protocol);
    xsession * session = calloc(sizeof(xsession), 1);

    session->descriptor = xsessionsocket_new(domain, type, protocol);

    xlogfunction_end("%s(...) => %p", __func__, session);
    return session;
}

extern void xsessionreleaser_default(xsession * session)
{
    xlogfunction_start("%s(%p)", __func__, session);

    if(session)
    {
        session->descriptor = session->descriptor->rem(session->descriptor);
        free(session);
    }

    xlogfunction_end("%s(...)", __func__);
}
