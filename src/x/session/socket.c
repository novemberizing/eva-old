#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"

#include "../descriptor/status.h"

#include "../server.h"
#include "socket.h"

static void xsessionsocketeventhandler_tcp(xsessionsocketevent * event);
static xint64 xsessionsocketsubscriber_tcp(xsessionsocket * descriptor, xuint32 event, void * data, xint64 result);
static xint64 xsessionsocketprocessor_tcp(xsessionsocket * descriptor, xuint32 event, void * data);
static xint32 xsessionsocketcheck_tcp(xsessionsocket * descriptor, xuint32 event);

extern xsessionsocket * xsessionsocket_new(xint32 domain, xint32 type, xint32 protocol)
{
    xsessionsocket * descriptor = (xsessionsocket * ) calloc(sizeof(xsessionsocket), 1);

    descriptor->rem = xsessionsocket_rem;
    descriptor->handle.f = xinvalid;
    descriptor->event.descriptor = descriptor;
    descriptor->event.on = xsessionsocketeventhandler_tcp;
    descriptor->process = xsessionsocketprocessor_tcp;
    descriptor->check = xsessionsocketcheck_tcp;
    descriptor->on = xsessionsocketsubscriber_tcp;
    descriptor->domain = domain;
    descriptor->type = type;
    descriptor->protocol = protocol;

    return descriptor;
}

extern xsessionsocket * xsessionsocket_rem(xsessionsocket * descriptor)
{
    if(descriptor)
    {
        // 세션 소켓의 경우 SUBSCRIPTION 이 존재할 수 있다.
        xassertion(descriptor->subscription, "");
        xassertion(descriptor->status != xdescriptorstatus_void && descriptor->status != xdescriptorstatus_rem, "0x%08x", descriptor->status);
        xassertion(descriptor->handle.f >= 0, "");
        xassertion(descriptor->event.queue || descriptor->event.prev || descriptor->event.next, "");

        descriptor->sync = xsyncrem(descriptor->sync);

        descriptor->stream.in = xstreamrem(descriptor->stream.in);
        descriptor->stream.out = xstreamrem(descriptor->stream.out);

        free(descriptor);
    }
    return xnil;
}

extern xstream * xsessionsocketstreamin_get(xsessionsocket * descriptor)
{
    return descriptor->stream.in;
}

extern xstream * xsessionsocketstreamin_set(xsessionsocket * descriptor, xstream * stream)
{
    xstream * prev = descriptor->stream.in;

    descriptor->stream.in = stream;

    return prev;
}

extern void xsessionsocketstreamin_del(xsessionsocket * descriptor)
{
    descriptor->stream.in = xstreamrem(descriptor->stream.in);
}

extern xstream * xsessionsocketstreamout_get(xsessionsocket * descriptor)
{
    return descriptor->stream.out;
}

extern void xsessionsocketstreamout_del(xsessionsocket * descriptor)
{
    descriptor->stream.out = xstreamrem(descriptor->stream.out);
}

extern xstream * xsessionsocketstreamout_set(xsessionsocket * descriptor, xstream * stream)
{
    xstream * prev = descriptor->stream.out;

    descriptor->stream.out = stream;

    return prev;
}

static void xsessionsocketeventhandler_tcp(xsessionsocketevent * event)
{
    xdescriptorevent_processor_on((xdescriptor *) event->descriptor);
}

static xint64 xsessionsocketsubscriber_tcp(xsessionsocket * descriptor, xuint32 event, void * data, xint64 result)
{
    xsession * session = descriptor->session;
    xserver * server = session->server;
    
    return server->session.on(session, event, data, result);
}

static inline xint64 xsessionsocketprocessor_tcp_in(xsessionsocket * descriptor, void * data)
{
    if(xdescriptorcheck_open((xdescriptor *) descriptor))
    {
        xstreamadjust(descriptor->stream.in, xfalse);
        // TODO: 8192 CHANGE OPTIMIZED VALUE
        xstreamcapacity_set(descriptor->stream.in, xstreamcapacity_get(descriptor->stream.in) + 8192);

        xint64 n = xdescriptorread((xdescriptor *) descriptor, xstreamback(descriptor->stream.in), xstreamremain(descriptor->stream.in));
        if(n > 0)
        {
            xstreamsize_set(descriptor->stream.in, n + xstreamsize_get(descriptor->stream.in));
            return n;
        }
        return n;
    }
    return xfail;
}

static inline xint64 xsessionsocketprocessor_tcp_out(xsessionsocket * descriptor, void * data)
{
    if(xdescriptorcheck_open((xdescriptor *) descriptor))
    {
        if(xstreamlen(descriptor->stream.out) > 0)
        {
            xint64 n = xdescriptorwrite((xdescriptor *) descriptor, xstreamfront(descriptor->stream.out), xstreamlen(descriptor->stream.out));
            if(n > 0)
            {
                xstreampos_set(descriptor->stream.out, xstreampos_get(descriptor->stream.out) + n);
            }
            return n;
        }
        return xsuccess;
    }
    return xfail;
}

static inline xint64 xsessionsocketprocessor_tcp_close(xsessionsocket * descriptor, void * data)
{
    descriptor->status |= xsessionsocketstatus_rem; // FORCE SHUTDOWN
    xsocketshutdown((xsocket *) descriptor, xsocketeventtype_offall);
    return xdescriptorclose((xdescriptor *) descriptor);
}

static inline xint64 xsessionsocketprocessor_tcp_exception(xsessionsocket * descriptor, void * data)
{
    descriptor->status |= xsessionsocketstatus_rem; // FORCE SHUTDOWN
    xsocketshutdown((xsocket *) descriptor, xsocketeventtype_offall);
    return xdescriptorclose((xdescriptor *) descriptor);
}

static xint64 xsessionsocketprocessor_tcp(xsessionsocket * descriptor, xuint32 event, void * data)
{
    switch(event)
    {
        case xsessionsocketeventtype_in:        return xsessionsocketprocessor_tcp_in(descriptor, data);
        case xsessionsocketeventtype_out:       return xsessionsocketprocessor_tcp_out(descriptor, data);
        case xsessionsocketeventtype_close:     return xsessionsocketprocessor_tcp_close(descriptor, data);
        case xsessionsocketeventtype_exception: return xsessionsocketprocessor_tcp_exception(descriptor, data);
    }
    xassertion(xtrue, "implement this: 0x%08x", event);

    return xfail;
}

static xint32 xsessionsocketcheck_tcp(xsessionsocket * descriptor, xuint32 event)
{
    xassertion(xtrue, "implement this");

    return xfail;
}
