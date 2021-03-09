#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <netinet/in.h>

#include "../thread.h"

#include "socket.h"

#include "../socket/status.h"

static xint64 xclientsocketprocessor_tcp(xclientsocket * o, xuint32 event, void * parameter);
static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * parameter, xint64 result);
static xint32 xclientsocketcheck_tcp(xclientsocket * o, xuint32 event);
static void xclientsocketeventhandler_tcp(xclientsocketevent * event);

extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xclientsocket * o = (xclientsocket *) calloc(sizeof(xclientsocket), 1);

    o->rem              = xclientsocket_rem;
    o->handle.f         = xinvalid;
    o->process          = xclientsocketprocessor_tcp;
    o->check            = xclientsocketcheck_tcp;
    o->on               = xclientsocketsubscriber_tcp;
    o->event.descriptor = o;
    o->event.on         = xclientsocketeventhandler_tcp;
    o->domain           = domain;
    o->type             = type;
    o->protocol         = protocol;
    o->addr             = xobjectdup(addr, addrlen);
    o->addrlen          = addrlen;
    o->client           = client;

    return o;
}

extern xclientsocket * xclientsocket_rem(xclientsocket * o)
{
    xassertion(o == xnil, "");
    xassertion(o->subscription == xnil, "");
    if(o->handle.f >= 0)
    {
        // TODO: STDIN, OUT, ERR 를 종료시키지 않는다.
        close(o->handle.f);
        o->handle.f = xinvalid;
    }
    o->sync = xsyncrem(o->sync);
    o->addr = xobjectrem(o->addr);
    o->stream.in = xstreamrem(o->stream.in);
    o->stream.out = xstreamrem(o->stream.out);

    return xnil;
}

static xint64 xclientsocketprocessor_tcp(xclientsocket * o, xuint32 event, void * parameter)
{
    xassertion(xtrue, "implement this");
    return xfail;
}

static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * parameter, xint64 result)
{
    xassertion(xtrue, "implement this");
    return xfail;
}

static xint32 xclientsocketcheck_tcp(xclientsocket * o, xuint32 event)
{
    xassertion(xtrue, "implement this");
    return xfail;
}

static void xclientsocketeventhandler_tcp(xclientsocketevent * event)
{
    xassertion(xtrue, "implement this");
}

extern xint32 xclientsocketcheck_open(xclientsocket * o)
{
    xassertion(o == xnil, "");
    if(o->handle.f < 0)
    {
        return xfalse;
    }
    if(o->status & (xsocketstatus_exception | xsocketstatus_rem | xsocketstatus_close))
    {
        return xfalse;
    }
    if((o->status & (xsocketstatus_open | xsocketstatus_connecting | xsocketstatus_connect)) == xsocketstatus_void)
    {
        return xfalse;
    }
    return xtrue;
}

extern xint32 xclientsocketcheck_connecting(xclientsocket * o)
{
    return o->status & xsocketstatus_connecting;
}
