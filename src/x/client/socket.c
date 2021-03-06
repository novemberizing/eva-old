#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "socket.h"

static xint64 xclientsocketprocessor_tcp_on(xclientsocket * o, xuint32 event, void * data);
static xint64 xclientsocketprocessor_tcp_open(xclientsocket * o);
static xint64 xclientsocketprocessor_tcp_in(xclientsocket * o);
static xint64 xclientsocketprocessor_tcp_out(xclientsocket * o);
static xint64 xclientsocketprocessor_tcp_close(xclientsocket * o);
static xint64 xclientsocketprocessor_tcp_exception(xclientsocket * o);

static xint32 xclientsocketstatuscheck_tcp(xclientsocket * o, xuint32 event);
static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * data, xint64 val);

extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xassertion(client == xnil, "");

    xclientsocket * o = (xclientsocket *) calloc(sizeof(xclientsocket), 1);

    o->handle.f       = xinvalid;
    o->client         = client;
    o->domain         = domain;
    o->type           = type;
    o->protocol       = protocol;
    o->addr           = xobjectdup(addr, addrlen);
    o->addrlen        = addrlen;

    o->process        = xclientsocketprocessor_tcp_on;
    o->check          = xclientsocketstatuscheck_tcp;
    o->on             = xclientsocketsubscriber_tcp;
    o->rem            = xclientsocket_rem;

    return o;
}

extern xclientsocket * xclientsocket_rem(xclientsocket * o)
{
    xassertion(o->subscription, "");
    xassertion(o->handle.f >= 0, "");
    xassertion(o->event.queue, "");

    o->sync = xsyncrem(o->sync);
    o->addr = xobjectrem(o->addr);
    o->stream.in = xstreamrem(o->stream.in);
    o->stream.out = xstreamrem(o->stream.out);

    free(o);

    return xnil;
}

static xint64 xclientsocketprocessor_tcp_on(xclientsocket * o, xuint32 event, void * data)
{
    switch(event)
    {
        case xdescriptoreventtype_open:         return xclientsocketprocessor_tcp_open(o);
        case xdescriptoreventtype_in:           return xclientsocketprocessor_tcp_in(o);
        case xdescriptoreventtype_out:          return xclientsocketprocessor_tcp_out(o);
        case xdescriptoreventtype_close:        return xclientsocketprocessor_tcp_close(o);
        case xdescriptoreventtype_exception:    return xclientsocketprocessor_tcp_close(o);
        // REMOVE LOGIC 은 살펴 보자.
        case xdescriptoreventtype_rem:          return xclientsocketprocessor_tcp_close(o);
    }
    xassertion(event, "");
}

static xint64 xclientsocketprocessor_tcp_open(xclientsocket * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        if((o->status & xdescriptorstatus_open) == xdescriptorstatus_void)
        {
            if(o->handle.f < 0)
            {
                xassertion(o->status & xsocketstatus_bind, "");
                xassertion(o->status & xsocketstatus_create, "");
                xassertion(o->status & xsocketstatus_connecting, "");
                xassertion(o->status & xsocketstatus_connect, "");

                o->handle.f = socket(o->domain, o->type, o->protocol);

                if(o->handle.f < 0)
                {
                    o->exception.func   = socket;
                    o->exception.number = errno;
                    o->status          |= xdescriptorstatus_exception;
                    return xfail;
                }
            }
            else
            {
                xassertion((o->status & xsocketstatus_create) == xdescriptorstatus_void, "");
                if(o->status & xsocketstatus_connect)
                {
                    return xsuccess;
                }
                if(o->status & xsocketstatus_connecting)
                {
                    xint32 value = xsuccess;
                    if(getsockopt(o->handle.f, SOL_SOCKET, SO_ERROR, &value, sizeof(xint32)) == xsuccess)
                    {
                        if(value == EAGAIN || value == EINPROGRESS)
                        {
                            return xsuccess;
                        }
                        else if(value == xsuccess)
                        {
                            o->status |= (xsocketstatus_connect | xsocketstatus_bind);
                            o->status &= (~xsocketstatus_connecting);
                            o->on(o, xsocketeventtype_connect, xnil, 0);
                            return xsuccess;
                        }
                        else
                        {
                            o->exception.func   = connect;
                            o->exception.number = value;
                            o->status          |= xdescriptorstatus_exception;
                            return xfail;
                        }
                    }
                    else
                    {
                        o->exception.func   = getsockopt;
                        o->exception.number = errno;
                        o->status          |= xdescriptorstatus_exception;
                        return xfail;
                    }
                }
            }
            xdescriptornonblock_set((xdescriptor *) o, xtrue);
            xint32 ret = connect(o->handle.f, o->addr, o->addrlen);
            if(ret == xsuccess)
            {
                o->status |= (xsocketstatus_connect | xsocketstatus_bind);
                o->on(o, xsocketeventtype_connect, xnil, 0);
                return xsuccess;
            }
            else
            {
                if(errno == EAGAIN || errno == EINPROGRESS)
                {
                    o->status |= xsocketstatus_connecting;
                    o->on(o, xsocketstatus_connecting, xnil, 0);
                    return xsuccess;
                }
                else
                {
                    o->exception.func   = connect;
                    o->exception.number = errno;
                    o->status          |= xdescriptorstatus_exception;
                    return xfail;
                }
            }
        }
        return xsuccess;
    }
    return xfail;
}

static xint64 xclientsocketprocessor_tcp_in(xclientsocket * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        // TODO: 적절한 TCP 버그 크기를 구한다.
        xstreamadjust(o->stream.in, xfalse);
        xstreamcapacity_set(o->stream.in, xstreamcapacity_get(o->stream.in) + 8192);
        xint64 n = xdescriptorread((xdescriptor *) o, xstreamback(o->stream.in), xstreamremain(o->stream.in));
        if(n > 0)
        {
            xstreamsize_set(o->stream.in, xstreamsize_get(o->stream.in) + n);
        }
        return n;
    }
    return xfail;
}

static xint64 xclientsocketprocessor_tcp_out(xclientsocket * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        // TODO: 적절한 TCP 버그 크기를 구한다.
        xstreamcapacity(o->stream.in, 8192);
        xint64 n = xdescriptorwrite((xdescriptor *) o, xstreamfront(o->stream.in), xstreamlen(o->stream.in));
        if(n > 0)
        {
            xstreampos_set(o->stream.out, xstreampos_get(o->stream.out) + n);
            xstreamadjust(o->stream.out, xfalse);
        }
        return n;
    }
    return xfail;
}

static xint64 xclientsocketprocessor_tcp_close(xclientsocket * o)
{
    if(o->exception.func)
    {
        o->on(o, xdescriptoreventtype_exception, xaddressof(o->exception), 0);
        xexceptioninit(xaddressof(o->exception));

    }
    if(o->handle.f >= 0)
    {

        // TODO: SHUTDOWN IMPLEMENT
        if(close(o->handle.f) != xsuccess)
        {
            o->exception.func   = close;
            o->exception.number = errno;
            o->on(o, xdescriptoreventtype_exception, xaddressof(o->exception), 0);
            xexceptioninit(xaddressof(o->exception));
        }
        o->status   |= xdescriptorstatus_close;
        o->handle.f  = xinvalid;
    }

    return xsuccess;
}

static xint32 xclientsocketstatuscheck_tcp(xclientsocket * o, xuint32 event)
{
    if(event == xdescriptoreventtype_out)
    {
        return xstreamlen(o->stream.out) > 0;
    }
    // 다른 이벤트 체크는 필요에 따라서 구현한다.
    xassertion(event, "");
}

static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * data, xint64 val)
{
    switch(event)
    {
        case xdescriptoreventtype_in:           return o->client->on(o->client, event, o->stream.in, val);
        case xdescriptoreventtype_out:          return o->client->on(o->client, event, o->stream.out, val);
        case xdescriptoreventtype_exception:    return o->client->on(o->client, event, xaddressof(o->exception), 0);
        case xdescriptoreventtype_close:        return o->client->on(o->client, event, xnil, 0);
        case xdescriptoreventtype_rem:          return o->client->on(o->client, event, xnil, 0);
        case xdescriptoreventtype_register:     return o->client->on(o->client, event, xnil, val);
    }
    return o->client->on(o->client, event, data, val);
}
