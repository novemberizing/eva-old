#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "descriptor.h"
#include "thread.h"

#include "event/engine.h"

static xint32 xdescriptoreventavail_in(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_rem | xdescriptorstatus_exception))
    {
        return xfalse;
    }
    if(descriptor->handle.f < 0)
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_readoff;
}

static xint32 xdescriptoreventavail_out(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_rem | xdescriptorstatus_exception))
    {
        return xfalse;
    }
    if(descriptor->handle.f < 0)
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_writeoff;
}

extern xint64 xdescriptoron(xdescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
{
    if(event == xdescriptoreventtype_exception)
    {
        result = descriptor->on(descriptor, event, param, result);
    }
    else
    {
        xint64 n = descriptor->on(descriptor, event, param, result);
        if(result >=0 && n < 0)
        {
            descriptor->status |= xdescriptorstatus_exception;
            xexceptionset(xaddressof(descriptor->exception), descriptor->on, n, xexceptiontype_user, "");
            result = descriptor->process(descriptor, xdescriptoreventtype_exception);
        }
        else
        {
            result = n;
        }
    }
    return result;
}

extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
{
    xint64 ret = xfail;
    if(xdescriptoreventavail_in(descriptor))
    {
        if(buffer && size)
        {
            ret = read(descriptor->handle.f, buffer, size);
            if(ret > 0)
            {
                descriptor->status |= xdescriptorstatus_in;
                ret = xdescriptoron(descriptor, xdescriptoreventtype_in, xdescriptorparamgen(buffer), ret);
            }
            else if(ret == 0)
            {
                descriptor->status |= xdescriptorstatus_readend;
                descriptor->status &= (~xdescriptorstatus_in);
                ret = descriptor->process(descriptor, xdescriptoreventtype_readend);
            }
            else
            {
                if(errno == EAGAIN)
                {
                    descriptor->status &= (~(xdescriptorstatus_in | xdescriptorstatus_readend));
                    ret = xsuccess;
                }
                else
                {
                    descriptor->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(descriptor->exception), read, errno, xexceptiontype_sys, "");
                    descriptor->process(descriptor, xdescriptoreventtype_exception);
                }
            }
        }
        else
        {
            ret = xsuccess;
        }
    }
    return ret;
}

extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len)
{
    xint64 ret = xfail;
    if(xdescriptoreventavail_out(descriptor))
    {
        if(data && len)
        {
            ret = write(descriptor->handle.f, data, len);
            if(ret > 0)
            {
                descriptor->status |= xdescriptorstatus_out;
                ret = xdescriptoron(descriptor, xdescriptoreventtype_out, xdescriptorparamgen_const(data), ret);
            }
            else if(ret == 0)
            {
                descriptor->status |= xdescriptorstatus_writeend;
                descriptor->status &= (~xdescriptorstatus_out);
                ret = descriptor->process(descriptor, xdescriptoreventtype_writeend);
            }
            else
            {
                if(errno == EAGAIN)
                {
                    descriptor->status &= (~(xdescriptorstatus_out | xdescriptorstatus_writeend));
                    ret = xsuccess;
                }
                else
                {
                    descriptor->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(descriptor->exception), read, errno, xexceptiontype_sys, "");
                    descriptor->process(descriptor, xdescriptoreventtype_exception);
                }
            }
        }
        else
        {
            ret = xsuccess;
        }
    }
    return ret;
}

extern xint64 xdescriptorclose(xdescriptor * descriptor)
{
    if(descriptor->event.queue)
    {
        descriptor->status |= xdescriptorstatus_close;
    }
    else if(descriptor->subscription && descriptor->subscription->generatornode.list)
    {
        descriptor->status |= xdescriptorstatus_close;
    }
    else
    {
        if(descriptor->handle.f >= 0)
        {
            if(descriptor->subscription)
            {
                xdescriptoreventgenerator_descriptor_unregister(descriptor->subscription->generatornode.generator, descriptor);
            }
            if(descriptor->handle.f > xdescriptorsystemno_max)
            {
                if(close(descriptor->handle.f) != xsuccess)
                {
                    descriptor->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(descriptor->exception), close, errno, xexceptiontype_sys, "");
                    descriptor->process(descriptor, xdescriptoreventtype_exception);
                }
                xdescriptoron(descriptor, xdescriptoreventtype_close, xdescriptorparamgen(xnil), xsuccess);
            }
            descriptor->process(descriptor, xdescriptoreventtype_clear);
        }
        if(descriptor->subscription)
        {
            xdescriptoreventgenerator_descriptor_dispatch(descriptor->subscription->generatornode.generator, descriptor);
        }
    }
    return xsuccess;
}

extern xint64 xdescriptorexception(xdescriptor * descriptor, void * func, xint32 number, xuint32 type, const char * message)
{
    if(descriptor->status & xdescriptorstatus_exception)
    {
        descriptor->status |= xdescriptorstatus_exception;
        // TODO: LOGGING
    }
    xexceptionset(xaddressof(descriptor->exception), func, number, type, message);
    xdescriptoron(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), xfail);
    return xsuccess;
}

extern xint64 xdescriptorrem(xdescriptor * descriptor)
{
    if(descriptor->event.queue)
    {
        descriptor->status |= xdescriptorstatus_rem;
    }
    else if(descriptor->subscription && descriptor->subscription->generatornode.list)
    {
        descriptor->status |= xdescriptorstatus_rem;
    }
    else
    {
        descriptor->subscription = xdescriptoreventsubscription_rem(descriptor->subscription);
        descriptor = descriptor->rem(descriptor);
    }
    return xsuccess;
}

extern xint32 xdescriptornonblock(xdescriptor * descriptor, xint32 on)
{
    xint32 ret = xfail;
    if(descriptor->handle.f >= 0)
    {
        xint32 value = fcntl(descriptor->handle.f, F_GETFL);
        if(value >= 0)
        {
            if(on)
            {
                value |= O_NONBLOCK;
            }
            else
            {
                value &= (~O_NONBLOCK);
            }

            if(fcntl(descriptor->handle.f, F_SETFL, value) == xsuccess)
            {
                ret = xsuccess;
            }
            else
            {
                descriptor->status |= xdescriptorstatus_exception;
                xexceptionset(xaddressof(descriptor->exception), fcntl, errno, xexceptiontype_sys, "");
                descriptor->process(descriptor, xdescriptoreventtype_exception);                
            }
        }
        else
        {
            descriptor->status |= xdescriptorstatus_exception;
            xexceptionset(xaddressof(descriptor->exception), fcntl, errno, xexceptiontype_sys, "");
            descriptor->process(descriptor, xdescriptoreventtype_exception);
        }
    }
    return ret;
}

extern xint64 xdescriptoreventdispatch(xdescriptor * descriptor, xuint32 event)
{
    xint64 ret = xfail;
    xdescriptoreventsubscription * subscription = descriptor->subscription;
    if(subscription)
    {
        if((ret = xeventengine_descriptor_dispatch(descriptor, event)) != xsuccess)
        {
            ret = descriptor->process(descriptor, event);
        }
    }
    else
    {
        ret = descriptor->process(descriptor, event);
    }
    return ret;
}
