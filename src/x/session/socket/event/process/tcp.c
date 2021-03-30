#include <stdio.h>
#include <stdlib.h>

#include "../../../../thread.h"

#include "tcp.h"

#include "../avail.h"
#include "../../../../server.h"

static const xuint64 socketbuffersize = 8192;
static const xint32 maxretrycount = 32;

typedef xint64 (*xsessionsocketprocess)(xsessionsocket * o);

static xint64 xsessionsocketprocess_void(xsessionsocket * o);
static xint64 xsessionsocketprocess_open(xsessionsocket * o);
static xint64 xsessionsocketprocess_in(xsessionsocket * o);
static xint64 xsessionsocketprocess_out(xsessionsocket * o);
static xint64 xsessionsocketprocess_close(xsessionsocket * o);
static xint64 xsessionsocketprocess_exception(xsessionsocket * o);
static xint64 xsessionsocketprocess_rem(xsessionsocket * o);
static xint64 xsessionsocketprocess_register(xsessionsocket * o);
static xint64 xsessionsocketprocess_flush(xsessionsocket * o);
static xint64 xsessionsocketprocess_readoff(xsessionsocket * o);
static xint64 xsessionsocketprocess_writeoff(xsessionsocket * o);
static xint64 xsessionsocketprocess_opening(xsessionsocket * o);
static xint64 xsessionsocketprocess_create(xsessionsocket * o);
static xint64 xsessionsocketprocess_bind(xsessionsocket * o);
static xint64 xsessionsocketprocess_clear(xsessionsocket * o);
static xint64 xsessionsocketprocess_alloff(xsessionsocket * o);
static xint64 xsessionsocketprocess_connect(xsessionsocket * o);
static xint64 xsessionsocketprocess_listen(xsessionsocket * o);
static xint64 xsessionsocketprocess_connecting(xsessionsocket * o);
static xint64 xsessionsocketprocess_unregister(xsessionsocket * o);

static xsessionsocketprocess processes[xsocketeventtype_max] = {
    xsessionsocketprocess_void,         // xsocketeventtype_void           0
    xsessionsocketprocess_open,         // xsocketeventtype_open           1
    xsessionsocketprocess_in,           // xsocketeventtype_in             2
    xsessionsocketprocess_out,          // xsocketeventtype_out            3
    xsessionsocketprocess_close,        // xsocketeventtype_close          4
    xsessionsocketprocess_exception,    // xsocketeventtype_exception      5
    xsessionsocketprocess_rem,          // xsocketeventtype_rem            6
    xsessionsocketprocess_register,     // xsocketeventtype_register       7
    xsessionsocketprocess_flush,        // xsocketeventtype_flush          8
    xsessionsocketprocess_readoff,      // xsocketeventtype_readoff        9
    xsessionsocketprocess_writeoff,     // xsocketeventtype_writeoff       10
    xsessionsocketprocess_opening,      // xsocketeventtype_opening        11
    xsessionsocketprocess_create,       // xsocketeventtype_create         12
    xsessionsocketprocess_bind,         // xsocketeventtype_bind           13
    xsessionsocketprocess_clear,        // xsocketeventtype_clear          14
    xsessionsocketprocess_alloff,       // xsocketeventtype_alloff         15
    xsessionsocketprocess_connect,      // xsocketeventtype_connect        16
    xsessionsocketprocess_listen,       // xsocketeventtype_listen         17
    xsessionsocketprocess_connecting,   // xsocketeventtype_connecting     18
    xsessionsocketprocess_unregister    // xsocketeventtype_unregister     19
};

extern xint64 xsessionsocketprocess_tcp(xsessionsocket * o, xuint32 event)
{
    if(event < xsocketeventtype_max)
    {
        return processes[event](o);
    }
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xsessionsocketprocess_void(xsessionsocket * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xsessionsocketclose(o);
        return xsuccess;
    }

    xsessionsocketprocess_flush(o);
    xsessionsocketprocess_in(o);
    xsessionsocketprocess_flush(o);

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->status & xsocketstatus_in)
        {
            if(o->subscription && o->subscription->enginenode.engine)
            {
                xeventengine_queue_push(o->subscription->enginenode.engine, (xevent *) xaddressof(o->event));
            }
        }
        else
        {
            xdescriptorregister((xdescriptor *) o);
        }
    }

    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xsessionsocketclose(o);
    }

    return xsuccess;
}

static xint64 xsessionsocketprocess_open(xsessionsocket * o)
{
    xassertion(xtrue, "");

    return xfail;
}

static xint64 xsessionsocketprocess_in(xsessionsocket * o)
{
    return xdescriptorstreamread((xdescriptor *) o, o->stream.in, socketbuffersize);
}

static xint64 xsessionsocketprocess_out(xsessionsocket * o)
{
    return xdescriptorstreamwrite((xdescriptor *) o, o->stream.out);
}

static xint64 xsessionsocketprocess_close(xsessionsocket * o)
{
    return xsessionsocketclose(o);
}

static xint64 xsessionsocketprocess_exception(xsessionsocket * o)
{
    xassertion(xtrue, "");

    return xsuccess;
}

static xint64 xsessionsocketprocess_rem(xsessionsocket * o)
{
    if(xsessionsocketeventavail_rem(o) == xfalse)
    {
        xassertion(xsessionsocketeventavail_rem(o) == xfalse, "");
        return xfail;
    }

    xsession * session = o->session;
    xserver * server = session->server;

    server->session.release(session);

    return xsuccess;
}

static xint64 xsessionsocketprocess_register(xsessionsocket * o)
{
    return xdescriptorregister((xdescriptor *) o);
}

static xint64 xsessionsocketprocess_flush(xsessionsocket * o)
{
    do {
        xdescriptorstreamwrite((xdescriptor *) o, o->stream.out);
    } while(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse && xstreamlen(o->stream.out) > 0 && (o->status & xsocketstatus_out) == xsocketstatus_void);

    return xsuccess;
}
static xint64 xsessionsocketprocess_readoff(xsessionsocket * o)
{
    return xsocketshutdown((xsocket *) o, xsocketeventtype_readoff);
}

static xint64 xsessionsocketprocess_writeoff(xsessionsocket * o)
{
    return xsocketshutdown((xsocket *) o, xsocketeventtype_writeoff);
}

static xint64 xsessionsocketprocess_opening(xsessionsocket * o)
{
    // 이 이벤트 타입에 대해서 고민이 많다. 어떻게 처리해야하는가?
    // 무엇을 하는 이벤트인가?
    xassertion(xtrue, "");

    return xfail;
}

static xint64 xsessionsocketprocess_create(xsessionsocket * o)
{
    xassertion(xtrue, "");
    
    return xfail;
}

static xint64 xsessionsocketprocess_bind(xsessionsocket * o)
{
    xassertion(xtrue, "");

    return xfail;
}

static xint64 xsessionsocketprocess_clear(xsessionsocket * o)
{
    return xsessionsocketclear(o);
}

static xint64 xsessionsocketprocess_alloff(xsessionsocket * o)
{
    return xsocketshutdown((xsocket *) o, xsocketeventtype_alloff);
}

static xint64 xsessionsocketprocess_connect(xsessionsocket * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xsessionsocketprocess_listen(xsessionsocket * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xsessionsocketprocess_connecting(xsessionsocket * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xsessionsocketprocess_unregister(xsessionsocket * o)
{
    return xdescriptorunregister((xdescriptor *) o);
}
