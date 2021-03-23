#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "server.h"

#include "../../../session/socket.h"

typedef xint64 (*xsocketeventprocessortcp)(xserversocket * o);

static xint64 xdescriptoreventprocess_void(xserversocket * o);
static xint64 xdescriptoreventprocessserver_open(xserversocket * o);
static xint64 xdescriptoreventprocessserver_accept(xserversocket * o);
static xint64 xdescriptoreventprocessserver_close(xserversocket * o);
static xint64 xdescriptoreventprocessserver_rem(xserversocket * o);
static xint64 xdescriptoreventprocessserver_register(xserversocket * o);
static xint64 xdescriptoreventprocessserver_readoff(xserversocket * o);
static xint64 xdescriptoreventprocessserver_writeoff(xserversocket * o);
static xint64 xdescriptoreventprocessserver_create(xserversocket * o);
static xint64 xdescriptoreventprocessserver_bind(xserversocket * o);
static xint64 xdescriptoreventprocessserver_clear(xserversocket * o);
static xint64 xdescriptoreventprocessserver_alloff(xserversocket * o);
static xint64 xdescriptoreventprocessserver_listen(xserversocket * o);
static xint64 xdescriptoreventprocessserver_unregister(xserversocket * o);

static xsocketeventprocessortcp xsocketprocessors[xdescriptoreventtype_max] = {
    xdescriptoreventprocessserver_void, //  0: xdescriptoreventtype_void
    xdescriptoreventprocessserver_open, //  1: xdescriptoreventtype_open
    xdescriptoreventprocessserver_accept, //  2: xdescriptoreventtype_in
    xnil, //  3: xdescriptoreventtype_out
    xdescriptoreventprocessserver_close, //  4: xdescriptoreventtype_close
    xnil, //  5: xdescriptoreventtype_exception
    xdescriptoreventprocessserver_rem, //  6: xdescriptoreventtype_rem
    xdescriptoreventprocessserver_register, //  7: xdescriptoreventtype_register
    xnil, //  8: xdescriptoreventtype_flush
    xdescriptoreventprocessserver_readoff, //  9: xdescriptoreventtype_readoff
    xdescriptoreventprocessserver_writeoff, // 10: xdescriptoreventtype_writeoff
    xnil, // 11: xdescriptoreventtype_opening
    xdescriptoreventprocessserver_create, // 12: xdescriptoreventtype_create
    xdescriptoreventprocessserver_bind, // 13: xdescriptoreventtype_bind
    xdescriptoreventprocessserver_clear, // 14: xdescriptoreventtype_clear
    xdescriptoreventprocessserver_alloff, // 15: xdescriptoreventtype_alloff
    xnil, // 16: xdescriptoreventtype_connect
    xdescriptoreventprocessserver_listen, // 17: xdescriptoreventtype_listen
    xnil, // 18: xdescriptoreventtype_connecting
    xdescriptoreventprocessserver_unregister // 19: xdescriptoreventtype_unregister
};

extern xint64 xsocketprocessortcp_server(xserversocket * o, xuint32 event)
{
    xassertion(event >= xdescriptoreventtype_max, "");

    if(event < xdescriptoreventtype_max)
    {
        xsocketeventprocessortcp process = xsocketprocessors[event];
        if(process)
        {
            return process(o);
        }
    }
    return xfail;
}

static xint32 __maximum_retry_count = 32;

static xint64 xdescriptoreventprocessserver_void(xserversocket * o)
{
    xassertion(o->subscription == xnil, "");

    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xdescriptoreventgenerator_descriptor_unregister(o->subscription->generatornode.generator, (xdescriptor *) o);
        xdescriptorclose((xdescriptor *) o);
        xdescriptoreventgenerator_descriptor_dispatch(o->subscription->generatornode.generator, (xdescriptor *) o);

        return xsuccess;
    }

    if(xdescriptorstatuscheck_open((xdescriptor *) o) == xfalse)
    {
        xdescriptoreventprocessserver_open(o);
    }

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if((o->status & xdescriptorstatus_register) == xdescriptorstatus_void)
        {
            xdescriptoreventgenerator_descriptor_register(o->subscription->generatornode.generator, (xdescriptor *) o);
        }

        for(xint32 i = 0; i < __maximum_retry_count; i ++)
        {
            xdescriptoreventprocessserver_accept(o);
            if((o->status & xdescriptorstatus_in) == xdescriptorstatus_void || xdescriptorstatuscheck_close((xdescriptor *) o))
            {
                break;
            }
        }

        if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse && (o->status & xdescriptorstatus_in) == xdescriptorstatus_void)
        {
            xdescriptoreventgenerator_descriptor_update(o->subscription->generatornode.generator, (xdescriptor *) o);
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

static xint64 xdescriptoreventprocessserver_open(xserversocket * o)
{
    if(xserversocketeventavail_open(o))
    {
        xsocketcreate((xsocket *) o);
        xsocketbind((xsocket *) o, o->addr, o->addrlen);
        xsocketlisten((xsocket *) o, o->backlog);
    }

    return xdescriptorstatuscheck_open((xdescriptor *) o) ? xsuccess : xfail;
}

static xint64 xdescriptoreventprocessserver_accept(xserversocket * o)
{
    if(xserversocketstatuscheck_open(o))
    {
        int f = accept(o->handle.f, xnil, xnil);

        if(f >= 0)
        {
            xsession * session = o->server->session.create(o->server, o->domain, o->type, o->protocol);

            xassertion(session->server == xnil || session->cntr == xnil, "");
            
            session->descriptor->handle.f = f;
            session->descriptor->status |= xdescriptorstatus_open;

            xdescriptoron(session->descriptor, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess);

            session->descriptor->process(session->descriptor, xdescriptoreventtype_void);

            return xsuccess;
        }
        else
        {
            if(errno == EAGAIN)
            {
                o->status &= (~xsocketstatus_in);
            }
            else
            {
                xdescriptorexception((xdescriptor *) o, accept, errno, xexceptiontype_sys, "");
            }
        }
    }
    return xfail;
}

static xint64 xdescriptoreventprocessserver_close(xserversocket * o)
{
    return xdescriptorclose((xdescriptor *) o);
}

static xint64 xdescriptoreventprocessserver_rem(xserversocket * o)
{
    xassertion(xserversocketeventavail_rem(o) == xfalse, "");

    if(xserversocketeventavail_rem(o))
    {
        xassertion(xtrue, "implement this");
        // 서버를 삭제하면 모든 세션을 제거한다. ?????????

        return xsuccess;
    }

    return xfail;
}

static xint64 xdescriptoreventprocessserver_register(xserversocket * o)
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

static xint64 xdescriptoreventprocessserver_readoff(xserversocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_readoff);
}


static xint64 xdescriptoreventprocessserver_writeoff(xserversocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_writeoff);
}

static xint64 xdescriptoreventprocessserver_alloff(xserversocket * o)
{
    return xsocketshutdown((xsocket *) o, xdescriptoreventtype_alloff);
}

static xint64 xdescriptoreventprocessserver_create(xserversocket * o)
{
    return xsocketcreate((xsocket *) o);
}

static xint64 xdescriptoreventprocessserver_bind(xserversocket * o)
{
    return xsocketbind((xsocket *) o, o->addr, o->addrlen);
}

static xint64 xdescriptoreventprocessserver_clear(xserversocket * o)
{
    return xsuccess;
}

static xint64 xdescriptoreventprocessserver_listen(xserversocket * o)
{
    return xsocketlisten((xsocket *) o, o->backlog);
}

static xint64 xdescriptoreventprocessserver_unregister(xserversocket * o)
{
    return xdescriptoreventgenerator_descriptor_unregister(o->subscription->generatornode.generator, (xdescriptor *) o);
}
