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

static xint32 xsocketstatuscheck_void(xsocket * o);
static xint32 xsocketstatuscheck_open(xsocket * o);
static xint32 xsocketstatuscheck_in(xsocket * o);
static xint32 xsocketstatuscheck_out(xsocket * o);
static xint32 xsocketstatuscheck_create(xsocket * o);
static xint32 xsocketstatuscheck_exception(xsocket * o);
static xint32 xsocketstatuscheck_rem(xsocket * o);
static xint32 xsocketstatuscheck_register(xsocket * o);
static xint32 xsocketstatuscheck_flush(xsocket * o);
static xint32 xsocketstatuscheck_readoff(xsocket * o);
static xint32 xsocketstatuscheck_writeoff(xsocket * o);
static xint32 xsocketstatuscheck_opening(xsocket * o);
static xint32 xsocketstatuscheck_close(xsocket * o);
static xint32 xsocketstatuscheck_bind(xsocket * o);
static xint32 xsocketstatuscheck_alloff(xsocket * o);

static xint64 xsocketon(xsocket * o, xuint32 event, xdescriptorparam param, xint64 result)
{
    if(event == xsocketeventtype_exception)
    {
        result = o->on(o, event, param, result);
    }
    else
    {
        result = o->on(o, event, param, result);
        if(result < 0)
        {
            o->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(o->exception), o->on, 0, xexceptiontype_user, "");
            result = o->on(o, event, xdescriptorparamgen(xaddressof(o->exception)), result);
        }
    }
    return result;
}

extern xint64 xsocketcreate(xsocket * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    xint64 ret = xfail;
    if(xsocketstatuscheck_close(o) == xfalse)
    {
        if(o->handle.f < 0)
        {
            o->handle.f = socket(o->domain, o->type, o->protocol);

            if(o->handle.f >= 0)
            {
                if((o->status & xsocketstatus_create) == xsocketstatus_void)
                {
                    o->status |= xsocketstatus_create;
                    ret = xsocketon(o, xsocketeventtype_create, xdescriptorparamgen(xnil), xsuccess);
                }
                else
                {
                    xlognotice("already create");
                    ret = xsuccess;
                }
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), socket, errno, xexceptiontype_system, "");
                ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
            }
        }
        else
        {
            if((o->status & xsocketstatus_create) == xsocketstatus_void)
            {
                o->status |= xsocketstatus_create;
                ret = xsocketon(o, xsocketeventtype_create, xdescriptorparamgen(xnil), xsuccess);
            }
            else
            {
                xlognotice("already create");
                ret = xsuccess;
            }
        }
    }
    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketbind(xsocket * o, void * addr, xuint32 addrlen)
{
    xlogfunction_start("%s(%p, %p, %u)", __func__, o, addr, addrlen);

    xint64 ret = xfail;

    if(xsocketstatuscheck_close(o) == xfalse)
    {
        xassertion(o->handle.f < 0 || (o->status & xsocketstatus_create) == xsocketstatus_void, "");
        if(o->handle.f >= 0 && (o->status & xsocketstatus_create))
        {
            if((o->status & xsocketstatus_bind) == xsocketstatus_void)
            {
                ret = bind(o->handle.f, addr, addrlen);
                if(ret == xsuccess)
                {
                    o->status |= xsocketstatus_bind;
                    ret = xsocketon(o, xsocketeventtype_bind, xdescriptorparamgen(xnil), ret);
                }
                else
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), bind, errno, xexceptiontype_system, "");
                    ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
                }
            }
            else
            {
                xlognotice("already bind");
                ret = xsuccess;
            }
        }
        else
        {
            o->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(o->exception), xsocketbind, errno, xexceptiontype_lib, "");
            ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);

    return ret;
}

extern xint64 xsocketlisten(xsocket * o, xint32 backlog)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, backlog);
    xint64 ret = xfail;

    if(xsocketstatuscheck_close(o) == xfalse)
    {
        if(o->handle.f >= 0 && (o->status & (xsocketstatus_create | xsocketstatus_bind)) == (xsocketstatus_create | xsocketstatus_bind))
        {
            if((o->status & xsocketstatus_listen) == xsocketstatus_void)
            {
                ret = listen(o->handle.f, backlog);
                if(ret == xsuccess)
                {
                    if((o->subscription && o->subscription->enginenode.engine) || (o->mask & xdescriptormask_nonblock))
                    {
                        if(xdescriptornonblock_set((xdescriptor *) o, xtrue) == xsuccess)
                        {
                            o->status |= (xsocketstatus_listen | xsocketstatus_out);
                            ret = xsocketon(o, xsocketeventtype_listen, xdescriptorparamgen(xnil), ret);
                        }
                        else
                        {
                            o->status &= (~xsocketstatus_exception);
                            xexceptionset(xaddressof(o->exception), xdescriptornonblock_set, errno, xexceptiontype_lib, "");
                            ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), ret);
                        }
                    }
                    else
                    {
                        o->status |= (xsocketstatus_listen | xsocketstatus_out);
                        ret = xsocketon(o, xsocketeventtype_listen, xdescriptorparamgen(xnil), ret);
                    }
                }
                else
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), listen, errno, xexceptiontype_system, "");
                    ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
                }
            }
            else
            {
                xlognotice("already listen");
                ret = xsuccess;
            }
        }
        else
        {
            o->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(o->exception), xsocketlisten, errno, xexceptiontype_lib, "");
            ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketread(xsocket * o, void * buffer, xuint64 size)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, o, buffer, size);
    xint64 ret = xfail;

    if(xsocketstatuscheck_opening(o))
    {
        o->process(o, xsocketeventtype_opening, xdescriptorparamgen(xnil));
    }

    if(xsocketstatuscheck_open(o))
    {
        if(buffer && size)
        {
            ret = read(o->handle.f, buffer, size);

            if(ret > 0)
            {
                o->status |= xsocketstatus_in;
                ret = xsocketon(o, xsocketeventtype_in, xdescriptorparamgen(buffer), ret);
            }
            else if(ret == 0)
            {
                o->status |= xsocketstatus_close;
                ret = xfail;
            }
            else
            {
                if(errno != EAGAIN)
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), read, errno, xexceptiontype_system, "");
                    ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xnil), ret);
                }
                else
                {
                    o->status &= (~xsocketstatus_in);
                    ret = xsuccess;
                }
            }
        }
        else
        {
            xlogcaution("");
            ret = xsuccess;
        }
    }
    else
    {
        ret = xsocketstatuscheck_close(o) ? xfail : xsuccess;
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketwrite(xsocket * o, const void * data, xuint64 len)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, o, data, len);
    xint64 ret = xfail;

    if(xsocketstatuscheck_opening(o))
    {
        o->process(o, xsocketeventtype_opening, xdescriptorparamgen(xnil));
    }

    if(xsocketstatuscheck_open(o))
    {
        if(data && len)
        {
            ret = write(o->handle.f, data, len);

            if(ret > 0)
            {
                o->status |= xsocketstatus_out;
                ret = xsocketon(o, xsocketstatus_out, xdescriptorparamgen(xnil), ret);
            }
            else if(ret == 0)
            {
                xassertion(ret == 0, "");

                o->status |= xsocketstatus_close;
                ret = xfail;
            }
            else
            {
                if(errno != EAGAIN)
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), write, errno, xexceptiontype_system, "");
                    ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xnil), ret);
                }
                else
                {
                    o->status &= (~xsocketstatus_out);
                    ret = xsuccess;
                }
            }
        }
        else
        {
            xlogcaution("");
            ret = xsuccess;
        }
    }
    else
    {
        ret = xsocketstatuscheck_close(o) ? xfail : xsuccess;
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketclose(xsocket * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    if(o->handle.f > xdescriptorsystemno_max)
    {
        if(close(o->handle.f) != xsuccess)
        {
            xlogcaution("close(%d) => fail (%d)", o->handle.f, errno);
        }
        o->status |= xdescriptorstatus_close;
        xsocketon(o, xdescriptoreventtype_close, xdescriptorparamgen(xnil), xsuccess);
        o->handle.f = xinvalid;
    }

    xlogfunction_end("%s(...) => %ld", xsuccess);
    return xsuccess;
}

extern xint64 xsocketshutdown(xsocket * o, xuint32 how)
{
    xlogfunction_start("%s(%p, %u)", __func__, o, how);

    if(o->handle.f > xdescriptorsystemno_max)
    {
        if(how == xsocketeventtype_readoff)
        {
            if((o->status & xsocketeventtype_readoff) == xsocketeventtype_void)
            {
                if(shutdown(o->handle.f, SHUT_RD) != xsuccess)
                {
                    xlogcaution("fail to shutdown => %d", errno);
                }
                o->status |= xsocketstatus_readoff;
                xsocketon(o, xsocketstatus_readoff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else if(how == xsocketeventtype_writeoff)
        {
            if((o->status & xsocketeventtype_writeoff) == xsocketeventtype_void)
            {
                if(shutdown(o->handle.f, SHUT_WR) != xsuccess)
                {
                    xlogcaution("fail to shutdown => %d", errno);
                }
                o->status |= xsocketstatus_writeoff;
                xsocketon(o, xsocketstatus_writeoff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
        else if(how == xsocketeventtype_alloff)
        {
            if((o->status & (xsocketeventtype_readoff | xsocketeventtype_writeoff)) == xsocketeventtype_void)
            {
                if(shutdown(o->handle.f, SHUT_RDWR) != xsuccess)
                {
                    xlogcaution("fail to shutdown => %d", errno);
                }
                o->status |= xsocketstatus_alloff;
                xsocketon(o, xsocketstatus_alloff, xdescriptorparamgen(xnil), xsuccess);
            }
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
    // xsocketeventtype_offin
}

extern xint64 xsocketconnecting(xsocket * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xint64 ret = xfail;
    if(xsocketstatuscheck_opening(o))
    {
        int code = 0;
        socklen_t size = sizeof(int);
        ret = getsockopt(o->handle.f, SOL_SOCKET, SO_ERROR, xaddressof(code), xaddressof(size));
        if(ret == xsuccess)
        {
            if(code == 0)
            {
                o->status &= (~xsocketstatus_connecting);
                o->status |= (xsocketstatus_connect | xsocketstatus_out);
                ret = xsocketon(o, xsocketeventtype_connect, xdescriptorparamgen(xnil), code);
            }
            else if(code == EINPROGRESS || code == EAGAIN)
            {
                ret = xsuccess;
            }
            else
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), xsocketconnect, code, xexceptiontype_lib, "");
                xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
            }
        }
        else
        {
            o->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(o->exception), getsockopt, errno, xexceptiontype_system, "");
            xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xsocketconnect(xsocket * o, void * addr, xuint32 addrlen)
{
    xlogfunction_start("%s(%p, %p, %u)", __func__, o, addr, addrlen);

    xint64 ret = xfail;

    if(xsocketstatuscheck_open(o) == xfalse)
    {
        if(xsocketstatuscheck_opening(o))
        {
            ret = xsocketconnecting(o);
        }
        else
        {
            // TODO: 디스크립터가 엔진에 등록되어 있다면 언제나 논블럭을 설정한다.
            //       그렇지만 논블럭 설정 코드가 이곳에 있어야 하는지는 의문이다.
            if((o->subscription && o->subscription->enginenode.engine) || (o->mask & xdescriptormask_nonblock))
            {
                xdescriptornonblock_set((xdescriptor *) o, xtrue);
            }
            ret = connect(o->handle.f, addr, addrlen);
            if(ret == xsuccess)
            {
                o->status |= (xsocketstatus_connect | xsocketstatus_out);
                ret = xsocketon(o, xsocketeventtype_connect, xdescriptorparamgen(xnil), ret);
            }
            else
            {
                if(errno == EINPROGRESS || errno == EAGAIN)
                {
                    o->status |= xsocketstatus_connecting;
                    ret = xsocketon(o, xsocketeventtype_connecting, xdescriptorparamgen(xnil), ret);
                }
                else
                {
                    o->status |= xsocketstatus_exception;
                    xexceptionset(xaddressof(o->exception), connect, errno, xexceptiontype_system, "");
                    ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), xfail);
                }
            }
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint32 xsocketresuseaddr_set(xsocket * o, xint32 on)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, on);
    xint32 ret = xfail;

    if(xsocketstatuscheck_close(o) == xfalse)
    {
        if(o->handle.f >= 0)
        {
            ret = setsockopt(o->handle.f, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(xint32));

            if(ret != xsuccess)
            {
                o->status |= xsocketstatus_exception;
                xexceptionset(xaddressof(o->exception), setsockopt, errno, xexceptiontype_system, "");
                ret = xsocketon(o, xsocketeventtype_exception, xdescriptorparamgen(xaddressof(o->exception)), ret);
            }
        }
    }
    xlogfunction_end("%s(...) => %d", ret);
    return ret;
}

extern xint32 xsocketstatuscheck(xsocket * o, xuint32 status)
{
    xint32 ret = xfail;
    switch(status)
    {
        case xsocketstatus_void:        ret = xsocketstatuscheck_void(o);       break;
        case xsocketstatus_open:        ret = xsocketstatuscheck_open(o);       break;
        case xsocketstatus_in:          ret = xsocketstatuscheck_in(o);         break;
        case xsocketstatus_out:         ret = xsocketstatuscheck_out(o);        break;
        case xsocketstatus_close:       ret = xsocketstatuscheck_close(o);      break;
        case xsocketstatus_exception:   ret = xsocketstatuscheck_exception(o);  break;
        case xsocketstatus_rem:         ret = xsocketstatuscheck_rem(o);        break;
        case xsocketstatus_register:    ret = xsocketstatuscheck_register(o);   break;
        case xsocketstatus_flush:       ret = xsocketstatuscheck_flush(o);      break;
        case xsocketstatus_readoff:     ret = xsocketstatuscheck_readoff(o);    break;
        case xsocketstatus_writeoff:    ret = xsocketstatuscheck_writeoff(o);   break;
        case xsocketstatus_opening:     ret = xsocketstatuscheck_opening(o);    break;
        case xsocketstatus_create:      ret = xsocketstatuscheck_create(o);     break;
        case xsocketstatus_bind:        ret = xsocketstatuscheck_bind(o);       break;
        case xsocketstatus_alloff:      ret = xsocketstatuscheck_alloff(o);     break;
        default: xassertion(xtrue, ""); ret = xfalse;                           break;
    }

    return ret;
}

static xint32 xsocketstatuscheck_void(xsocket * o)
{
    return o->status == xsocketstatus_void;
}

static xint32 xsocketstatuscheck_open(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xfalse;
    }
    if(o->status & xsocketstatus_open)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_in(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xfalse;
    }
    if(o->status & xsocketstatus_in)
    {
        return xtrue;
    }
    return xfalse;
}
static xint32 xsocketstatuscheck_out(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xfalse;
    }
    if(o->status & xsocketstatus_out)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_create(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xfalse;
    }
    if(o->status & xsocketstatus_create)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_exception(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xfalse;
    }
    if(o->status & xsocketstatus_exception)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_rem(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xfalse;
    }
    if(o->status & xsocketstatus_rem)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_register(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xfalse;
    }
    if(o->status & xsocketstatus_register)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_flush(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xfalse;
    }
    if(o->status & xsocketstatus_flush)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_readoff(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xtrue;
    }
    if(o->status & xsocketstatus_readoff)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_writeoff(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xtrue;
    }
    if(o->status & xsocketstatus_writeoff)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_opening(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xtrue;
    }
    if(o->status & xsocketstatus_opening)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_close(xsocket * o)
{
    if(o->status & (xsocketstatus_exception | xsocketstatus_close | xsocketstatus_rem))
    {
        return xtrue;
    }
    if(o->handle.f < 0)
    {
        if(o->status != xsocketstatus_void)
        {
            return xtrue;
        }
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_bind(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xtrue;
    }
    if(o->status & xsocketstatus_bind)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xsocketstatuscheck_alloff(xsocket * o)
{
    if(xsocketstatuscheck_close(o))
    {
        return xtrue;
    }
    if((o->status & xsocketstatus_alloff) == xsocketstatus_alloff)
    {
        return xtrue;
    }
    return xfalse;
}