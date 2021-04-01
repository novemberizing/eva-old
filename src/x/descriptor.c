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

static xuint64 streambuffersize = 8192;

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
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        xdescriptoreventgenerator * generator = subscription ? descriptor->subscription->generatornode.generator : xnil;
        if(generator)
        {
            xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
        }
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
            descriptor->status = (descriptor->status & xdescriptorstatus_rem);
        }
        if(generator)
        {
            xdescriptoreventgenerator_descriptor_dispatch(generator, descriptor);
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

extern xint64 xdescriptorregister(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_open(descriptor))
    {
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        xdescriptoreventgenerator * generator = subscription ? subscription->generatornode.generator : xnil;
        

        if(generator)
        {
            if(subscription->generatornode.list == xnil)
            {
                xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
            }

            if((descriptor->status & xdescriptorstatus_register) == xdescriptorstatus_void)
            {
                xdescriptoreventgenerator_descriptor_register(generator, descriptor);
            }
            else
            {
                if((descriptor->status & (xdescriptorstatus_in | xdescriptorstatus_out)) != (xdescriptorstatus_in | xdescriptorstatus_out))
                {
                    xdescriptoreventgenerator_descriptor_update(generator, descriptor);
                }
                else
                {
                    if(descriptor->event.queue == xnil)
                    {
                        xeventengine_queue_push(subscription->enginenode.engine, (xevent *) xaddressof(descriptor->event));
                    }
                    else
                    {
                        xassertion(xtrue, "");
                    }
                }
            }

            return xdescriptorstatuscheck_close(descriptor) ? xfail : xsuccess;
        }
    }


    return xfail;
}

extern xint64 xdescriptorunregister(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;
    xdescriptoreventgenerator * generator = subscription ? subscription->generatornode.generator : xnil;

    if(generator)
    {
        if(subscription->generatornode.list == generator->alive)
        {
            xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
            xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
            return xsuccess;
        }
        else if(subscription->generatornode.list == xnil)
        {
            return xsuccess;
        }
        else
        {
            xassertion(xtrue, "");
        }
    }

    return xfail;
}

extern xint64 xdescriptorstreamread(xdescriptor * descriptor, xstream * stream, xuint64 capacity)
{
    xstreamadjust(stream, capacity, xfalse);
    if(xstreamremain(stream) < capacity)
    {
        xstreamcapacity_set(stream, xstreamcapacity_get(stream) + capacity - xstreamremain(stream));
    }

    xbyte * back = xstreamback(stream);

    xint64 ret = xdescriptorread(descriptor, xstreamback(stream), xstreamremain(stream));
    
    if(ret > 0)
    {
        xstreamsize_set(stream, xstreamsize_get(stream) + ret);

        ret = xdescriptoron(descriptor, xdescriptoreventtype_in, xdescriptorparamgen(back), ret);

        if(ret > 0)
        {
            xstreampos_set(stream, xstreampos_get(stream) + ret);
            xstreamadjust(stream, capacity, xfalse);
        }
    }

    return ret;
}

extern xint64 xdescriptorstreamwrite(xdescriptor * descriptor, xstream * stream)
{
    if(xstreamlen(stream) > 0)
    {
        xbyte * front = xstreamfront(stream);
        xint64 ret = xdescriptorwrite(descriptor, front, xstreamlen(stream));

        if(ret > 0)
        {
            xstreampos_set(stream, xstreampos_get(stream) + ret);

            ret = xdescriptoron(descriptor, xdescriptoreventtype_out, xdescriptorparamgen(front), ret);

            xstreamadjust(stream, streambuffersize, xfalse);  // capacity reset ... 
        }

        return ret;
    }
    return xdescriptorstatuscheck_close(descriptor) ? xfail : xsuccess;
}