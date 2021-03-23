#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../../../thread.h"

#include "client.h"

#include "../../../client/socket/event/avail.h"

typedef xint64 (*xsocketeventprocessortcp)(xclientsocket * o);

static xint64 xclientsocketprocess_void(xclientsocket * o);
static xint64 xclientsocketprocess_open(xclientsocket * o);
static xint64 xclientsocketprocess_in(xclientsocket * o);
static xint64 xclientsocketprocess_out(xclientsocket * o);
static xint64 xclientsocketprocess_close(xclientsocket * o);
// static xint64 xclientsocketprocess_exception(xclientsocket * o);
static xint64 xclientsocketprocess_rem(xclientsocket * o);
static xint64 xclientsocketprocess_register(xclientsocket * o);
// static xint64 xclientsocketprocess_flush(xclientsocket * o);
static xint64 xclientsocketprocess_readoff(xclientsocket * o);
static xint64 xclientsocketprocess_writeoff(xclientsocket * o);
static xint64 xclientsocketprocess_opening(xclientsocket * o);
static xint64 xclientsocketprocess_create(xclientsocket * o);
// static xint64 xclientsocketprocess_bind(xclientsocket * o);
static xint64 xclientsocketprocess_clear(xclientsocket * o);
static xint64 xclientsocketprocess_alloff(xclientsocket * o);
// static xint64 xclientsocketprocess_connect(xclientsocket * o);
// static xint64 xclientsocketprocess_listen(xclientsocket * o);
// static xint64 xclientsocketprocess_connecting(xclientsocket * o);
static xint64 xclientsocketprocess_unregister(xclientsocket * o);

static xsocketeventprocessortcp socketeventprocessors[xdescriptoreventtype_max] = {
    xclientsocketprocess_void,          // xdescriptoreventtype_void
    xclientsocketprocess_open,          // xdescriptoreventtype_open
    xclientsocketprocess_in,            // xdescriptoreventtype_in
    xclientsocketprocess_out,           // xdescriptoreventtype_out
    xclientsocketprocess_close,         // xdescriptoreventtype_close
    xnil,                               // xdescriptoreventtype_exception
    xclientsocketprocess_rem,           // xdescriptoreventtype_rem
    xclientsocketprocess_register,      // xdescriptoreventtype_register
    xnil,                               // xdescriptoreventtype_flush
    xclientsocketprocess_readoff,       // xdescriptoreventtype_readoff
    xclientsocketprocess_writeoff,      // xdescriptoreventtype_writeoff
    xclientsocketprocess_opening,       // xdescriptoreventtype_opening
    xclientsocketprocess_create,        // xdescriptoreventtype_create
    xnil,                               // xdescriptoreventtype_bind
    xclientsocketprocess_clear,         // xdescriptoreventtype_clear
    xclientsocketprocess_alloff,        // xdescriptoreventtype_alloff
    xclientsocketprocess_open,          // xdescriptoreventtype_connect
    xnil,                               // xdescriptoreventtype_listen
    xclientsocketprocess_opening,       // xdescriptoreventtype_connecting
    xclientsocketprocess_unregister     // xdescriptoreventtype_unregister
};

extern xint64 xsocketprocessortcp_client(xclientsocket * o, xuint32 event)
{
    if(event < xdescriptoreventtype_max)
    {
        xsocketeventprocessortcp process = socketeventprocessors[event];
        if(process)
        {
            return process(o);
        }
        else
        {
            return xfail;
        }
    }
    xassertion(xtrue, "");
    return xfail;
}

static xint32 __maximum_retry_count = 32;

static xint64 xclientsocketprocess_void(xclientsocket * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xdescriptoreventgenerator_descriptor_unregister(o->subscription->generatornode.generator, (xdescriptor *) o);
        xdescriptorclose((xdescriptor *) o);
        xdescriptoreventgenerator_descriptor_dispatch(o->subscription->generatornode.generator, (xdescriptor *) o);

        return xsuccess;
    }

    if(xdescriptorstatuscheck_open((xdescriptor *) o) == xfalse)
    {
        xclientsocketprocess_open(o);
    }

    if(xdescriptorstatuscheck_open((xdescriptor *) o))
    {
        if((o->status & xdescriptorstatus_register) == xdescriptorstatus_void)
        {
            xdescriptoreventgenerator_descriptor_register(o->subscription->generatornode.generator, (xdescriptor *) o);
        }

        for(xint32 i = 0; i < __maximum_retry_count; i++)
        {
            xclientsocketprocess_out(o);
            xclientsocketprocess_in(o);
            xclientsocketprocess_out(o);

            if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
            {
                if((o->status & xdescriptorstatus_in) == xdescriptorstatus_void && xstreamlen(o->stream.out) == 0)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xdescriptoreventgenerator_descriptor_unregister(o->subscription->generatornode.generator, (xdescriptor *) o);
        xdescriptorclose((xdescriptor *) o);
        xdescriptoreventgenerator_descriptor_dispatch(o->subscription->generatornode.generator, (xdescriptor *) o);

        return xsuccess;
    }

    return xsuccess;
}

static xint64 xclientsocketprocess_open(xclientsocket * o)
{
    xsocketcreate((xsocket *) o);

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->status & xdescriptorstatus_connecting)
        {
            xint32 code = xsocketerror((xsocket *) o);
            if(code != xsuccess)
            {
                if((o->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
                {
                    o->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(o->exception), connect, code, xexceptiontype_sys, "");
                }
            }
            else
            {
                o->status &= (~xdescriptorstatus_connecting);
                o->status |= (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_out);
                xdescriptoron((xdescriptor *) o, xdescriptoreventtype_connect, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else
        {
            xclientsocketconnect(o, o->addr, o->addrlen);
        }
    }
    

    return o->status & xdescriptorstatus_exception;
}

static xint64 xclientsocketprocess_in(xclientsocket * o)
{
    return xdescriptorread((xdescriptor *) o, xstreamback(o->stream.in), xstreamremain(o->stream.in));
}

static xint64 xclientsocketprocess_out(xclientsocket * o)
{
    return xdescriptorwrite((xdescriptor *) o, xstreamfront(o->stream.out), xstreamlen(o->stream.out));
}

static xint64 xclientsocketprocess_close(xclientsocket * o)
{
    return xdescriptorclose((xdescriptor *) o);
}

static xint64 xclientsocketprocess_rem(xclientsocket * o)
{
    xassertion(xclientsocketeventavail_rem(o) == xfalse, "");

    if(xclientsocketeventavail_rem(o))
    {
        xassertion(xtrue, "implement this");
        // 서버를 삭제하면 모든 세션을 제거한다. ?????????

        return xsuccess;
    }

    return xfail;
}

static xint64 xclientsocketprocess_register(xclientsocket * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->status & xdescriptorstatus_register)
        {
            return xdescriptoreventgenerator_descriptor_update(o->subscription->generatornode.generator, (xdescriptor *) o);
        }
        else
        {
            return xdescriptoreventgenerator_descriptor_register(o->subscription->generatornode.generator, (xdescriptor *) o);
        }
    }

    return xfail;
}

static xint64 xclientsocketprocess_readoff(xclientsocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_readoff);
}

static xint64 xclientsocketprocess_writeoff(xclientsocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_writeoff);
}

static xint64 xclientsocketprocess_create(xclientsocket * o)
{
    return xsocketcreate((xsocket *) o);
}

static xint64 xclientsocketprocess_clear(xclientsocket * o)
{
    xassertion(o->handle.f >= 0, "");

    o->status = (o->status & xdescriptorstatus_rem);
    xstreamclear(o->stream.in);
    xstreamclear(o->stream.out);
    o->handle.f = xinvalid;

    return xsuccess;
}

static xint64 xclientsocketprocess_alloff(xclientsocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_alloff);
}

static xint64 xclientsocketprocess_opening(xclientsocket * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->status & xdescriptorstatus_connecting)
        {
            xint32 code = xsocketerror((xsocket *) o);
            if(code != xsuccess)
            {
                if((o->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
                {
                    o->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(o->exception), connect, code, xexceptiontype_sys, "");
                }
            }
            else
            {
                o->status &= (~xdescriptorstatus_connecting);
                o->status |= (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_out);
                xdescriptoron((xdescriptor *) o, xdescriptoreventtype_connect, xdescriptorparamgen(xnil), xsuccess);

                return xsuccess;
            }
        }
        else if(o->status & xdescriptorstatus_connect)
        {
            return xsuccess;
        }
    }

    return xfail;
}

static xint64 xclientsocketprocess_unregister(xclientsocket * o)
{
    return xdescriptoreventgenerator_descriptor_unregister(o->subscription->generatornode.generator, (xdescriptor *) o);
}