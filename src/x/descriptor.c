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

static xint64 xdescriptoron(xdescriptor * descriptor, xuint32 event, void * param, xint64 result)
{
    if(event == xdescriptoreventtype_exception)
    {
        result = descriptor->on(descriptor, event, param, result);
    }
    else
    {
        result = descriptor->on(descriptor, event, param, result);
        if(result < 0)
        {
            descriptor->status |= xdescriptorstatus_exception;
            result = descriptor->on(descriptor, xdescriptoreventtype_exception, xaddressof(descriptor->exception), result);
        }
    }
    return result;
}

static xint32 xdescriptorstatuscheck_open(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_in(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_out(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_close(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_exception(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_rem(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_register(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_readoff(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_writeoff(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_alloff(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_opening(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_create(xdescriptor * descriptor);
static xint32 xdescriptorstatuscheck_bind(xdescriptor * descriptor);

static xint64 xdescriptoreventprocess_void(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_open(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_in(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_out(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_close(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_exception(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_rem(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_register(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_readoff(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_writeoff(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_opening(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_create(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_bind(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_alloff(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_connect(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_listen(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_connecting(xdescriptor * descriptor);
static xint64 xdescriptoreventprocess_unregister(xdescriptor * descriptor);

extern xint64 xdescriptorclose(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor == xnil, "");

    if(descriptor->handle.f > xdescriptorsystemno_max)
    {
        if(close(descriptor->handle.f) != xsuccess)
        {
            xlogcaution("close(%d) => fail (%d)", descriptor->handle.f, errno);
        }
        descriptor->status |= xdescriptorstatus_close;
        descriptor->handle.f = xinvalid;
        xdescriptoron(descriptor, xdescriptoreventtype_close, xnil, xsuccess);
    }

    xlogfunction_end("%s(...) => %ld", xsuccess);
    return xsuccess;
}

extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, descriptor, buffer, size);

    xassertion(descriptor == xnil, "");

    xint64 n = xfail;

    if(xdescriptorstatuscheck_in(descriptor))
    {
        if(buffer && size)
        {
            n = read(descriptor->handle.f, buffer, size);

            if(n > 0)
            {
                descriptor->status |= xdescriptorstatus_in;
                n = xdescriptoron(descriptor, xdescriptoreventtype_in, buffer, n);
            }
            else if(n == 0)
            {
                // N IS ZERO => END OF FILE
                descriptor->status &= (~xdescriptorstatus_in);
                n = xdescriptoron(descriptor, xdescriptoreventtype_in, buffer, n);
            }
            else
            {
                if(errno != EAGAIN)
                {
                    xexceptionset(xaddressof(descriptor->exception), read, errno, xexceptiontype_system, "");
                    descriptor->status |= xdescriptorstatus_exception;
                    n = xdescriptoron(descriptor, xdescriptoreventtype_exception, xnil, n);
                }
                else
                {
                    descriptor->status &= (~xdescriptorstatus_in);
                    n = xsuccess;
                }
            }
        }
        else
        {
            xlogcaution("buffer: %p, size: %lu", buffer, size);
            n = xsuccess;
        }
    }
    else
    {
        n = xdescriptorstatuscheck_close(descriptor) ? xfail : xsuccess;
    }

    xlogfunction_end("%s(...) => %ld", n);
    return n;
}

extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, descriptor, data, len);

    xassertion(descriptor == xnil, "");

    xint64 n = xfail;
    if(xdescriptorstatuscheck_out(descriptor))
    {
        if(data && len)
        {
            n = write(descriptor->handle.f, data, len);

            if(n > 0)
            {
                descriptor->status |= xdescriptorstatus_out;
                n = xdescriptoron(descriptor, xdescriptoreventtype_out, xnil, n);
            }
            else if(n == 0)
            {
                // 이 부분에 대해서 고민을 더 해보자.
                xassertion(xtrue, "");
            }
            else
            {
                if(errno != EAGAIN)
                {
                    xexceptionset(xaddressof(descriptor->exception), read, errno, xexceptiontype_system, "");
                    descriptor->status |= xdescriptorstatus_exception;
                    n = xdescriptoron(descriptor, xdescriptoreventtype_exception, xnil, n);
                }
                else
                {
                    descriptor->status &= (~xdescriptorstatus_out);
                    n = xsuccess;
                }
            }
        }
        else
        {
            xlogcaution("data: %p, size: %lu", data, len);
            n = xsuccess;
        }
    }
    else
    {
        n = xdescriptorstatuscheck_close(descriptor) ? xfail : xsuccess;
    }

    return n;
}

extern xint32 xdescriptorstatuscheck(xdescriptor * descriptor, xuint32 status)
{
    xint32 ret = xfalse;

    switch(status)
    {
        case xdescriptorstatus_void:        xassertion(xtrue, "");                              break;
        case xdescriptorstatus_open:        ret = xdescriptorstatuscheck_open(descriptor);      break;
        case xdescriptorstatus_in:          ret = xdescriptorstatuscheck_in(descriptor);        break;
        case xdescriptorstatus_out:         ret = xdescriptorstatuscheck_out(descriptor);       break;
        case xdescriptorstatus_close:       ret = xdescriptorstatuscheck_close(descriptor);     break;
        case xdescriptorstatus_exception:   ret = xdescriptorstatuscheck_exception(descriptor); break;
        case xdescriptorstatus_rem:         ret = xdescriptorstatuscheck_rem(descriptor);       break;
        case xdescriptorstatus_register:    ret = xdescriptorstatuscheck_register(descriptor);  break;
        case xdescriptorstatus_readoff:     ret = xdescriptorstatuscheck_readoff(descriptor);   break;
        case xdescriptorstatus_writeoff:    ret = xdescriptorstatuscheck_writeoff(descriptor);  break;
        case xdescriptorstatus_opening:     ret = xdescriptorstatuscheck_opening(descriptor);   break;
        case xdescriptorstatus_create:      ret = xdescriptorstatuscheck_create(descriptor);    break;
        case xdescriptorstatus_bind:        ret = xdescriptorstatuscheck_bind(descriptor);      break;
        case xdescriptorstatus_alloff:      ret = xdescriptorstatuscheck_alloff(descriptor);    break;
        default:                            xassertion(xtrue, "");                              break;
    }

    return ret;
}

extern xint64 xdescriptoreventdispatch(xdescriptor * descriptor, xuint32 event)
{
    xint64 ret = xsuccess;

    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(subscription)
    {
        if(xeventengine_descriptor_dispatch(descriptor, event) != xsuccess)
        {
            ret = xdescriptoreventprocess(descriptor, xdescriptoreventtype_void);
        }
    }
    else
    {
        ret = xdescriptoreventprocess(descriptor, event);
    }

    return ret;
}

extern xint64 xdescriptorevent_process(xdescriptor * descriptor, xuint32 event)
{
    xint64 ret = xfail;
    switch(event)
    {
        case xdescriptoreventtype_void:         ret = xdescriptoreventprocess_void(descriptor);         break;
        case xdescriptoreventtype_open:         ret = xdescriptoreventprocess_open(descriptor);         break;
        case xdescriptoreventtype_in:           ret = xdescriptoreventprocess_in(descriptor);           break;
        case xdescriptoreventtype_out:          ret = xdescriptoreventprocess_out(descriptor);          break;
        case xdescriptoreventtype_close:        ret = xdescriptoreventprocess_close(descriptor);        break;
        case xdescriptoreventtype_exception:    ret = xdescriptoreventprocess_exception(descriptor);    break;
        case xdescriptoreventtype_rem:          ret = xdescriptoreventprocess_rem(descriptor);          break;
        case xdescriptoreventtype_register:     ret = xdescriptoreventprocess_register(descriptor);     break;
        case xdescriptoreventtype_readoff:      ret = xdescriptoreventprocess_readoff(descriptor);      break;
        case xdescriptoreventtype_writeoff:     ret = xdescriptoreventprocess_writeoff(descriptor);     break;
        case xdescriptoreventtype_opening:      ret = xdescriptoreventprocess_opening(descriptor);      break;
        case xdescriptoreventtype_create:       ret = xdescriptoreventprocess_create(descriptor);       break;
        case xdescriptoreventtype_bind:         ret = xdescriptoreventprocess_bind(descriptor);         break;
        case xdescriptoreventtype_alloff:       ret = xdescriptoreventprocess_alloff(descriptor);       break;

        default:                                xassertion(xtrue, "");                                  break;
    }
    return ret;
}

extern xint32 xdescriptornonblock_set(xdescriptor * descriptor, xint32 on)
{
    xlogfunction_start("%s(%p, %d)", __func__, descriptor, on);

    xassertion(descriptor == xnil || descriptor->handle.f < 0, "");

    int mask = fcntl(descriptor->handle.f, F_GETFL, 0);
    if(mask < 0)
    {
        descriptor->status |= xdescriptorstatus_exception;
        xexceptionset(xaddressof(descriptor->exception), fcntl, errno, xexceptiontype_system, "");
        xdescriptoron(descriptor, xdescriptoreventtype_exception, xaddressof(descriptor->exception), xfail);

        xlogfunction_end("%s(...) => %d", __func__, xfail);
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
        descriptor->status |= xdescriptorstatus_exception;
        xexceptionset(xaddressof(descriptor->exception), fcntl, errno, xexceptiontype_system, "");
        xdescriptoron(descriptor, xdescriptoreventtype_exception, xaddressof(descriptor->exception), xfail);

        xlogfunction_end("%s(...) => %d", __func__, xfail);
        return xfail;
    }

    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}

static xint32 xdescriptorstatuscheck_open(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    if(descriptor->status & xdescriptorstatus_open)
    {
        if(descriptor->handle.f >= 0)
        {
            return xtrue;
        }
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_in(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_open(descriptor))
    {
        if(descriptor->status & xdescriptorstatus_readoff)
        {
            return xfalse;
        }
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_out(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_open(descriptor))
    {
        if(descriptor->status & xdescriptorstatus_writeoff)
        {
            return xfalse;
        }
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_close(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_exception | xdescriptorstatus_rem))
    {
        return xtrue;
    }
    if((descriptor->status & xdescriptorstatus_alloff) == xdescriptorstatus_alloff)
    {
        return xtrue;
    }
    if(descriptor->handle.f < 0)
    {
        return xtrue;
    }
    return xfalse;
}
static xint32 xdescriptorstatuscheck_exception(xdescriptor * descriptor)
{
    if(descriptor->status & xdescriptorstatus_exception)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_rem(xdescriptor * descriptor)
{
    if((descriptor->status & xdescriptorstatus_rem) == xdescriptorstatus_void)
    {
        return xfalse;
    }
    if(descriptor->handle.f >= 0)
    {
        return xfalse;
    }
    if(descriptor->event.queue)
    {
        return xfalse;
    }
    if(descriptor->status & xdescriptorstatus_register)
    {
        return xfalse;
    }
    if(descriptor->subscription->enginenode.engine)
    {
        return xfalse;
    }
    if(descriptor->subscription->generatornode.generator)
    {
        return xfalse;
    }
    if(descriptor->subscription->generatornode.list)
    {
        return xfalse;
    }
    return xtrue;
}

static xint32 xdescriptorstatuscheck_register(xdescriptor * descriptor)
{
    if(descriptor->status & xdescriptorstatus_register)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_readoff(xdescriptor * descriptor)
{
    if(descriptor->status & xdescriptorstatus_readoff)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_writeoff(xdescriptor * descriptor)
{
    if(descriptor->status & xdescriptorstatus_writeoff)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_alloff(xdescriptor * descriptor)
{
    if((descriptor->status & xdescriptorstatus_alloff) == xdescriptorstatus_alloff);
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_opening(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    if(descriptor->status & xdescriptorstatus_opening)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_create(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    if(descriptor->status & xdescriptorstatus_create)
    {
        return xtrue;
    }
    return xfalse;
}

static xint32 xdescriptorstatuscheck_bind(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    if(descriptor->status & xdescriptorstatus_bind)
    {
        return xtrue;
    }
    return xfalse;
}

static xint64 xdescriptoreventprocess_void(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor == xnil, "");

    if(xdescriptorstatuscheck_close(descriptor))
    {
        xdescriptoreventprocess_unregister(descriptor);
        xint64 ret = xdescriptoreventprocess_close(descriptor);

        xlogfunction_end("%s(...) => %d", __func__, ret);
        return ret;
    }
    if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
    {
        if((descriptor->status & xdescriptorstatus_opening) == xdescriptorstatus_void)
        {
            xdescriptoreventprocess_open(descriptor);
        }
        else
        {
            xdescriptoreventprocess_opening(descriptor);
        }
    }

    xdescriptoreventprocess_out(descriptor);
    xdescriptoreventprocess_in(descriptor);
    xdescriptoreventprocess_out(descriptor);

    if(xdescriptorstatuscheck_close(descriptor) == xfalse)
    {
        if((descriptor->status & (xdescriptorstatus_in | xdescriptorstatus_out)) != (xdescriptorstatus_in | xdescriptorstatus_out))
        {
            xdescriptoreventprocess_register(descriptor);
        }
    }

    if(xdescriptorstatuscheck_close(descriptor))
    {
        xdescriptoreventprocess_unregister(descriptor);
        xdescriptoreventprocess_close(descriptor);
        xlogfunction_end("%s(...) => %d", __func__, xfail);
        return xfail;
    }

    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}

static xint64 xdescriptoreventprocess_open(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_open, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_in(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_in, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_out(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_out, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_close(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");
    xassertion(descriptor->event.queue, "");
    xassertion(descriptor->status & xdescriptorstatus_register, "");

    xdescriptoreventsubscription *  subscription = descriptor->subscription;
    if(subscription)
    {
        xdescriptoreventgenerator * generator = subscription->generatornode.generator;
        if(subscription->generatornode.list == generator->alive)
        {
            xdescriptoreventgeneratorsubscriptionlist_del(descriptor->subscription);
        }
        descriptor->process(descriptor, xdescriptoreventtype_close, xnil);

        descriptor->exception = xexception_void;
        descriptor->status    = (descriptor->status & xdescriptorstatus_rem) ? xdescriptorstatus_rem : xdescriptorstatus_void;

        if(subscription->generatornode.list != generator->queue)
        {
            xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
        }
    }
    else
    {
        descriptor->process(descriptor, xdescriptoreventtype_close, xnil);
    }

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

static xint64 xdescriptoreventprocess_exception(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_exception, xnil);

    n = xdescriptoreventprocess_close(descriptor);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_rem(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);
    if(xdescriptorstatuscheck_rem(descriptor))
    {
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        if(subscription)
        {
            xeventengine * engine = subscription->enginenode.engine;
            xeventengine_descriptor_unregister(engine, descriptor);

            // TODO: CHECK SUBSCRIPTION
            xassertion(subscription->enginenode.engine || subscription->enginenode.prev || subscription->enginenode.next, "");
            xassertion(subscription->generatornode.prev || subscription->generatornode.next || subscription->generatornode.list, "");

            descriptor->subscription = xnil;
            descriptor->process(descriptor, xdescriptoreventtype_rem, xnil);
            free(subscription);
        }
        else
        {
            descriptor->process(descriptor, xdescriptoreventtype_rem, xnil);
        }
    }
    else
    {
        xassertion((descriptor->status & xdescriptorstatus_rem) == xdescriptorstatus_void, "");
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        xdescriptoreventgenerator * generator = subscription->generatornode.generator;
        xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
    }
    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

static xint64 xdescriptoreventprocess_register(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);
    if(xdescriptorstatuscheck_open(descriptor))
    {
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        xdescriptoreventgenerator * generator = subscription->generatornode.generator;
        xint64 n = xdescriptoreventgenerator_descriptor_update(generator, descriptor);
        n = descriptor->on(descriptor, xdescriptoreventtype_register, xnil, n == xsuccess);
        xlogfunction_end("%s(...) => %ld", __func__, n);
        return n;
    }
    else if(xdescriptorstatuscheck_close(descriptor) == xfalse && (descriptor->status & xdescriptorstatus_opening))
    {
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        xdescriptoreventgenerator * generator = subscription->generatornode.generator;
        xint64 n = xdescriptoreventgenerator_descriptor_update(generator, descriptor);
        n = descriptor->on(descriptor, xdescriptoreventtype_register, xnil, n == xsuccess);
        xlogfunction_end("%s(...) => %ld", __func__, n);
        return n;
    }

    xlogfunction_end("%s(...) => %ld", __func__, xfail);
    return xfail;
}

static xint64 xdescriptoreventprocess_readoff(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_readoff, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_writeoff(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_writeoff, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_opening(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_opening, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_create(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_create, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_bind(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_bind, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_alloff(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_alloff, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_connect(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_connect, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_listen(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_listen, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_connecting(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->process == xnil, "");

    xint64 n = descriptor->process(descriptor, xdescriptoreventtype_connecting, xnil);

    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

static xint64 xdescriptoreventprocess_unregister(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xdescriptoreventsubscription * subscription = descriptor->subscription;
    xdescriptoreventgenerator * generator = subscription->generatornode.generator;
    xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
    descriptor->on(descriptor, xdescriptoreventtype_register, xnil, xfalse);

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

extern xuint32 xdescriptorstatus_get(xdescriptor * descriptor)
{
    return descriptor->status;
}

extern xdescriptoreventsubscription * xdescriptoreventsubscription_get(xdescriptor * descriptor)
{
    return descriptor->subscription;
}
