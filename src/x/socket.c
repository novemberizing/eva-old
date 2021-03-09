#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "thread.h"
#include "socket.h"
#include "descriptor.h"

extern xint64 xsocketcreate(xsocket * o)
{
    xassertion(o == xnil, "");
    if(o->handle.f < 0)
    {
        o->handle.f = socket(o->domain, o->type, o->protocol);
        if(o->handle.f >= 0)
        {
            o->status |= xsocketstatus_create;
            return xsuccess;
        }
        else
        {
            o->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(o->exception), socket, errno, 0, "");
            return xfail;
        }
    }

    if((o->status & xsocketstatus_create) == xsocketstatus_void)
    {
        o->status |= xsocketstatus_create;
    }

    return xsuccess;
}

extern xint64 xsocketbind(xsocket * o, void * addr, xuint32 addrlen)
{
    xassertion(o == xnil, "");
    xassertion(o->handle.f < 0 || (o->status & xsocketstatus_create) == xsocketstatus_void, "");

    if((o->status & xsocketstatus_exception) == xsocketstatus_void)
    {
        if((o->status & xsocketstatus_bind) == xsocketstatus_void)
        {
            xint32 ret = bind(o->handle.f, (struct sockaddr *) addr, addrlen);

            if(ret == xsuccess)
            {
                o->status |= xsocketstatus_bind;
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), bind, errno, 0, "");
                return xfail;
            }
        }

        return xsuccess;
    }
    return xfail;
}

extern xint64 xsocketlisten(xsocket * o, xint32 backlog)
{
    xassertion(o == xnil, "");
    xassertion(o->handle.f < 0 || (o->status & xsocketstatus_create) == xsocketstatus_void, "");
    xassertion((o->status & xsocketstatus_bind) == xsocketstatus_void, "");
    xassertion((o->status & (xsocketstatus_connect | xsocketstatus_connecting)) != xsocketstatus_void, "");

    // TODO: 클라이언트 소켓과 서버 소켓, 세션 소켓을 구분할 필요가 있을까? - 구분할 필요성을 찾고 요구사항이 존재하면 반영하도록 하자.
    // o->process 로 체크하도록 하자.

    if((o->status & xsocketstatus_exception) == xsocketstatus_void)
    {
        if((o->status & xsocketstatus_listen) == xsocketstatus_void)
        {
            int ret = listen(o->handle.f, backlog);
            if(ret == xsuccess)
            {
                o->status |= xsocketstatus_listen;
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), listen, errno, 0, "");
                return xfail;
            }
        }
        return xsuccess;
    }
    return xfail;
}

extern xint64 xsocketread(xsocket * o, void * buffer, xuint64 size)
{
    return xdescriptorread((xdescriptor *) o, buffer, size);
}

extern xint64 xsocketwrite(xsocket * o, const void * data, xuint64 len)
{
    return xdescriptorwrite((xdescriptor *) o, data, len);
}

extern xint64 xsocketclose(xsocket * o)
{
    return xdescriptorclose((xdescriptor *) o);
}

extern xint64 xsocketshutdown(xsocket * o, xuint32 how)
{
    if(how == xsocketeventtype_offin)
    {
        if((o->status & xsocketstatus_offin) == xsocketstatus_void)
        {
            int ret = shutdown(o->handle.f, SHUT_RD);
            if(ret == xsuccess)
            {
                o->status |= xsocketstatus_offin;
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), shutdown, errno, 0, "");
                return xfail;
            }
        }
        return xsuccess;
    }
    else if(how == xsocketeventtype_offout)
    {
        if((o->status & xsocketstatus_offout) == xsocketstatus_void)
        {
            int ret = shutdown(o->handle.f, SHUT_WR);
            if(ret == xsuccess)
            {
                o->status |= xsocketstatus_offin;
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), shutdown, errno, 0, "");
                return xfail;
            }
        }
        return xsuccess;
    }
    else if(how == xsocketeventtype_offall)
    {
        if((o->status & xsocketstatus_offall) == xsocketstatus_void)
        {
            int ret = shutdown(o->handle.f, SHUT_RDWR);
            if(ret == xsuccess)
            {
                o->status |= xsocketstatus_offin;
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), shutdown, errno, 0, "");
                return xfail;
            }
        }
        return xsuccess;
    }
    else
    {
        xassertion(xtrue, "");
    }
    return xfail;
}

extern xint64 xsocketconnect(xsocket * o, void * addr, xuint32 addrlen)
{
    xassertion(o == xnil, "");
    xassertion(o->handle.f < 0, "");
    xassertion((o->status & xsocketstatus_create) == xsocketstatus_void, "");

    if((o->status & xsocketstatus_exception) == xsocketstatus_void)
    {
        if((o->status & (xsocketstatus_connect | xsocketstatus_connecting)) == xsocketstatus_void)
        {
            int ret = connect(o->handle.f, (struct sockaddr *) addr, addrlen);
            if(ret == xsuccess)
            {
                o->status |= xsocketstatus_connect;
                return xsuccess;
            }
            else
            {
                if(errno != EAGAIN && errno != EINPROGRESS)
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), connect, errno, 0, "");
                    return xfail;
                }
                o->status |= xsocketstatus_connecting;
                return xsuccess;
            }
        }
        return xsuccess;
    }
    return xfail;
}

extern xint32 xsocketresuseaddr_set(xsocket * o, xint32 on)
{
    xassertion(o == xnil, "");
    xassertion(o->handle.f < 0 || (o->status & xsocketstatus_create) == xsocketstatus_void, "");

    int ret = setsockopt(o->handle.f, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(xint32));

    if(ret != xsuccess)
    {
        o->exception.func = setsockopt;
        o->exception.number = errno;
        o->status |= xsocketstatus_exception;

        return xfail;
    }

    return xsuccess;
}

extern const char * xsocketeventtype_str(xuint32 event)
{
    switch(event)
    {
        case xsocketeventtype_open:         return "open";
        case xsocketeventtype_in:           return "in";
        case xsocketeventtype_out:          return "out";
        case xsocketeventtype_close:        return "close";
        case xsocketeventtype_exception:    return "exception";
        case xsocketeventtype_rem:          return "rem";
        case xsocketeventtype_register:     return "register";
        case xsocketeventtype_create:       return "create";
        case xsocketeventtype_bind:         return "bind";
        case xsocketeventtype_connect:      return "connect";
        case xsocketeventtype_connecting:   return "connecting";
        case xsocketeventtype_listen:       return "listen";
        case xsocketeventtype_offin:        return "off in";
        case xsocketeventtype_offout:       return "off out";
        case xsocketeventtype_offall:       return "off all";
        default:                            return "unknown";
    }
}