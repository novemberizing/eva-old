#include <stdio.h>
#include <stdlib.h>

#include "../../../../thread.h"

#include "tcp.h"

#include "../avail.h"

static const xuint64 socketbuffersize = 8192;
static const xint32 maxretrycount = 32;

typedef xint64 (*xclientsocketprocess)(xclientsocket * o);

static xint64 xclientsocketprocess_void(xclientsocket * o);
static xint64 xclientsocketprocess_open(xclientsocket * o);
static xint64 xclientsocketprocess_in(xclientsocket * o);
static xint64 xclientsocketprocess_out(xclientsocket * o);
static xint64 xclientsocketprocess_close(xclientsocket * o);
static xint64 xclientsocketprocess_exception(xclientsocket * o);
static xint64 xclientsocketprocess_rem(xclientsocket * o);
static xint64 xclientsocketprocess_register(xclientsocket * o);
static xint64 xclientsocketprocess_flush(xclientsocket * o);
static xint64 xclientsocketprocess_readoff(xclientsocket * o);
static xint64 xclientsocketprocess_writeoff(xclientsocket * o);
static xint64 xclientsocketprocess_opening(xclientsocket * o);
static xint64 xclientsocketprocess_create(xclientsocket * o);
static xint64 xclientsocketprocess_bind(xclientsocket * o);
static xint64 xclientsocketprocess_clear(xclientsocket * o);
static xint64 xclientsocketprocess_alloff(xclientsocket * o);
static xint64 xclientsocketprocess_connect(xclientsocket * o);
static xint64 xclientsocketprocess_listen(xclientsocket * o);
static xint64 xclientsocketprocess_connecting(xclientsocket * o);
static xint64 xclientsocketprocess_unregister(xclientsocket * o);

static xclientsocketprocess processes[xsocketeventtype_max] = {
    xclientsocketprocess_void,          // xsocketeventtype_void           0
    xclientsocketprocess_open,          // xsocketeventtype_open           1
    xclientsocketprocess_in,            // xsocketeventtype_in             2
    xclientsocketprocess_out,           // xsocketeventtype_out            3
    xclientsocketprocess_close,         // xsocketeventtype_close          4
    xclientsocketprocess_exception,     // xsocketeventtype_exception      5
    xclientsocketprocess_rem,           // xsocketeventtype_rem            6
    xclientsocketprocess_register,      // xsocketeventtype_register       7
    xclientsocketprocess_flush,         // xsocketeventtype_flush          8
    xclientsocketprocess_readoff,       // xsocketeventtype_readoff        9
    xclientsocketprocess_writeoff,      // xsocketeventtype_writeoff       10
    xclientsocketprocess_opening,       // xsocketeventtype_opening        11
    xclientsocketprocess_create,        // xsocketeventtype_create         12
    xclientsocketprocess_bind,          // xsocketeventtype_bind           13
    xclientsocketprocess_clear,         // xsocketeventtype_clear          14
    xclientsocketprocess_alloff,        // xsocketeventtype_alloff         15
    xclientsocketprocess_connect,       // xsocketeventtype_connect        16
    xclientsocketprocess_listen,        // xsocketeventtype_listen         17
    xclientsocketprocess_connecting,    // xsocketeventtype_connecting     18
    xclientsocketprocess_unregister     // xsocketeventtype_unregister     19
};

extern xint64 xclientsocketprocess_tcp(xclientsocket * o, xuint32 event)
{
    if(event < xsocketeventtype_max)
    {
        return processes[event](o);
    }
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xclientsocketprocess_void(xclientsocket * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xdescriptorclose((xdescriptor *) o);
        return xsuccess;
    }

    if(xclientsocketeventavail_open(o))
    {
        xclientsocketprocess_open(o);
    }

    for(xint32 i = 0; i < maxretrycount; i++)
    {
        xclientsocketprocess_out(o);
        xclientsocketprocess_in(o);
        xclientsocketprocess_out(o);

        if(xdescriptorstatuscheck_close((xdescriptor * ) o))
        {
            break;
        }
        else if((o->status & xdescriptorstatus_in) == xdescriptorstatus_void && xstreamlen(o->stream.out) == 0)
        {
            break;
        }
    }

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(xstreamlen(o->stream.out) == 0)
        {
            o->status |= xdescriptorstatus_out;
        }

        xdescriptorregister((xdescriptor *) o);
    }

    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xdescriptorclose((xdescriptor *) o);
    }

    return xsuccess;
}

static xint64 xclientsocketprocess_open(xclientsocket * o)
{
    xsocketcreate((xsocket *) o);
    xclientsocketconnect(o, o->addr, o->addrlen);

    return xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse &&
           (o->status & (xsocketstatus_open | xsocketstatus_connect | xsocketstatus_connecting));
}

static xint64 xclientsocketprocess_in(xclientsocket * o)
{
    return xdescriptorstreamread((xdescriptor *) o, o->stream.in, socketbuffersize);
}

static xint64 xclientsocketprocess_out(xclientsocket * o)
{
    return xdescriptorstreamwrite((xdescriptor *) o, o->stream.out);
}

static xint64 xclientsocketprocess_close(xclientsocket * o)
{
    return xdescriptorclose((xdescriptor *) o);
}

static xint64 xclientsocketprocess_exception(xclientsocket * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xclientsocketprocess_rem(xclientsocket * o)
{
    if(xclientsocketeventavail_rem(o) == xfalse)
    {
        xassertion(xclientsocketeventavail_rem(o) == xfalse, "");
        return xfail;
    }

    o = o->rem(o);

    return xsuccess;
}

static xint64 xclientsocketprocess_register(xclientsocket * o)
{
    return xdescriptorregister((xdescriptor *) o);
}

static xint64 xclientsocketprocess_flush(xclientsocket * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}
static xint64 xclientsocketprocess_readoff(xclientsocket * o)
{
    return xsocketshutdown((xsocket *) o, xsocketeventtype_readoff);
}

static xint64 xclientsocketprocess_writeoff(xclientsocket * o)
{
    return xsocketshutdown((xsocket *) o, xsocketeventtype_writeoff);
}

static xint64 xclientsocketprocess_opening(xclientsocket * o)
{
    // 이 이벤트 타입에 대해서 고민이 많다. 어떻게 처리해야하는가?
    // 무엇을 하는 이벤트인가?
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xclientsocketprocess_create(xclientsocket * o)
{
    return xsocketcreate((xsocket *) o);
}

static xint64 xclientsocketprocess_bind(xclientsocket * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xclientsocketprocess_clear(xclientsocket * o)
{
    return xclientsocketclear(o);
}

static xint64 xclientsocketprocess_alloff(xclientsocket * o)
{
    return xsocketshutdown((xsocket *) o, xsocketeventtype_alloff);
}

static xint64 xclientsocketprocess_connect(xclientsocket * o)
{
    return xclientsocketconnect(o, o->addr, o->addrlen);
}

static xint64 xclientsocketprocess_listen(xclientsocket * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xclientsocketprocess_connecting(xclientsocket * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xclientsocketprocess_unregister(xclientsocket * o)
{
    return xdescriptorunregister((xdescriptor *) o);
}

