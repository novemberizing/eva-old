#include <stdio.h>
#include <stdlib.h>

#include "../../../../thread.h"
#include "tcp.h"
#include "../avail.h"

static const xint32 maxretrycount = 32;

typedef xint64 (*xserversocketprocess)(xserversocket * o);

static xint64 xserversocketprocess_void(xserversocket * o);
static xint64 xserversocketprocess_open(xserversocket * o);
static xint64 xserversocketprocess_in(xserversocket * o);
static xint64 xserversocketprocess_out(xserversocket * o);
static xint64 xserversocketprocess_close(xserversocket * o);
static xint64 xserversocketprocess_exception(xserversocket * o);
static xint64 xserversocketprocess_rem(xserversocket * o);
static xint64 xserversocketprocess_register(xserversocket * o);
static xint64 xserversocketprocess_flush(xserversocket * o);
static xint64 xserversocketprocess_readoff(xserversocket * o);
static xint64 xserversocketprocess_writeoff(xserversocket * o);
static xint64 xserversocketprocess_opening(xserversocket * o);
static xint64 xserversocketprocess_create(xserversocket * o);
static xint64 xserversocketprocess_bind(xserversocket * o);
static xint64 xserversocketprocess_clear(xserversocket * o);
static xint64 xserversocketprocess_alloff(xserversocket * o);
static xint64 xserversocketprocess_connect(xserversocket * o);
static xint64 xserversocketprocess_listen(xserversocket * o);
static xint64 xserversocketprocess_connecting(xserversocket * o);
static xint64 xserversocketprocess_unregister(xserversocket * o);

static xserversocketprocess processes[xsocketeventtype_max] = {
    xserversocketprocess_void,          // xsocketeventtype_void           0
    xserversocketprocess_open,          // xsocketeventtype_open           1
    xserversocketprocess_in,            // xsocketeventtype_in             2
    xserversocketprocess_out,           // xsocketeventtype_out            3
    xserversocketprocess_close,         // xsocketeventtype_close          4
    xserversocketprocess_exception,     // xsocketeventtype_exception      5
    xserversocketprocess_rem,           // xsocketeventtype_rem            6
    xserversocketprocess_register,      // xsocketeventtype_register       7
    xserversocketprocess_flush,         // xsocketeventtype_flush          8
    xserversocketprocess_readoff,       // xsocketeventtype_readoff        9
    xserversocketprocess_writeoff,      // xsocketeventtype_writeoff       10
    xserversocketprocess_opening,       // xsocketeventtype_opening        11
    xserversocketprocess_create,        // xsocketeventtype_create         12
    xserversocketprocess_bind,          // xsocketeventtype_bind           13
    xserversocketprocess_clear,         // xsocketeventtype_clear          14
    xserversocketprocess_alloff,        // xsocketeventtype_alloff         15
    xserversocketprocess_connect,       // xsocketeventtype_connect        16
    xserversocketprocess_listen,        // xsocketeventtype_listen         17
    xserversocketprocess_connecting,    // xsocketeventtype_connecting     18
    xserversocketprocess_unregister     // xsocketeventtype_unregister     19
};

extern xint64 xserversocketprocess_tcp(xserversocket * o, xuint32 event)
{
    if(event < xsocketeventtype_max)
    {
        return processes[event](o);
    }
    xassertion(xtrue, "");
    return xfail;
}

extern xint64 xserversocketprocess_void(xserversocket * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xdescriptorclose((xdescriptor *) o);
        return xsuccess;
    }

    if(xserversocketeventavail_open(o))
    {
        xserversocketprocess_open(o);
    }

    for(xint32 i = 0; i < maxretrycount; i++)
    {
        xserversocketprocess_in(o);

        if(xdescriptorstatuscheck_close((xdescriptor *) o))
        {
            break;
        }

        if(o->status & xdescriptorstatus_in)
        {
            break;
        }
    }

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->status & xsocketstatus_in)
        {
            if(o->subscription && o->subscription->enginenode.engine)
            {
                if(o->event.queue == xnil)
                {
                    xeventengine_queue_push(o->subscription->enginenode.engine, (xevent *) xaddressof(o->event));
                }
                else
                {
                    xassertion(xtrue, "");
                }
            }
        }
        else
        {
            xdescriptorregister((xdescriptor *) o);
        }
    }

    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xdescriptorclose((xdescriptor *) o);

        return xsuccess;
    }

    return xfail;
}

static xint64 xserversocketprocess_open(xserversocket * o)
{
    xint64 ret = xfail;

    xsocketcreate((xsocket *) o);
    xsocketbind((xsocket *) o, o->addr, o->addrlen);
    xserversocketlisten(o, o->backlog);

    return xdescriptorstatuscheck_close((xdescriptor *) o) ? xfail : xsuccess;
}

static xint64 xserversocketprocess_in(xserversocket * o)
{
    xserveraccept(o);
    return xsuccess;
}

static xint64 xserversocketprocess_out(xserversocket * o)
{
    xassertion(xtrue, "");

    return xfail;
}

static xint64 xserversocketprocess_close(xserversocket * o)
{
    return xdescriptorclose((xdescriptor *) o);
}

static xint64 xserversocketprocess_exception(xserversocket * o)
{
    return xsuccess;
}

static xint64 xserversocketprocess_rem(xserversocket * o)
{
    xassertion(xtrue, "implement this");

    return xsuccess;
}

static xint64 xserversocketprocess_register(xserversocket * o)
{
    return xdescriptorregister((xdescriptor *) o);
}

static xint64 xserversocketprocess_flush(xserversocket * o)
{
    while((o->status & xdescriptorstatus_in) && xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        xserversocketprocess_in(o);
    }
}
static xint64 xserversocketprocess_readoff(xserversocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_readoff);
}

static xint64 xserversocketprocess_writeoff(xserversocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_writeoff);
}

static xint64 xserversocketprocess_opening(xserversocket * o)
{
    return xsuccess;
}

static xint64 xserversocketprocess_create(xserversocket * o)
{
    return xsocketcreate((xsocket *) o);
}

static xint64 xserversocketprocess_bind(xserversocket * o)
{
    return xsocketbind((xsocket *) o, o->addr, o->addrlen);
}

static xint64 xserversocketprocess_clear(xserversocket * o)
{
    xassertion(xtrue, "implement this");
    return xsuccess;
}

static xint64 xserversocketprocess_alloff(xserversocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_alloff);
}

static xint64 xserversocketprocess_connect(xserversocket * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xserversocketprocess_listen(xserversocket * o)
{
    return xserversocketlisten(o, o->backlog);
}

static xint64 xserversocketprocess_connecting(xserversocket * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xserversocketprocess_unregister(xserversocket * o)
{
    return xdescriptorunregister((xdescriptor *) o);
}
