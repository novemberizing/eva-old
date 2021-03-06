#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../thread.h"

#include "../socket.h"
#include "../session/socket.h"
#include "socket.h"

static void xserversocketeventhandler_tcp(xserversocketevent * server);
static xint64 xserversocketprocessor_tcp(xserversocket *, xuint32, void *);
static xint64 xserversocketsubscriber_tcp(xserversocket *, xuint32, void *, xint64);
static xint32 xserversocketcheck_tcp(xserversocket *, xuint32);

static xint64 xserversocketprocessor_tcp_open(xserversocket * descriptor, void * data);
static xint64 xserversocketprocessor_tcp_in(xserversocket * descriptor, void * data);
static xint64 xserversocketprocessor_tcp_close(xserversocket * descriptor, void * data);

extern xserversocket * xserversocket_new(xserver * server, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xserversocket * descriptor = calloc(sizeof(xserversocket), 1);

    descriptor->rem              = xserversocket_rem;
    descriptor->handle.f         = xinvalid;
    descriptor->process          = xserversocketprocessor_tcp;
    descriptor->check            = xserversocketcheck_tcp;
    descriptor->on               = xserversocketsubscriber_tcp;
    descriptor->event.on         = xserversocketeventhandler_tcp;
    descriptor->event.descriptor = descriptor;
    descriptor->domain           = domain;
    descriptor->type             = type;
    descriptor->protocol         = protocol;
    descriptor->addr             = xobjectdup(addr, addrlen);
    descriptor->addrlen          = addrlen;
    descriptor->server           = server;
    descriptor->backlog          = SOMAXCONN;

    return descriptor;
}

extern xint32 xserversocketcheck_open(xserversocket * descriptor)
{
    xassertion(descriptor == xnil, "");
    if(descriptor->handle.f < 0)
    {
        return xfalse;
    }
    if((descriptor->status & xserversocketstatus_open) == xserversocketstatus_void)
    {
        return xfalse;
    }

    return xtrue;
}

extern xint32 xserversocketcheck_close(xserversocket * descriptor)
{
    return descriptor->status & (xserversocketstatus_exception | xserversocketstatus_close | xserversocketstatus_rem);
}

extern xint32 xserversocketcheck_rem(xserversocket * descriptor)
{
    xassertion(descriptor == xnil, "");

    if(descriptor->subscription)
    {
        return xfalse;
    }
    if(descriptor->handle.f >= 0)
    {
        return xfalse;
    }
    if(descriptor->event.queue || descriptor->event.next || descriptor->event.prev)
    {
        return xfalse;
    }
    return xtrue;
}


extern xserversocket * xserversocket_rem(xserversocket * descriptor)
{
    xassertion(xserversocketcheck_rem(descriptor), "");

    descriptor->sync = xsyncrem(descriptor->sync);
    descriptor->addr = xobjectrem(descriptor->addr);

    free(descriptor);
    
    return xnil;
}

extern void xserversocketbacklog_set(xserversocket * descriptor, xint32 backlog)
{
    xassertion(descriptor == xnil, "");

    descriptor->backlog = backlog;
}

static void xserversocketeventhandler_tcp(xserversocketevent * event)
{
    xdescriptorevent_processor_on((xdescriptor *) event->descriptor);
}

static xint64 xserversocketprocessor_tcp(xserversocket * descriptor, xuint32 event, void * data)
{
    switch(event)
    {
        case xserversocketeventtype_open:   return xserversocketprocessor_tcp_open(descriptor, data);
        case xserversocketeventtype_in:     return xserversocketprocessor_tcp_in(descriptor, data);
        case xserversocketeventtype_out:    return xsuccess;
        case xserversocketeventtype_close:  return xserversocketprocessor_tcp_close(descriptor, data);
    }
    xassertion(xtrue, "implement this - check event 0x%08x", event);
}

static xint64 xserversocketprocessor_tcp_open(xserversocket * descriptor, void * data)
{
    if(xserversocketcheck_close(descriptor) == xfalse)
    {
        if(xserversocketcheck_open(descriptor) == xfalse)
        {
            if((descriptor->status & xsocketstatus_create) == xsocketstatus_void)
            {
                if(xsocketcreate((xsocket *) descriptor) != xsuccess)
                {
                    return xfail;
                }
            }
            xdescriptornonblock_set((xdescriptor *) descriptor, xtrue);
            xsocketresuseaddr_set((xsocket *) descriptor, xtrue);

            if((descriptor->status & xsocketstatus_bind) == xsocketstatus_void)
            {
                if(xsocketbind((xsocket *) descriptor, descriptor->addr, descriptor->addrlen) != xsuccess)
                {
                    return xfail;
                }
            }
            if((descriptor->status & xsocketstatus_listen) == xsocketstatus_void)
            {
                if(xsocketlisten((xsocket *) descriptor, descriptor->backlog) != xsuccess)
                {
                    return xfail;
                }
            }
            descriptor->status |= (xsocketstatus_open | xsocketstatus_out);
        }
        descriptor->status |= (xsocketstatus_out | xsocketstatus_out);
        return xsuccess;
    }
    return xfail;
}

static xint64 xserversocketprocessor_tcp_in(xserversocket * descriptor, void * data)
{
    xassertion(descriptor == xnil, "");
    xassertion(descriptor->subscription == xnil, "");
    xassertion(descriptor->server == xnil, "");

    xserver * server = descriptor->server;
    xserversocketeventsubscription * subscription = descriptor->subscription;
    xeventengine * engine = subscription->enginenode.engine;

    xassertion(engine == xnil, "");
    
    int f = accept(descriptor->handle.f, xnil, 0);

    if(f >= 0)
    {
        xsession * session = server->session.create(descriptor->domain, descriptor->type, descriptor->protocol);
        if(session)
        {
            session->server = server;

            xsessionsocket * sessionsocket = session->descriptor;

            sessionsocket->session = session;
            sessionsocket->handle.f = f;
            sessionsocket->status = (xsessionsocketstatus_open | xsessionsocketstatus_bind | xsessionsocketstatus_out);
            if(xeventengine_session_register(engine, session) == xnil)
            {
                xassertion(xtrue, "");
                return xfail;
            }
            xassertion((sessionsocket->status & xsessionsocketstatus_register) == xsessionsocketstatus_void, "");
            sessionsocket->on(sessionsocket, xsessionsocketstatus_open, xnil, xsuccess);
        }
        else
        {
            xcheck(xtrue, "shutdown apply");
            if(close(f) != xsuccess)
            {
                xassertion(xtrue, "");
            }
            xassertion(session == xnil, "");
        }
        return 1;
    }
    else
    {
        if(errno != EAGAIN)
        {
            xcheck(xtrue, "accept fail %d", errno);
            xassertion(xtrue, "implement this");
        }
        return 0;
        // 서버를 체크하도록 하자.
        
    }

    return xfail;
}

static xint64 xserversocketprocessor_tcp_close(xserversocket * descriptor, void * data)
{
    return xdescriptorclose((xdescriptor *) descriptor);
}

static xint64 xserversocketsubscriber_tcp(xserversocket * descriptor, xuint32 event, void * data, xint64 result)
{
    xserver * server = descriptor->server;
    if(descriptor->exception.number)
    {
        xcheck(xtrue, "exception errno => %d", descriptor->exception.number);
    }
    xcheck(xtrue, "event => 0x%08x, result => %ld", event, result);

    return server->on(server, event, data, result);
}

static xint32 xserversocketcheck_tcp(xserversocket * descriptor, xuint32 event)
{
    xassertion(xtrue, "implement this");
}
