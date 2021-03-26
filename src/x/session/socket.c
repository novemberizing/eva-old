#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../thread.h"

#include "../descriptor/status.h"

#include "socket/event/process/tcp.h"

#include "../server.h"
#include "socket.h"

static xsessionsocketprocessor xsessionsocketprocessor_get(xint32 domain, xint32 type, xint32 protocol);

static xint64 xsessionsocketobserve(xsessionsocket * o, xuint32 event, xdescriptorparam param, xint64 result);
static void xsessionsocketeventon(xsessionsocketevent * event);

extern xsessionsocket * xsessionsocket_new(xint32 domain, xint32 type, xint32 protocol)
{
    xsessionsocket * o = (xsessionsocket *) calloc(sizeof(xsessionsocket), 1);

    o->rem = xsessionsocket_rem;
    o->subscription = xnil;
    o->sync = xnil;
    o->mask = xdescriptormask_void;
    o->status = xdescriptorstatus_void;
    o->handle.f = xinvalid;
    o->process = xsessionsocketprocessor_get(domain, type, protocol);
    o->check = xnil;
    o->on = xsessionsocketobserve;
    o->event.descriptor = o;
    o->event.on = xsessionsocketeventon;
    o->exception = xexception_void;
    o->domain = domain;
    o->type = type;
    o->protocol = protocol;
    o->stream.in = xnil;
    o->stream.out = xnil;
    o->session = xnil;

    return o;
}

extern xsessionsocket * xsessionsocket_rem(xsessionsocket * descriptor)
{
    if(descriptor)
    {
        xassertion(xtrue, "implement this");
    }
    return xnil;
}

extern xint64 xsessionsocketclear(xsessionsocket * o)
{
    xassertion(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse, "");

    o->stream.in = xstreamrem(o->stream.in);
    o->stream.out = xstreamrem(o->stream.out);

    return xsuccess;
}

static xint64 xsessionsocketobserve(xsessionsocket * o, xuint32 event, xdescriptorparam param, xint64 result)
{
    xsession * session = o->session;
    xserver * server = session->server;
    return server->session.on(session, event, param, result);
}

static void xsessionsocketeventon(xsessionsocketevent * event)
{
    event->descriptor->process(event->descriptor, xdescriptoreventtype_void);
}

static xsessionsocketprocessor xsessionsocketprocessor_get(xint32 domain, xint32 type, xint32 protocol)
{
    if(domain == AF_INET)
    {
        if(type == SOCK_STREAM)
        {
            if(protocol == IPPROTO_TCP)
            {
                return xsessionsocketprocess_tcp;
            }
        }
    }
    xassertion(xtrue, "");
    return xnil;
}
