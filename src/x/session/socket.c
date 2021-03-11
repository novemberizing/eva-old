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
    xlogfunction_start("%s(%d, %d, %d)", __func__, domain, type, protocol);

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

    xlogfunction_end("%s(...) => %p", __func__, descriptor);
    return descriptor;
}

extern xsessionsocket * xsessionsocket_rem(xsessionsocket * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);
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

    xlogfunction_end("%s(...) => %p", __func__, xnil);
    return xnil;
}

extern xstream * xsessionsocketstreamin_get(xsessionsocket * descriptor)
{
    return descriptor->stream.in;
}

extern xstream * xsessionsocketstreamin_set(xsessionsocket * descriptor, xstream * stream)
{
    xlogfunction_start("%s(%p, %p)", __func__, descriptor, stream);
    xstream * prev = descriptor->stream.in;

    descriptor->stream.in = stream;

    xlogfunction_end("%s(...) => %p", __func__, prev);
    return prev;
}

extern void xsessionsocketstreamin_del(xsessionsocket * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    descriptor->stream.in = xstreamrem(descriptor->stream.in);

    xlogfunction_end("%s(...)", __func__);
}

extern xstream * xsessionsocketstreamout_get(xsessionsocket * descriptor)
{
    return descriptor->stream.out;
}

extern void xsessionsocketstreamout_del(xsessionsocket * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    descriptor->stream.out = xstreamrem(descriptor->stream.out);

    xlogfunction_end("%s(...)", __func__);
}

extern xstream * xsessionsocketstreamout_set(xsessionsocket * descriptor, xstream * stream)
{
    xlogfunction_start("%s(%p, %p)", __func__, descriptor, stream);

    xstream * prev = descriptor->stream.out;

    descriptor->stream.out = stream;

    xlogfunction_end("%s(...) => %p", __func__, prev);
    return prev;
}

static void xsessionsocketeventhandler_tcp(xsessionsocketevent * event)
{
    xlogfunction_start("%s(%p)", __func__, event);

    xdescriptorevent_processor_on((xdescriptor *) event->descriptor);

    xlogfunction_end("%s(...)", __func__);
}

static xint64 xsessionsocketsubscriber_tcp(xsessionsocket * descriptor, xuint32 event, void * data, xint64 result)
{
    xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, descriptor, event, data, result);

    xsession * session = descriptor->session;
    xserver * server = session->server;
    
    xint64 ret =  server->session.on(session, event, data, result);

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

static inline xint64 xsessionsocketprocessor_tcp_in(xsessionsocket * descriptor, void * data)
{
    xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

    if(xdescriptorcheck_open((xdescriptor *) descriptor))
    {
        xstreamadjust(descriptor->stream.in, xfalse);
        // TODO: 8192 CHANGE OPTIMIZED VALUE
        xstreamcapacity_set(descriptor->stream.in, xstreamcapacity_get(descriptor->stream.in) + 8192);

        xint64 n = xdescriptorread((xdescriptor *) descriptor, xstreamback(descriptor->stream.in), xstreamremain(descriptor->stream.in));
        if(n > 0)
        {
            xstreamsize_set(descriptor->stream.in, n + xstreamsize_get(descriptor->stream.in));

            xlogfunction_end("%s(...) => %ld", __func__,  n);
            return n;
        }

        xlogfunction_end("%s(...) => %ld", __func__,  n);
        return n;
    }

    xlogfunction_end("%s(...) => %ld", xfail);
    return xfail;
}

static inline xint64 xsessionsocketprocessor_tcp_out(xsessionsocket * descriptor, void * data)
{
    xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

    if(xdescriptorcheck_open((xdescriptor *) descriptor))
    {
        if(xstreamlen(descriptor->stream.out) > 0)
        {
            xint64 n = xdescriptorwrite((xdescriptor *) descriptor, xstreamfront(descriptor->stream.out), xstreamlen(descriptor->stream.out));
            if(n > 0)
            {
                xstreampos_set(descriptor->stream.out, xstreampos_get(descriptor->stream.out) + n);
            }
            xlogfunction_end("%s(...) => %ld", __func__, n);
            return n;
        }

        xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
        return xsuccess;
    }

    xlogfunction_end("%s(...) => %ld", __func__, xfail);
    return xfail;
}

static inline xint64 xsessionsocketprocessor_tcp_close(xsessionsocket * descriptor, void * data)
{
    xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

    descriptor->status |= xsessionsocketstatus_rem; // FORCE SHUTDOWN
    xsocketshutdown((xsocket *) descriptor, xsocketeventtype_offall);
    xint64 ret = xdescriptorclose((xdescriptor *) descriptor);

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

static inline xint64 xsessionsocketprocessor_tcp_exception(xsessionsocket * descriptor, void * data)
{
    xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

    descriptor->status |= xsessionsocketstatus_rem; // FORCE SHUTDOWN
    xsocketshutdown((xsocket *) descriptor, xsocketeventtype_offall);

    xint64 ret = xdescriptorclose((xdescriptor *) descriptor);

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

static xint64 xsessionsocketprocessor_tcp(xsessionsocket * descriptor, xuint32 event, void * data)
{
    xlogfunction_start("%s(%p, %u, %p)", __func__, descriptor, event, data);

    xint64 ret = xfail;
    switch(event)
    {
        case xsessionsocketeventtype_in:        ret = xsessionsocketprocessor_tcp_in(descriptor, data);         break;
        case xsessionsocketeventtype_out:       ret = xsessionsocketprocessor_tcp_out(descriptor, data);        break;
        case xsessionsocketeventtype_close:     ret = xsessionsocketprocessor_tcp_close(descriptor, data);      break;
        case xsessionsocketeventtype_exception: ret = xsessionsocketprocessor_tcp_exception(descriptor, data);  break;
        default:                                xassertion(xtrue, "implement this: 0x%08x", event);             break;
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

static xint32 xsessionsocketcheck_tcp(xsessionsocket * descriptor, xuint32 event)
{
    xlogfunction_start("%s(%p, %u)", __func__, descriptor, event);
    xassertion(xtrue, "implement this");

    xlogfunction_end("%s(...) => %d", __func__, xfail);
    return xfail;
}
