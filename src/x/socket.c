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
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");
    if(o->handle.f < 0)
    {
        o->handle.f = socket(o->domain, o->type, o->protocol);
        if(o->handle.f >= 0)
        {
            o->status |= xsocketstatus_create;

            xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
            return xsuccess;
        }
        else
        {
            o->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(o->exception), socket, errno, 0, "");

            xlogfunction_end("%s(...) => %ld", __func__, xfail);
            return xfail;
        }
    }

    if((o->status & xsocketstatus_create) == xsocketstatus_void)
    {
        o->status |= xsocketstatus_create;
    }

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

extern xint64 xsocketbind(xsocket * o, void * addr, xuint32 addrlen)
{
    xlogfunction_start("%s(%p, %p, %u)", __func__, o, addr, addrlen);

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

                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), bind, errno, 0, "");

                xlogfunction_end("%s(...) => %ld", __func__, xfail);
                return xfail;
            }
        }

        xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
        return xsuccess;
    }

    xlogfunction_end("%s(...) => %ld", __func__, xfail);
    return xfail;
}

extern xint64 xsocketlisten(xsocket * o, xint32 backlog)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, backlog);

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

                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), listen, errno, 0, "");

                xlogfunction_end("%s(...) => %ld", __func__, xfail);
                return xfail;
            }
        }

        xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
        return xsuccess;
    }

    xlogfunction_end("%s(...) => %ld", __func__, xfail);
    return xfail;
}

extern xint64 xsocketread(xsocket * o, void * buffer, xuint64 size)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, o, buffer, size);

    xint64 ret = xdescriptorread((xdescriptor *) o, buffer, size);

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketwrite(xsocket * o, const void * data, xuint64 len)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, o, data, len);

    xint64 ret = xdescriptorwrite((xdescriptor *) o, data, len);

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketclose(xsocket * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xint64 ret = xdescriptorclose((xdescriptor *) o);

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketshutdown(xsocket * o, xuint32 how)
{
    xlogfunction_start("%s(%p, %u)", __func__, o, how);

    if(how == xsocketeventtype_offin)
    {
        if((o->status & xsocketstatus_offin) == xsocketstatus_void)
        {
            int ret = shutdown(o->handle.f, SHUT_RD);
            if(ret == xsuccess)
            {
                o->status |= xsocketstatus_offin;

                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), shutdown, errno, 0, "");

                xlogfunction_end("%s(...) => %ld", __func__, xfail);
                return xfail;
            }
        }

        xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
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

                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), shutdown, errno, 0, "");

                xlogfunction_end("%s(...) => %ld", __func__, xfail);
                return xfail;
            }
        }

        xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
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

                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), shutdown, errno, 0, "");

                xlogfunction_end("%s(...) => %ld", __func__, xfail);
                return xfail;
            }
        }

        xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
        return xsuccess;
    }
    else
    {
        xassertion(xtrue, "");
    }

    xlogfunction_end("%s(...) => %ld", __func__, xfail);
    return xfail;
}

extern xint64 xsocketconnect(xsocket * o, void * addr, xuint32 addrlen)
{
    xlogfunction_start("%s(%p, %p, %u)", __func__, o, addr, addrlen);

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
                o->status |= (xsocketstatus_connect | xsocketstatus_open | xsocketstatus_out);

                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
            else
            {
                if(errno != EAGAIN && errno != EINPROGRESS)
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), connect, errno, 0, "");

                    xlogfunction_end("%s(...) => %ld", __func__, xfail);
                    return xfail;
                }
                o->status |= xsocketstatus_connecting;

                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
        }

        xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
        return xsuccess;
    }

    xlogfunction_end("%s(...) => %ld", __func__, xfail);
    return xfail;
}

extern xint32 xsocketresuseaddr_set(xsocket * o, xint32 on)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, on);

    xassertion(o == xnil, "");
    xassertion(o->handle.f < 0 || (o->status & xsocketstatus_create) == xsocketstatus_void, "");

    int ret = setsockopt(o->handle.f, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(xint32));

    if(ret != xsuccess)
    {
        o->exception.func = setsockopt;
        o->exception.number = errno;
        o->status |= xsocketstatus_exception;

        xlogfunction_end("%s(...) => %d", __func__, xfail);
        return xfail;
    }

    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}

/**
 * DO NOT LOGGING
 */
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