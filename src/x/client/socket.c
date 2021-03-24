#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <netinet/in.h>

#include "../thread.h"
#include "../socket/handle.h"
#include "../socket/processor/tcp/client.h"

#include "socket.h"
#include "socket/status.h"
#include "socket/event.h"
#include "socket/event/type.h"
#include "socket/event/avail.h"

static xclientsocketprocessor xclientsocketprocessor_get(xint32 domain, xint32 type, xint32 protocol);
static xint64 xclientsocketon(xclientsocket * o, xuint32 event, xdescriptorparam param, xint64 result);
static void xclientsocketeventon(xclientsocketevent * event);

extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xclientsocket * o = (xclientsocket *) calloc(sizeof(xclientsocket), 1);

    o->rem = xclientsocket_rem;
    // o->subscription = xnil;
    // o->sync = xnil;
    // o->mask = xdescriptormask_void;
    // o->status = xsocketstatus_void;
    o->handle.f = xinvalid;
    o->process = xclientsocketprocessor_get(domain, type, protocol);
    // o->check = xnil;
    o->on = xclientsocketon;
    o->event.descriptor = o;
    o->event.on = xclientsocketeventon;
    o->domain = domain;
    o->type = type;
    o->protocol = protocol;
    o->addr = xobjectdup(addr, addrlen);
    o->addrlen = addrlen;
    // o->stream.in = xnil;
    // o->stream.out = xnil;
    o->client = client;

    return o;
}

extern xclientsocket * xclientsocket_rem(xclientsocket * o)
{
    if(o)
    {
        xassertion(xclientsocketeventavail_rem(o) == xfalse, "");

        o->subscription = xobjectrem(o->subscription);
        o->handle.f = xsockethandle_shutdown(o->handle.f);
        o->stream.in = xstreamrem(o->stream.in);
        o->stream.out = xstreamrem(o->stream.out);
        o->sync = xsyncrem(o->sync);
        o->addr = xobjectrem(o->addr);

        free(o);
    }
    return xnil;
}

extern xint64 xclientsocketconnect(xclientsocket * o, void * addr, xuint32 addrlen)
{
    xint64 ret = xfail;
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f >= 0 && (o->status & xsocketstatus_create))
        {
            if((o->status & (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_connecting)) == xdescriptorstatus_void)
            {
                if((o->subscription && o->subscription->enginenode.engine) || (o->mask & xdescriptormask_nonblock))
                {
                    xdescriptornonblock((xdescriptor *) o, xtrue);
                }

                if((o->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
                {
                    if((ret = connect(o->handle.f, addr, addrlen)) == xsuccess)
                    {
                        o->status |= (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_out);
                        ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess);
                        if(ret == xsuccess)
                        {
                            if(o->stream.in == xnil)
                            {
                                o->stream.in = xstreamnew(xstreamtype_buffer);
                            }
                            if(o->stream.out == xnil)
                            {
                                o->stream.out = xstreamnew(xstreamtype_buffer);
                            }
                        }
                    }
                    else
                    {
                        if(errno == EAGAIN || errno == EINPROGRESS)
                        {
                            o->status |= xdescriptorstatus_connecting;
                            ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_opening, xdescriptorparamgen(xnil), xsuccess);
                        }
                        else
                        {
                            xdescriptorexception((xdescriptor *) o, connect, errno, xexceptiontype_sys, "");
                        }
                    }
                }
            }
            else
            {
                ret = xsuccess;
            }
        }
    }
    return ret;
}

static xclientsocketprocessor xclientsocketprocessor_get(xint32 domain, xint32 type, xint32 protocol)
{
    if(domain == AF_INET)
    {
        if(type == SOCK_STREAM)
        {
            if(protocol == IPPROTO_TCP)
            {
                return xsocketprocessortcp_client;
            }
        }
    }
    xassertion(xtrue, "");
    return xnil;
}

static xint64 xclientsocketon(xclientsocket * o, xuint32 event, xdescriptorparam param, xint64 result)
{
    xclient * client = o->client;

    return client->on(client, event, param, result);
}

static void xclientsocketeventon(xclientsocketevent * event)
{
    xclientsocket * o = event->descriptor;

    o->process(o, xsocketeventtype_void);
}

static xint64 xserversocketon(xserversocket * o, xuint32 event, xdescriptorparam param, xint64 result)
{
    return result;
}
