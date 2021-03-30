#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../thread.h"

#include "../socket.h"
#include "socket/event/process/tcp.h"

#include "../session/socket.h"
#include "socket.h"
#include "socket/event/avail.h"

static xserversocketprocessor xserversocketprocessor_get(xint32 domain, xint32 type, xint32 protocol);

static xint64 xserversocketprocess(xserversocket * o, xuint32 event);
static void xserversocketeventon(xserversocketevent * event);
static xint64 xserversocketon(xserversocket * o, xuint32 event, xdescriptorparam param, xint64 result);

extern xserversocket * xserversocket_new(xserver * server, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xserversocket * o = (xserversocket *) calloc(sizeof(xserversocket), 1);

    o->rem              = xserversocket_rem;
    o->subscription     = xnil;
    o->sync             = xnil;
    o->mask             = xdescriptormask_void;
    o->status           = xsocketstatus_void;
    o->handle.f         = xinvalid;
    o->process          = xserversocketprocessor_get(domain, type, protocol);
    o->check            = xnil;
    o->on               = xserversocketon;
    o->event.descriptor = o;
    o->event.on         = xserversocketeventon;
    o->exception        = xexception_void;
    o->domain           = domain;
    o->type             = type;
    o->protocol         = protocol;
    o->addr             = xobjectdup(addr, addrlen);
    o->addrlen          = addrlen;
    o->backlog          = SOMAXCONN;
    o->server           = server;

    return o;
}

extern xserversocket * xserversocket_rem(xserversocket * o)
{
    if(o)
    {
        xassertion(xserversocketeventavail_rem(o) == xfalse, "");

        o->subscription = xobjectrem(o->subscription);
        o->sync = xsyncrem(o->sync);
        if(o->handle.f >= 0)
        {
            if(close(o->handle.f) != xsuccess)
            {
                xassertion(xtrue, "close(...) => %d", errno);
            }
        }
        o->addr = xobjectrem(o->addr);
    }

    return xnil;
}

extern xint64 xserversocketlisten(xserversocket * o, xint32 backlog)
{
    xint64 ret = xfail;

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f >= 0)
        {
            xassertion((o->status & xdescriptorstatus_create) == xdescriptorstatus_void, "");
            if((o->status & (xdescriptorstatus_create | xdescriptorstatus_bind)) == (xdescriptorstatus_create | xdescriptorstatus_bind))
            {
                printf("= 1 =\n");
                if((o->status & xdescriptorstatus_listen) == xdescriptorstatus_void)
                {
                    printf("= 2 =\n");
                    if((ret = listen(o->handle.f, backlog)) == xsuccess)
                    {
                        printf("= 3 =\n");
                        o->status |= (xdescriptorstatus_listen | xdescriptorstatus_open | xdescriptorstatus_out);

                        ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess);

                        if((o->subscription && o->subscription->enginenode.engine) || (o->mask & xdescriptormask_nonblock))
                        {
                            xdescriptornonblock((xdescriptor *) o, xtrue);
                        }
                    }
                    else
                    {
                        xdescriptorexception((xdescriptor *) o, listen, errno, xexceptiontype_sys, "");
                    }
                }
                else
                {
                    ret = xsuccess;
                }
            }
        }
    }

    return ret;
}

extern xint32 xserveraccept(xserversocket * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        int f = accept(o->handle.f, xnil, xnil);
        if(f >= 0)
        {
            xserver * server = o->server;
            xserversocketeventsubscription * subscription = o->subscription;
            xeventengine * engine = subscription->enginenode.engine;

            xsession * session = server->session.create(server, o->domain, o->type, o->protocol);

            session->descriptor->handle.f = f;
            session->descriptor->status |= xdescriptorstatus_create;

            xint64 ret = xdescriptoron((xdescriptor *) session->descriptor, xdescriptoreventtype_create, xdescriptorparamgen(xnil), xsuccess);

            if(ret == xsuccess)
            {
                if(session->descriptor->stream.in == xnil)
                {
                    session->descriptor->stream.in = xstreamnew(xstreamtype_buffer);
                }
                if(session->descriptor->stream.out == xnil)
                {
                    session->descriptor->stream.out = xstreamnew(xstreamtype_buffer);
                }

                session->descriptor->status |= (xdescriptorstatus_open | xdescriptorstatus_out);

                ret = xdescriptoron((xdescriptor *) session->descriptor, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess);

                if(ret == xsuccess)
                {
                    xeventengine_session_register(engine, session);
                }
            }

            return ret;
        }
        else
        {
            if(errno == EAGAIN)
            {
                return xsuccess;
            }
            else
            {
                if(errno == EBADF || errno == EINVAL || errno == ENOTSOCK || errno == EOPNOTSUPP)
                {
                    xdescriptorexception((xdescriptor *) o, accept, errno, xexceptiontype_sys, "");

                    return xfail;
                }
                else
                {
                    xassertion(xtrue, "accept => %d", errno);

                    return xsuccess;
                }
            }
        }
    }

    return xfail;
}

static xserversocketprocessor xserversocketprocessor_get(xint32 domain, xint32 type, xint32 protocol)
{
    if(domain == AF_INET)
    {
        if(type == SOCK_STREAM)
        {
            if(protocol == IPPROTO_TCP)
            {
                return xserversocketprocess_tcp;
            }
        }
    }
    xassertion(xtrue, "");
    return xnil;
}

static void xserversocketeventon(xserversocketevent * event)
{
    xserversocket * descriptor = event->descriptor;
    
    descriptor->process(descriptor, xsocketeventtype_void);
}

static xint64 xserversocketon(xserversocket * o, xuint32 event, xdescriptorparam param, xint64 result)
{
    printf("event => %s\n", xdescriptoreventtype_str(event));
    return result;
}


