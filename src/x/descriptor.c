#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "descriptor.h"
#include "thread.h"

#include "event/engine.h"

extern xint32 xdescriptorcheck_rem(xdescriptor * descriptor)
{
    return (descriptor->status & xdescriptorstatus_rem) && descriptor->handle.f < 0 && descriptor->event.queue == xnil;
}

extern xint32 xdescriptorcheck_close(xdescriptor * descriptor)
{
    return descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_exception | xdescriptorstatus_rem);
}

extern xint32 xdescriptorcheck_open(xdescriptor * descriptor)
{
    return xdescriptorcheck_close(descriptor) == xfalse && (descriptor->status & xdescriptorstatus_open);
}

extern xint64 xdescriptorevent_processor_on(xdescriptor * descriptor)
{
    xassertion(descriptor == xnil, "");

    if(xdescriptorcheck_close(descriptor))
    {
        xdescriptorevent_processor_unregister(descriptor);
        return xdescriptorevent_processor_close(descriptor);
    }
    else if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
    {
        xdescriptorevent_processor_open(descriptor);
    }
    xuint32 status = (descriptor->status & (xdescriptorstatus_in | xdescriptorstatus_out));

    xdescriptorevent_processor_out(descriptor);
    xdescriptorevent_processor_in(descriptor);

    if((descriptor->status & (xdescriptorstatus_in | xdescriptorstatus_out)) != (xdescriptorstatus_in | xdescriptorstatus_out))
    {
        xdescriptorevent_processor_register(descriptor);
    }

    if(xdescriptorcheck_close(descriptor))
    {
        xdescriptorevent_processor_unregister(descriptor);
        xdescriptorevent_processor_close(descriptor);
        return xfail;
    }

    return xsuccess;
}

/**
 * 이 함수는 
 */
extern xint64 xdescriptorevent_processor_open(xdescriptor * descriptor)
{
    xassertion(xdescriptorcheck_open(descriptor), "");
    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_open, xnil);
    return descriptor->on(descriptor, xdescriptoreventtype_open, xnil, n);
}

extern xint64 xdescriptorevent_processor_out(xdescriptor * descriptor)
{
    if(xdescriptorcheck_open(descriptor))
    {
        xint64 n = descriptor->process(descriptor, xdescriptoreventtype_out, xnil);
        return descriptor->on(descriptor, xdescriptoreventtype_out, xnil, n);
    }
    return xfail;
}

extern xint64 xdescriptorevent_processor_in(xdescriptor * descriptor)
{
    if(xdescriptorcheck_open(descriptor))
    {
        xint64 n = descriptor->process(descriptor, xdescriptoreventtype_in, xnil);

        return descriptor->on(descriptor, xdescriptoreventtype_in, xnil, n);
    }
    return xfail;
}

extern xint64 xdescriptorevent_processor_close(xdescriptor * descriptor)
{
    xassertion(descriptor->event.queue, "");
    xassertion(descriptor->status & xdescriptorstatus_register, "");

    xdescriptoreventsubscription * subscription = descriptor->subscription;
    xdescriptoreventgenerator *       generator = subscription->generatornode.generator;
    xint64                                    n = xsuccess;

    if(subscription->generatornode.list == generator->alive)
    {
        xdescriptoreventgeneratorsubscriptionlist_del(descriptor->subscription);
    }

    n = descriptor->process(descriptor, xdescriptoreventtype_close, xnil);
    n = descriptor->on(descriptor, xdescriptoreventtype_close, xnil, n);
    
    /**
     * 콘솔 입출력의 경우 핸들 값이 설정된 상태일 수 있다.
     * 이 함수는 UNREGISTER 가 수행된 상태에서 호출이 된다.
     */
    descriptor->exception = xexception_void;
    descriptor->status    = (descriptor->status & xdescriptorstatus_rem) ? xdescriptorstatus_rem : xdescriptorstatus_void;

    if(subscription->generatornode.list != generator->queue)
    {
        xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
    }

    return xsuccess;
}

extern xint64 xdescriptorevent_processor_register(xdescriptor * descriptor)
{
    if(xdescriptorcheck_open(descriptor))
    {
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        xdescriptoreventgenerator * generator = subscription->generatornode.generator;
        xint64 n = xdescriptoreventgenerator_descriptor_update(generator, descriptor);
        return descriptor->on(descriptor, xdescriptoreventtype_register, xnil, n == xsuccess);
    }

    return xfail;
}

extern xint64 xdescriptorevent_processor_unregister(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;
    xdescriptoreventgenerator * generator = subscription->generatornode.generator;
    xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
    descriptor->on(descriptor, xdescriptoreventtype_register, xnil, xfalse);
    return xsuccess;
}

extern xint64 xdescriptorevent_processor_rem(xdescriptor * descriptor)
{
    if(xdescriptorcheck_rem(descriptor))
    {
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        xeventengine * engine = subscription->enginenode.engine;

        xeventengine_descriptor_unregister(engine, descriptor);

        // TODO: CHECK SUBSCRIPTION
        xassertion(subscription->enginenode.engine || subscription->enginenode.prev || subscription->enginenode.next, "");
        xassertion(subscription->generatornode.prev || subscription->generatornode.next || subscription->generatornode.list, "");

        descriptor->subscription = xnil;
        descriptor->on(descriptor, xdescriptoreventtype_rem, xnil, 0);

        descriptor->status = xdescriptorstatus_void;
        descriptor = descriptor->rem(descriptor);

        free(subscription);
    }
    else
    {
        xassertion((descriptor->status & xdescriptorstatus_rem) == xdescriptorstatus_void, "");

        xdescriptoreventsubscription * subscription = descriptor->subscription;
        xdescriptoreventgenerator * generator = subscription->generatornode.generator;
        xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
    }
    return xsuccess;
}

extern xint64 xdescriptorevent_processor_exception(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;
    xdescriptoreventgenerator *       generator = subscription->generatornode.generator;
    xint64                                    n = xsuccess;

    n = descriptor->process(descriptor, xdescriptoreventtype_exception, xnil);
    n = descriptor->on(descriptor, xdescriptoreventtype_exception, xnil, n);

    if(subscription->generatornode.list == generator->alive)
    {
        xdescriptoreventgeneratorsubscriptionlist_del(descriptor->subscription);
    }
    
    n = descriptor->process(descriptor, xdescriptoreventtype_close, xnil);
    n = descriptor->on(descriptor, xdescriptoreventtype_close, xnil, n);

    if(subscription->generatornode.list != generator->queue)
    {
        xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
    }

    return xsuccess;
}

extern xint64 xdescriptorevent_dispatch_on(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(subscription)
    {
        if(xeventengine_descriptor_dispatch(descriptor) != xsuccess)
        {
            return xdescriptorevent_processor_on(descriptor);
        }
        return xsuccess;
    }
    else
    {
        return xdescriptorevent_processor_on(descriptor);
    }
}

extern xint64 xdescriptorevent_dispatch_open(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(xdescriptorcheck_close(descriptor) == xfalse)
    {
        if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
        {
            if(subscription)
            {
                if(xeventengine_descriptor_dispatch(descriptor) != xsuccess)
                {
                    return xdescriptorevent_processor_open(descriptor);
                }
                return xsuccess;
            }
            else
            {
                return xdescriptorevent_processor_open(descriptor);
            }
        }
        // 두번 오픈이 호출된 것이다. 큰 문제는 없지만, 체크는 할 필요가 있다.
        // 이것을 호출한 것은 불필요한 로직이 호출된 것이다.
        return xsuccess;
    }
    return xfail;
}
extern xint64 xdescriptorevent_dispatch_in(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(xdescriptorcheck_open(descriptor))
    {
        if(subscription)
        {
            if(xeventengine_descriptor_dispatch(descriptor) != xsuccess)
            {
                xint64 n = xdescriptorevent_processor_in(descriptor);
                if(n > 0)
                {
                    xeventengine_queue_push(subscription->enginenode.engine, (xevent *) xaddressof(descriptor->event));
                }
                else if(n == 0)
                {
                    if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
                    {
                        xassertion(xtrue, "implement this");
                    }
                }
                return n;
            }
            return xsuccess;
        }
        else
        {
            return xdescriptorevent_processor_in(descriptor);
        }
    }
    return xfail;
}
extern xint64 xdescriptorevent_dispatch_out(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(xdescriptorcheck_open(descriptor))
    {
        if(subscription)
        {
            if(xeventengine_descriptor_dispatch(descriptor) != xsuccess)
            {
                xint64 n = xdescriptorevent_processor_out(descriptor);
                if(n > 0)
                {
                    xeventengine_queue_push(subscription->enginenode.engine, (xevent *) xaddressof(descriptor->event));
                }
                else if(n == 0)
                {
                    if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
                    {
                        xassertion(xtrue, "implement this");
                    }
                }
                return n;
            }
            return xsuccess;
        }
        else
        {
            return xdescriptorevent_processor_out(descriptor);
        }
    }
    return xfail;
}

extern xint64 xdescriptorevent_dispatch_close(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if((descriptor->status & xdescriptorstatus_close) == xdescriptorstatus_void)
    {
        descriptor->status |= xdescriptorstatus_close;
        if(subscription)
        {
            if(xeventengine_descriptor_dispatch(descriptor) != xsuccess)
            {
                xdescriptorevent_processor_unregister(descriptor);
                return xdescriptorevent_processor_close(descriptor);
            }
            return xsuccess;
        }
        else
        {
            return xdescriptorevent_processor_close(descriptor);
        }    
    }
    
    return xfail;
}

/**
 * 
 * 이 함수는 메인 함수에서 불려야 한다.
 */
extern xint64 xdescriptorevent_dispatch_rem(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if((descriptor->status & xdescriptorstatus_rem) == xdescriptorstatus_void)
    {
        descriptor->status |= xdescriptorstatus_rem;
        if(subscription)
        {
            if(xeventengine_descriptor_dispatch(descriptor) != xsuccess)
            {
                xdescriptorevent_processor_unregister(descriptor);
                xdescriptorevent_processor_close(descriptor);
                return xdescriptorevent_processor_rem(descriptor);
            }
            return xsuccess;
        }
        else
        {
            xdescriptorevent_processor_unregister(descriptor);
            xdescriptorevent_processor_close(descriptor);
            return xdescriptorevent_processor_rem(descriptor);
        }    
    }
    
    return xfail;
}

extern xint64 xdescriptorevent_dispatch_exception(xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if((descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
    {
        descriptor->status |= xdescriptorstatus_exception;
        if(subscription)
        {
            if(xeventengine_descriptor_dispatch(descriptor) != xsuccess)
            {
                xdescriptorevent_processor_unregister(descriptor);
                return xdescriptorevent_processor_exception(descriptor);
            }
            return xsuccess;
        }
        else
        {
            return xdescriptorevent_processor_exception(descriptor);
        }    
    }
    
    return xfail;
}

extern xint64 xdescriptorclose(xdescriptor * descriptor)
{
    if(descriptor->handle.f >= 0)
    {
        int ret = close(descriptor->handle.f);
        xassertion(ret != xsuccess, "");
        descriptor->handle.f = xinvalid;
        descriptor->status |= xdescriptorstatus_close;
    }
    return xsuccess;
}

extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
{
    if(xdescriptorcheck_open(descriptor))
    {
        if(buffer && size)
        {
            xint64 n = read(descriptor->handle.f, buffer, size);
            if(n > 0)
            {
                descriptor->status |= xdescriptorstatus_in;
                return n;
            }
            else if(n == 0)
            {
                descriptor->status |= xdescriptorstatus_exception;
                descriptor->exception.func = read;
                descriptor->exception.number = 0;
                return xfail;
            }
            else
            {
                if(errno != EAGAIN)
                {
                    descriptor->status |= xdescriptorstatus_exception;
                    descriptor->exception.func = read;
                    descriptor->exception.number = errno;
                    return xfail;
                }
                descriptor->status &= (~xdescriptorstatus_in);
                return xsuccess;
            }
        }
        else
        {
            return xsuccess;
        }
    }
    return xfail;
}

extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len)
{
    if(xdescriptorcheck_open(descriptor))
    {
        if(data && len)
        {
            xint64 n = write(descriptor->handle.f, data, len);

            if(n > 0)
            {
                descriptor->status |= xdescriptorstatus_out;
                return n;
            }
            else if(n == 0)
            {
                xassertion(n == 0, "check this");
                return xsuccess;
            }
            else
            {
                if(errno != EAGAIN)
                {
                    descriptor->status |= xdescriptorstatus_exception;
                    descriptor->exception.func = write;
                    descriptor->exception.number = errno;
                    return xfail;
                }
                descriptor->status &= (~xdescriptorstatus_out);
                return xsuccess;
            }
        }
        else
        {
            return xsuccess;
        }
    }
    return xfail;
}

extern xint32 xdescriptornonblock_set(xdescriptor * descriptor, xint32 on)
{
    xassertion(descriptor == xnil || descriptor->handle.f < 0, "");

    int mask = fcntl(descriptor->handle.f, F_GETFL, 0);
    if(mask < 0)
    {
        descriptor->exception.func   = fcntl;
        descriptor->exception.number = errno;
        descriptor->status          |= xdescriptorstatus_exception;
        return xfail;
    }
    if(on)
    {
        mask |= O_NONBLOCK;
    }
    else
    {
        mask &= (~O_NONBLOCK);
    }
    if(fcntl(descriptor->handle.f, F_SETFL, mask) != xsuccess)
    {
        descriptor->exception.func   = fcntl;
        descriptor->exception.number = errno;
        descriptor->status          |= xdescriptorstatus_exception;

        return xfail;
    }
    return xsuccess;
}