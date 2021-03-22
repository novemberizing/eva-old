#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "thread.h"
#include "socket.h"
#include "socket/status.h"
#include "descriptor.h"

extern xint64 xsocketcreate(xsocket * o)
{
    xint64 ret = xfail;
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f < 0)
        {
            o->handle.f = socket(o->domain, o->type, o->protocol);

            if(o->handle.f >= 0)
            {
                o->status |= xdescriptorstatus_create;

                ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_create, xdescriptorparamgen(xnil), xsuccess);
            }
            else
            {
                xdescriptorexception((xdescriptor *) o, socket, errno, xexceptiontype_sys, "");
            }
        }
        else
        {
            if((o->status & xdescriptorstatus_create) == xdescriptorstatus_void)
            {
                o->status |= xdescriptorstatus_create;
                ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_create, xdescriptorparamgen(xnil), xsuccess);
            }
            else
            {
                ret = xsuccess;
            }
        }
    }
    return ret;
}

extern xint64 xsocketbind(xsocket * o, void * addr, xuint32 addrlen)
{
    xint64 ret = xfail;
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f >= 0)
        {
            xassertion((o->status & xdescriptorstatus_create) == xdescriptorstatus_void, "");
            if(o->status & xdescriptorstatus_create)
            {
                if((o->status & xdescriptorstatus_bind) == xdescriptorstatus_void)
                {
                    xsocketresuseaddr(o, xtrue);
                    if((ret = bind(o->handle.f, addr, addrlen)) == xsuccess)
                    {
                        o->status |= xdescriptorstatus_bind;

                        ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_bind, xdescriptorparamgen(xnil), xsuccess);
                    }
                    else
                    {
                        xdescriptorexception((xdescriptor *) o, bind, errno, xexceptiontype_sys, "");
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
extern xint64 xsocketlisten(xsocket * o, xint32 backlog)
{
    xint64 ret = xfail;

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f >= 0)
        {
            xassertion((o->status & xdescriptorstatus_create) == xdescriptorstatus_void, "");
            if((o->status & (xdescriptorstatus_create | xdescriptorstatus_bind)) == (xdescriptorstatus_create | xdescriptorstatus_bind))
            {
                if((o->status & xdescriptorstatus_listen) == xdescriptorstatus_void)
                {
                    if((ret = listen(o->handle.f, backlog)) == xsuccess)
                    {
                        o->status |= xdescriptorstatus_listen;

                        ret = xdescriptoron((xdescriptor *) o, xdescriptorstatus_listen, xdescriptorparamgen(xnil), xsuccess);

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

extern xint64 xsocketshutdown(xsocket * o, xuint32 how)
{
    if(o->handle.f > xdescriptorsystemno_max)
    {
        if(how == xdescriptoreventtype_readoff)
        {
            if((o->status & xdescriptorstatus_readoff) == xdescriptorstatus_void)
            {
                if(shutdown(o->handle.f, SHUT_RD) != xsuccess)
                {
                    xassertion(xtrue, "shutdown(...) => %d", errno);
                }

                o->status |= xdescriptorstatus_readoff;
                xdescriptoron((xdescriptor *) o, xdescriptoreventtype_readoff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else if(how == xdescriptoreventtype_writeoff)
        {
            if((o->status & xdescriptorstatus_writeoff) == xdescriptorstatus_void)
            {
                if(shutdown(o->handle.f, SHUT_WR) != xsuccess)
                {
                    xassertion(xtrue, "shutdown(...) => %d", errno);
                }

                o->status |= xdescriptorstatus_writeoff;
                xdescriptoron((xdescriptor *) o, xdescriptoreventtype_writeoff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else if(how == xdescriptoreventtype_alloff)
        {
            if((o->status & xdescriptoreventtype_alloff) != xdescriptoreventtype_alloff)
            {
                if(shutdown(o->handle.f, SHUT_RDWR) != xsuccess)
                {
                    xassertion(xtrue, "shutdown(...) => %d", errno);
                }

                o->status |= xdescriptorstatus_alloff;
                xdescriptoron((xdescriptor *) o, xdescriptoreventtype_alloff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else
        {
            xassertion(xtrue, "");
        }
    }

    return xsuccess;
}

extern xint64 xsocketconnect(xsocket * o, void * addr, xuint32 addrlen)
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

extern xint64 xsocketconnecting(xsocket * o)
{
    xint64 ret = xfail;
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->status & xdescriptorstatus_connecting)
        {
            xint32 code = 0;
            socklen_t size = sizeof(xint32);
            if(getsockopt(o->handle.f, SOL_SOCKET, SO_ERROR, xaddressof(code), xaddressof(size)) == xsuccess)
            {
                if(code == EAGAIN || code == EINPROGRESS)
                {
                    ret = xsuccess;
                }
                else if(code == 0)
                {
                    o->status &= (~xdescriptorstatus_connecting);
                    o->status |= (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_out);
                    ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess);
                }
                else
                {
                    xdescriptorexception((xdescriptor *) o, connect, code, xexceptiontype_sys, "");
                }
            }
            else
            {
                xdescriptorexception((xdescriptor *) o, getsockopt, errno, xexceptiontype_sys, "");
            }
        }
        else
        {
            // 리턴 값에 대한 고민을 하자.
            ret = xfail;
        }
    }
    return ret;
}

extern xint32 xsocketresuseaddr(xsocket * o, xint32 on)
{
    xint32 ret = xfail;

    if(o->handle.f >= 0)
    {
        if((ret = setsockopt(o->handle.f, SOL_SOCKET, SO_REUSEADDR, xaddressof(on), sizeof(int))) != xsuccess)
        {
            xdescriptorexception((xdescriptor *) o, setsockopt, errno, xexceptiontype_sys, "");
        }
    }

    return ret;
}