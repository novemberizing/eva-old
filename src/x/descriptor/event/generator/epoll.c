#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "epoll.h"
#include "subscription/list.h"

#include "../subscription.h"
#include "../../../thread.h"
#include "../../../descriptor.h"

static inline xint32 xdescriptoreventgenerator_epoll_register(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
{
    xlogfunction_start("%s(%d, %p, %d)", __func__, subscrption, force);

    xassertion(subscrption == xnil || subscrption->descriptor == xnil, "");

    if(epollfd >= 0)
    {
        xdescriptor * descriptor = subscrption->descriptor;

        if(descriptor->handle.f >= 0)
        {
            if(descriptor->status & xdescriptorstatus_exception)
            {
                xlogfunction_end("%s(...) => %d", __func__, xfail);
                return xfail;
            }
            if(descriptor->status & xdescriptorstatus_close)
            {
                xlogfunction_end("%s(...) => %d", __func__, xfail);
                return xfail;
            }
            // 아래의 로직은 고민스럽다.
            if((descriptor->status & xdescriptorstatus_register) == xdescriptorstatus_void || force)
            {
                struct epoll_event event;

                event.data.ptr = subscrption;
                event.events = (EPOLLERR | EPOLLPRI | EPOLLHUP | EPOLLRDHUP | EPOLLONESHOT | EPOLLET);

                if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
                {
                    event.events |= EPOLLOUT;
                }
                if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
                {
                    event.events |= EPOLLIN;
                }

                int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);

                if(force)
                {
                    if(errno == EEXIST)
                    {
                        if(epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event) == xsuccess)
                        {
                            descriptor->status |= xdescriptorstatus_register;
                            xlogfunction_end("%s(...) => %d", __func__, xsuccess);
                            return xsuccess;
                        }
                    }
                }
                if(ret != xsuccess)
                {
                    xexceptionset(xaddressof(descriptor->exception), epoll_ctl, errno, xexceptiontype_system, "");

                    // xdescriptorexception_set(descriptor)
                    xdescriptorevent_dispatch_exception(descriptor);

                    xlogfunction_end("%s(...) => %d", __func__, xfail);
                    return xfail;
                }

                descriptor->status |= xdescriptorstatus_register;

                xlogfunction_end("%s(...) => %d", __func__, xsuccess);
                return xsuccess;
            }
        }
        // TODO: 예외를 발생시킬 때 참조할 수 있는 것을 설정하도록 한다.
        descriptor->status |= xdescriptorstatus_exception;

        xlogfunction_end("%s(...) => %d", __func__, xfail);
        return xfail;
    }

    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}

static inline xint32 xdescriptoreventgenerator_epoll_unregister(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
{
    xlogfunction_start("%s(%d, %p, %d)", __func__, subscrption, force);
    if(epollfd >= 0)
    {
        xdescriptor * descriptor = subscrption->descriptor;
        if(descriptor->handle.f >= 0)
        {
            if((descriptor->status & xdescriptorstatus_register) || force)
            {
                int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);

                descriptor->status &= (~xdescriptorstatus_register);

                xassertion(ret != xsuccess, "");

                ret = (ret == xsuccess ? xsuccess : xexceptionno(errno));
                xlogfunction_end("%s(...) => %d", __func__, ret);
                return ret;
            }
        }
    }
    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}

static inline xint32 xdescriptoreventgenerator_epoll_update(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
{
    xlogfunction_start("%s(%d, %p, %d)", __func__, epollfd, subscrption, force);

    if(epollfd >= 0)
    {
        xdescriptor * descriptor = subscrption->descriptor;
        if(descriptor->handle.f >= 0)
        {
            if(descriptor->status & xdescriptorstatus_exception)
            {
                xlogfunction_end("%s(...) => %d", __func__, xfail);
                return xfail;
            }
            if(descriptor->status & xdescriptorstatus_close)
            {
                xlogfunction_end("%s(...) => %d", __func__, xfail);
                return xfail;
            }
            struct epoll_event event;
            event.data.ptr = subscrption;
            event.events = (EPOLLHUP | EPOLLERR | EPOLLRDHUP | EPOLLPRI | EPOLLET | EPOLLONESHOT);

            if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
            {
                event.events |= EPOLLOUT;
            }
            if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
            {
                event.events |= EPOLLIN;
            }

            if(descriptor->status & xdescriptorstatus_register)
            {
                int ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
                if(ret != xsuccess)
                {
                    if(force)
                    {
                        if(errno == ENOENT)
                        {
                            if(epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event) == xsuccess)
                            {
                                xlogfunction_end("%s(...) => %d", __func__, xsuccess);
                                return xsuccess;
                            }
                        }
                    }
                    if(ret != xsuccess)
                    {
                        descriptor->status |= xdescriptorstatus_exception;
                        descriptor->exception.func = epoll_ctl;
                        descriptor->exception.number = errno;
                        xlogfunction_end("%s(...) => %d", __func__, xfail);
                        return xfail;
                    }
                    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
                    return xsuccess;
                }
                xlogfunction_end("%s(...) => %d", __func__, xsuccess);
                return xsuccess;
            }
            else
            {
                int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                if(ret != xsuccess)
                {
                    if(force)
                    {
                        if(errno == EEXIST)
                        {
                            if(epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event) == xsuccess)
                            {
                                descriptor->status |= xdescriptorstatus_register;
                                xlogfunction_end("%s(...) => %d", __func__, xsuccess);
                                return xsuccess;
                            }
                        }
                    }
                    if(ret != xsuccess)
                    {
                        descriptor->status |= xdescriptorstatus_exception;
                        descriptor->exception.func = epoll_ctl;
                        descriptor->exception.number = errno;
                        xlogfunction_end("%s(...) => %d", __func__, xfail);
                        return xfail;
                    }
                    descriptor->status |= xdescriptorstatus_register;
                    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
                    return xsuccess;
                }
                descriptor->status |= xdescriptorstatus_register;
                xlogfunction_end("%s(...) => %d", __func__, xsuccess);
                return xsuccess;
            }
        }
        xlogfunction_end("%s(...) => %d", __func__, xfail);
        return xfail;
    }
    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}

static inline xint32 xdescriptoreventgenerator_epoll_open(xdescriptoreventgenerator_epoll * generator)
{
    xlogfunction_start("%s(%p)", __func__, generator);
    if(generator->f < 0)
    {
        generator->f = epoll_create(generator->max);

        if(generator->f >= 0)
        {
            __xsynclock(generator->alive->sync);
            xdescriptoreventsubscription * subscription = generator->alive->head;
            while(subscription)
            {
                
                if(subscription->descriptor->handle.f >= 0)
                {
                    if(xdescriptoreventgenerator_epoll_register(generator->f, subscription, xtrue) == xsuccess)
                    {
                        subscription = subscription->generatornode.next;
                        continue;
                    }
                }
                xassertion(xtrue, "implement this");
            }
            __xsyncunlock(generator->alive->sync);
        }
        else
        {
            xassertion(generator->f < 0, "");
            xlogfunction_end("%s(...) => %d", __func__, xfail);
            return xfail;
        }
    }
    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}

extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine)
{
    xlogfunction_start("%s(%p)", __func__, engine);

    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) calloc(sizeof(xdescriptoreventgenerator_epoll), 1);

    generator->alive       = xdescriptoreventgeneratorsubscriptionlist_new();
    generator->queue       = xdescriptoreventgeneratorsubscriptionlist_new();

    generator->engine      = engine;
    generator->f           = xinvalid;
    generator->max         = 1024;
    generator->millisecond = 1;
    generator->events      = (struct epoll_event *) malloc(sizeof(struct epoll_event) * generator->max);

    xlogfunction_end("%s(...) => %p", __func__, generator);
    return (xdescriptoreventgenerator *) generator;
}

extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(generator == xnil || generator->alive->size > 0 || generator->queue->size > 0, "");

    if(generator->f >= 0)
    {
        if(close(generator->f) != xsuccess)
        {
            xassertion(errno, "");
        }
        generator->f = xinvalid;
    }

    generator->events = xobjectrem(generator->events);

    generator->alive  = xdescriptoreventgeneratorsubscriptionlist_rem(generator->alive);
    generator->queue  = xdescriptoreventgeneratorsubscriptionlist_rem(generator->queue);

    xlogfunction_end("%s(...) => %p", __func__, xnil);
    return xnil;
}

extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xlogfunction_start("%s(%p, %p)", __func__, o, subscription);

    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;
    xdescriptor * descriptor = subscription->descriptor;

    if(descriptor->handle.f >= 0)
    {
        xdescriptornonblock_set(descriptor, xtrue);
        if((descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
        {
            if((descriptor->status & xdescriptorstatus_close) == xdescriptorstatus_void)
            {
                if(descriptor->status & xdescriptorstatus_open)
                {
                    int ret = xdescriptoreventgenerator_epoll_register(generator->f, subscription, xfalse);
                    if(ret == xsuccess)
                    {
                        descriptor->on(descriptor, xdescriptoreventtype_register, xnil, xtrue);
                        xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
                    }
                    xlogfunction_end("%s(...)", __func__);
                    return;
                }
            }
        }
    }

    xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
    xlogfunction_end("%s(...)", __func__);
}

extern void xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xlogfunction_start("%s(%p, %p)", __func__, o, subscription);
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptor * descriptor = subscription->descriptor;

    if(descriptor->handle.f >= 0)
    {
        if(descriptor->status & xdescriptorstatus_register)
        {
            xdescriptoreventgenerator_epoll_unregister(generator->f, subscription, xtrue);
            descriptor->on(descriptor, xdescriptoreventtype_register, xnil, xfalse);
        }
    }
    if(subscription->generatornode.list)
    {
        xdescriptoreventgeneratorsubscriptionlist_del(subscription);
    }

    xlogfunction_end("%s(...)", __func__);
}

extern void xdescriptoreventgenerator_once(xdescriptoreventgenerator * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    if(xdescriptoreventgenerator_epoll_open(generator) == xsuccess)
    {
        xdescriptoreventgenerator_queue_once(o);

        int nfds = epoll_wait(generator->f, generator->events, generator->max, generator->millisecond);

        if(nfds >= 0)
        {
            for(int i = 0; i < nfds; i++)
            {
                xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) generator->events[i].data.ptr;

                if(generator->events[i].events & (EPOLLERR | EPOLLPRI | EPOLLRDHUP | EPOLLHUP))
                {
                    xexceptionset(xaddressof(subscription->descriptor->exception), epoll_wait, generator->events[i].events, xexceptiontype_descriptor, ""); 
                    xdescriptorevent_dispatch_exception(subscription->descriptor);
                    continue;
                }
                if(generator->events[i].events & EPOLLOUT)
                {
                    xdescriptorevent_dispatch_out(subscription->descriptor);
                }
                if(generator->events[i].events & EPOLLIN)
                {
                    xdescriptorevent_dispatch_in(subscription->descriptor);
                }
            }
        }
        else
        {
            if(errno != EINTR)
            {
                int ret = close(generator->f);
                xassertion(ret != xsuccess, "");
                generator->f = xinvalid;
            }
        }
    }

    xlogfunction_end("%s(...)", __func__);
}

extern void xdescriptoreventgenerator_queue_once(xdescriptoreventgenerator * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    __xsynclock(generator->queue->sync);
    xuint64 total = generator->queue->size;
    for(xuint64 i = 0; i < total; i++)
    {
        xdescriptoreventsubscription * subscription = xdescriptoreventgeneratorsubscriptionlist_pop(generator->queue);
        if(subscription)
        {
            __xsyncunlock(generator->queue->sync);

            xdescriptor * descriptor = subscription->descriptor;
            if(descriptor->status & (xdescriptorstatus_exception | xdescriptorstatus_close | xdescriptorstatus_rem))
            {
                xassertion(descriptor->status & xdescriptorstatus_register, "");
                if(descriptor->handle.f >= 0)
                {
                    xassertion(descriptor->status & xdescriptorstatus_close, "");
                    xdescriptorevent_processor_close(descriptor);
                }

                if(descriptor->status & xdescriptorstatus_rem)
                {
                    xdescriptorevent_processor_rem(descriptor);
                    // TODO: CHECK GENERATOR QUEUE SIZE
                }
                __xsynclock(generator->queue->sync);
                continue;
            }
            
            if(xdescriptorevent_processor_open(descriptor) == xsuccess)
            {
                __xsynclock(generator->alive->sync);
                xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
                __xsyncunlock(generator->alive->sync);
                if(xdescriptorevent_processor_register(descriptor) >= 0)
                {
                    __xsynclock(generator->queue->sync);
                    continue;
                }
                if(subscription->generatornode.list)
                {
                    xdescriptoreventgeneratorsubscriptionlist_del(subscription);
                }
            }
            __xsynclock(generator->queue->sync);
            xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
            continue;
        }
        break;
    }
    __xsyncunlock(generator->queue->sync);

    xlogfunction_end("%s(...)", __func__);
}

extern void xdescriptoreventgenerator_sync(xdescriptoreventgenerator * o, xint32 on)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, on);
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    if(on)
    {
        if(generator->alive->sync)
        {
            generator->alive->sync = xsyncnew(xsynctype_default);
        }
        if(generator->queue->sync)
        {
            generator->queue->sync = xsyncnew(xsynctype_default);
        }
        
    }
    else
    {
        generator->alive->sync = xsyncrem(generator->alive->sync);
        generator->queue->sync = xsyncrem(generator->queue->sync);
    }

    xlogfunction_end("%s(...)", __func__);
}

extern void xdescriptoreventgenerator_on(xdescriptoreventgenerator * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptoreventgenerator_epoll_open(generator);

    xlogfunction_end("%s(...)", __func__);
}

extern void xdescriptoreventgenerator_off(xdescriptoreventgenerator * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    if(generator->f)
    {
        int ret = close(generator->f);
        xassertion(ret != xsuccess, "");
        generator->f = xinvalid;
    }

    generator->events = xobjectrem(generator->events);
    // alive session unregister set

    xdescriptoreventgenerator_alive_clear(o);
    xdescriptoreventgenerator_queue_clear(o);

    xlogfunction_end("%s(...)", __func__);
}

extern void xdescriptoreventgenerator_alive_clear(xdescriptoreventgenerator * generator)
{
    xlogfunction_start("%s(%p)", __func__, generator);

    xdescriptoreventsubscription * subscription = generator->alive->head;
    while(subscription)
    {
        xdescriptoreventsubscription * next = xdescriptoreventgeneratorsubscriptionlist_pop(generator->alive);

        xdescriptor * descriptor = subscription->descriptor;
        descriptor->status &= (~xdescriptorstatus_register);
        descriptor->on(descriptor, xdescriptoreventtype_register, xnil, xfalse);

        subscription->generatornode.generator = xnil;
        
        subscription = next;
    }

    xlogfunction_end("%s(...)", __func__);
}

extern void xdescriptoreventgenerator_queue_clear(xdescriptoreventgenerator * generator)
{
    xlogfunction_start("%s(%p)", __func__, generator);
    xdescriptoreventsubscription * subscription = generator->alive->head;
    while(subscription)
    {
        xdescriptoreventsubscription * next = xdescriptoreventgeneratorsubscriptionlist_pop(generator->alive);

        xdescriptor * descriptor = subscription->descriptor;

        subscription->generatornode.generator = xnil;
        
        subscription = next;
    }

    xlogfunction_end("%s(...)", __func__);
}

extern xint64 xdescriptoreventgenerator_descriptor_update(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p, %p)", __func__, o, descriptor);
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptoreventsubscription * subscription = descriptor->subscription;

    xassertion(o != subscription->generatornode.generator, "");
    xassertion(descriptor->handle.f < 0, "");
    xassertion(generator->alive != subscription->generatornode.list, "");

    xint64 ret = xdescriptoreventgenerator_epoll_update(generator->f, subscription, xtrue);

    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

extern xint64 xdescriptoreventgenerator_descriptor_unregister(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p, %p)", __func__, o, descriptor);

    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptoreventsubscription * subscription = descriptor->subscription;

    xassertion(o != subscription->generatornode.generator, "");
    xassertion(descriptor->handle.f < 0, "");
    xassertion(generator->alive != subscription->generatornode.list, "");

    if(xdescriptoreventgenerator_epoll_unregister(generator->f, subscription, xtrue) == xsuccess)
    {
        descriptor->on(descriptor, xdescriptoreventtype_register, xnil, xtrue);
    }

    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    // TODO: IMPLEMENT LOGIC
    return xsuccess;
}
