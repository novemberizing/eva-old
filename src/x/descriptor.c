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
#include "descriptor/event/avail.h"
#include "descriptor/event/dispatch.h"

extern xint64 xdescriptoron(xdescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
{
    if(event == xdescriptoreventtype_exception)
    {
        result = descriptor->on(descriptor, event, param, result);
    }
    else
    {
        xint64 ret = descriptor->on(descriptor, event, param, result);
        if(result >= 0 && ret < 0)
        {
            descriptor->status |= xdescriptorstatus_exception;
            xexceptionset(xaddressof(descriptor->exception), descriptor->on, ret, xexceptiontype_user, "");
            ret = descriptor->on(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), ret);
        }
        result = ret;
    }
    return result;
}

extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
{
    xint64 ret = xfail;
    if(xdescriptoreventavail_in(descriptor))
    {
        if(descriptor->status & xdescriptorstatus_open)
        {
            if(buffer && size)
            {
            ret = read(descriptor->handle.f, buffer, size);
            if(ret > 0) 
            {
                descriptor->status &= (~xdescriptorstatus_readend);
                descriptor->status |= xdescriptorstatus_in;
                ret = xdescriptoron(descriptor, xdescriptoreventtype_in, xdescriptorparamgen(buffer), ret);
            }
            else if(ret == 0)
            {
                descriptor->status &= (~xdescriptorstatus_in);
                descriptor->status |= xdescriptorstatus_readend;
                ret = xsuccess;
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
                    xdescriptorexception(descriptor, read, errno, xexceptiontype_sys, "");
                    ret = xfail;
                }
            }
            }
            else
            {
                ret = xsuccess;
            }
        }
        else
        {
            if(descriptor->status & xdescriptorstatus_connecting)
            {
                ret = xsuccess;
            }
        }
    }
    return ret;
}

extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len)
{
    xint64 ret = xfail;
    if(xdescriptoreventavail_out(descriptor))
    {
        if(descriptor->status & xdescriptorstatus_open)
        {
            if(data && len)
            {
            ret = write(descriptor->handle.f, data, len);
            if(ret > 0) 
            {
                descriptor->status &= (~xdescriptorstatus_writeend);
                descriptor->status |= xdescriptorstatus_out;
                ret = xdescriptoron(descriptor, xdescriptoreventtype_out, xdescriptorparamgen_const(data), ret);
            }
            else if(ret == 0)
            {
                descriptor->status &= (~xdescriptorstatus_out);
                descriptor->status |= xdescriptorstatus_writeend;
                ret = xsuccess;
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
                    xdescriptorexception(descriptor, write, errno, xexceptiontype_sys, "");
                    ret = xfail;
                }
            }
            }
            else
            {
                ret = xsuccess;
            }
        }
        else
        {
            if(descriptor->status & xdescriptorstatus_connecting)
            {
                ret = xsuccess;
            }
        }
    }
    return ret;
}

extern xint64 xdescriptorclose(xdescriptor * descriptor)
{
    if(descriptor->handle.f >= 0)
    {
        if(descriptor->handle.f > xdescriptorsystemno_max)
        {
            if(close(descriptor->handle.f) != xsuccess)
            {
                xassertion(xtrue, "close(...) => %d", errno);
            }
            descriptor->status |= xdescriptorstatus_close;
            descriptor->process(descriptor, xdescriptoreventtype_clear);
            xdescriptoron(descriptor, xdescriptoreventtype_close, xdescriptorparamgen(xnil), xsuccess);
            descriptor->handle.f = xinvalid;
        }
    }

    return xsuccess;
}

extern xint64 xdescriptorexception(xdescriptor * descriptor, void * func, xint32 number, xuint32 type, const char * message)
{
    descriptor->status |= xdescriptorstatus_exception;

    xexceptionset(xaddressof(descriptor->exception), func, number, type, message);

    return xsuccess;
}

extern xint32 xdescriptornonblock(xdescriptor * descriptor, xint32 on)
{
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
                return xsuccess;
            }
            xdescriptorexception(descriptor, fcntl, errno, xexceptiontype_sys, "");
        }
        else
        {
            xdescriptorexception(descriptor, fcntl, errno, xexceptiontype_sys, "");
        }
    }
    return xfail;
}
