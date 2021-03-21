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
    xlogfunction_start("%s(%p)", __func__, o);
    xint64 ret = xfail;

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f < 0)
        {
            o->handle.f = socket(o->domain, o->type, o->protocol);

            if(o->handle.f < 0)
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), socket, errno, xexceptiontype_system, "");
                ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
            }
            else
            {
                o->status |= xsocketstatus_create;
                ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_create, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else
        {
            xassertion(o->status & xsocketstatus_create, "");

            if((o->status & xsocketstatus_create) == xsocketstatus_void)
            {
                o->status |= xsocketstatus_create;
                ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_create, xdescriptorparamgen(xnil), xsuccess);
            }
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketbind(xsocket * o, void * addr, xuint32 addrlen)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xint64 ret = xfail;

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f >= 0)
        {
            if(o->status & xsocketstatus_create)
            {
                if((o->status & xsocketstatus_bind) == xsocketstatus_void)
                {
                    ret = bind(o->handle.f, addr, addrlen);

                    if(ret < 0)
                    {
                        o->status |= xsocketstatus_exception;
                        xexceptionset(xaddressof(o->exception), bind, errno, xexceptiontype_system, "");
                        ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
                    }
                    else
                    {
                        o->status |= xsocketstatus_bind;
                        ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_bind, xdescriptorparamgen(xnil), xsuccess);
                    }
                }
                else
                {
                    ret = xsuccess;
                }
            }
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}
extern xint64 xsocketlisten(xsocket * o, xint32 backlog)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xint64 ret = xfail;

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f >= 0)
        {
            if((o->status & (xsocketstatus_create | xsocketstatus_bind)) == (xsocketstatus_create | xsocketstatus_bind))
            {
                if((o->status & xsocketstatus_listen) == xsocketstatus_void)
                {
                    ret = listen(o->handle.f, backlog);

                    if(ret < 0)
                    {
                        o->status |= xsocketstatus_exception;
                        xexceptionset(xaddressof(o->exception), listen, errno, xexceptiontype_system, "");
                        ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
                    }
                    else
                    {
                        
                        if((ret = xsocketresuseaddr(o, xtrue)) == xsuccess)
                        {
                            if((ret = xdescriptornonblock((xdescriptor *) o, xtrue)) == xsuccess)
                            {
                                o->status |= (xsocketstatus_listen | xsocketstatus_out);
                                ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_listen, xdescriptorparamgen(xnil), xsuccess);
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
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}
extern xint64 xsocketshutdown(xsocket * o, xuint32 how)
{
    if(o->handle.f > xdescriptorsystemno_max)
    {
        if(how == xsocketeventtype_readoff)
        {
            if((o->status & xsocketstatus_readoff) == xsocketstatus_void)
            {
                if(shutdown(o->handle.f, SHUT_RD) < 0)
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), shutdown, errno, xexceptiontype_system, "");
                    xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
                }

                o->status |= xsocketstatus_readoff;
                xdescriptoron((xdescriptor *) o, xsocketeventtype_readoff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else if(how == xsocketeventtype_writeoff)
        {
            if((o->status & xsocketstatus_writeoff) == xsocketstatus_void)
            {
                if(shutdown(o->handle.f, SHUT_WR) < 0)
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), shutdown, errno, xexceptiontype_system, "");
                    xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
                }

                o->status |= xsocketstatus_writeoff;
                xdescriptoron((xdescriptor *) o, xsocketeventtype_writeoff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else if(how == xsocketeventtype_alloff)
        {
            if((o->status & xsocketstatus_alloff) == xsocketstatus_void)
            {
                if(shutdown(o->handle.f, SHUT_RDWR) < 0)
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), shutdown, errno, xexceptiontype_system, "");
                    xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
                }

                o->status |= xsocketstatus_alloff;
                xdescriptoron((xdescriptor *) o, xsocketstatus_alloff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else
        {
            xassertion(xtrue, "");
        }

        if((o->status & xsocketstatus_alloff) == xsocketstatus_alloff)
        {
            o->status |= xsocketstatus_close;
        }
    }
    
    return xsuccess;
}
extern xint64 xsocketconnect(xsocket * o, void * addr, xuint32 addrlen)
{
    xlogfunction_start("%s(%p, %p, %u)", __func__, o, addr, addrlen);
    xint64 ret = xfail;

    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if((o->status & (xsocketstatus_open | xsocketstatus_opening)) == xsocketstatus_void)
        {
            if((o->status & xsocketstatus_create) && o->handle.f >= 0)
            {
                if((o->subscription && o->subscription->enginenode.engine) || (o->mask & xdescriptormask_nonblock))
                {
                    ret = xdescriptornonblock((xsocket *) o, xtrue);
                }
                
                if((o->status & xsocketstatus_exception) == xsocketstatus_void)
                {
                    ret = connect(o->handle.f, addr, addrlen);

                    if(ret == xsuccess)
                    {
                        o->status |= xsocketstatus_connect;
                        ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_connect, xdescriptorparamgen(xnil), ret);
                    }
                    else
                    {
                        if(errno == EAGAIN || errno == EINPROGRESS)
                        {
                            o->status |= xsocketstatus_connecting;
                            ret = xdescriptoron((xdescriptor *) o, xsocketstatus_connecting, xdescriptorparamgen(xnil), ret);
                        }
                        else
                        {
                            o->status |= xsocketstatus_exception;
                            xexceptionset(xaddressof(o->exception), connect, errno, xexceptiontype_system, "");
                            ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);                                            
                        }
                    }
                }
            }
            else
            {
                xassertion(xtrue, "");
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), xsocketconnect, 0, xexceptiontype_lib, "");
                ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
            }
        }
        else
        {
            xassertion(o->status & xsocketstatus_opening, "");
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketconnecting(xsocket * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xint64 ret = xsuccess;
    if(xdescriptorstatuscheck_opening((xdescriptor *) o))
    {
        int code = 0;
        socklen_t size = sizeof(int);
        if(getsockopt(o->handle.f, SOL_SOCKET, SO_ERROR, xaddressof(code), xaddressof(size)) == xsuccess)
        {
            if(code == EAGAIN || code == EINPROGRESS)
            {
                ret = xsuccess;
            }
            else if(code == 0)
            {
                o->status &= (~xsocketstatus_connecting);
                o->status |= xsocketstatus_connect;
                ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_connect, xdescriptorparamgen(xnil), xsuccess);
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), xsocketconnecting, code, xexceptiontype_lib, "");
                ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
            }
        }
        else
        {
            o->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(o->exception), getsockopt, errno, xexceptiontype_system, "");
            ret = xdescriptoron((xdescriptor *) o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
        }
    }
    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint32 xsocketresuseaddr(xsocket * o, xint32 on)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, on);
    xint32 ret = xfail;

    xassertion(xtrue, "implement this");

    xlogfunction_end("%s(...) => %d", ret);
    return ret;
}