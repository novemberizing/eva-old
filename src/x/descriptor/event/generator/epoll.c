#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "epoll.h"
#include "subscription/list.h"

#include "../subscription.h"
#include "../../../thread.h"
#include "../../../descriptor.h"
#include "../avail.h"
#include "../dispatch.h"

static xint32 xdescriptoreventgenerator_epoll_open(xdescriptoreventgenerator_epoll * generator);
static xint32 xdescriptoreventgenerator_epoll_close(xdescriptoreventgenerator_epoll * generator);

static xint32 xdescriptoreventgenerator_epoll_add(xdescriptoreventgenerator_epoll * generator, xdescriptoreventsubscription * subscription);
static xint32 xdescriptoreventgenerator_epoll_mod(xdescriptoreventgenerator_epoll * generator, xdescriptoreventsubscription * subscription);
static xint32 xdescriptoreventgenerator_epoll_del(xdescriptoreventgenerator_epoll * generator, xdescriptoreventsubscription * subscription);

extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) calloc(sizeof(xdescriptoreventgenerator_epoll), 1);

    generator->engine      = engine;
    generator->sync        = xnil;
    generator->alive       = xdescriptoreventgeneratorsubscriptionlist_new();
    generator->queue       = xdescriptoreventgeneratorsubscriptionlist_new();
    generator->max         = 1024;
    generator->f           = epoll_create(generator->max);
    generator->millisecond = 1;
    generator->events      = (struct epoll_event *) malloc(sizeof(struct epoll_event) * 1024);

    return (xdescriptoreventgenerator *) generator;
}

extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;
    xassertion(generator == xnil, "");

    if(generator)
    {
        xdescriptoreventgeneratorsubscriptionlist_clear(generator->alive);
        generator->alive  = xdescriptoreventgeneratorsubscriptionlist_rem(generator->alive);

        xdescriptoreventgeneratorsubscriptionlist_clear(generator->queue);
        generator->queue  = xdescriptoreventgeneratorsubscriptionlist_rem(generator->queue);

        generator->events = xobjectrem(generator->events);

        xdescriptoreventgenerator_epoll_close(generator);

        generator->sync = xsyncrem(generator->sync);
    }
    return xnil;
}

extern void xdescriptoreventgenerator_once(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    if(xdescriptoreventgenerator_epoll_open(generator) == xsuccess)
    {
        xdescriptoreventgenerator_queue_once(o);

        xint32 nfds = epoll_wait(generator->f, generator->events, generator->max, generator->millisecond);

        if(nfds >= 0)
        {
            for(xint32 i = 0; i < nfds; i++)
            {
                xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) generator->events[i].data.ptr;

                if(generator->events[i].events & (EPOLLRDHUP | EPOLLPRI | EPOLLERR | EPOLLHUP))
                {
                    xdescriptoreventdispatch_exception(subscription->descriptor, xdescriptoreventgenerator_once, generator->events[i].events, xexceptiontype_descriptor, "");
                }
                else
                {
                    if(generator->events[i].events & EPOLLOUT)
                    {
                        subscription->descriptor->status |= xdescriptorstatus_out;
                        if(subscription->descriptor->status & xdescriptorstatus_connecting)
                        {
                            xdescriptoreventdispatch_connecting(subscription->descriptor);
                        }
                        xdescriptoreventdispatch_out(subscription->descriptor);
                    }
                    if(generator->events[i].events & EPOLLIN)
                    {
                        subscription->descriptor->status |= xdescriptorstatus_in;
                        xdescriptoreventdispatch_in(subscription->descriptor);
                    }
                }

                xdescriptoreventdispatch_void(subscription->descriptor);
            }
        }
        else
        {
            if(errno != EINTR)
            {
                xdescriptoreventgenerator_epoll_close(generator);
            }
        }
    }
    else
    {
        xdescriptoreventgenerator_queue_once(o);
    }
}

extern void xdescriptoreventgenerator_queue_once(xdescriptoreventgenerator * o)
{
    __xsynclock(o->queue->sync);
    xuint64 total = o->queue->size;
    for(xuint64 i = 0; i < total; i++)
    {
        xdescriptoreventsubscription * subscription = xdescriptoreventgeneratorsubscriptionlist_pop(o->queue);
        if(subscription)
        {
            __xsyncunlock(o->queue->sync);
            if(subscription->descriptor->status & xdescriptorstatus_rem)
            {
                xassertion(xdescriptoreventavail_rem(subscription->descriptor) == xfalse, "");

                xdescriptor * descriptor = subscription->descriptor;
                descriptor->process(descriptor, xdescriptoreventtype_rem);
            }
            else
            {
                xassertion(xdescriptoreventavail_open(subscription->descriptor) == xfalse, "");
                xdescriptor * descriptor = subscription->descriptor;

                descriptor->process(descriptor, xdescriptoreventtype_open);
                xdescriptoreventdispatch_void(descriptor);
            }
            __xsynclock(o->queue->sync);
        }
    }
    __xsyncunlock(o->queue->sync);
}

extern xint64 xdescriptoreventgenerator_descriptor_register(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptoreventsubscription * subscription = descriptor->subscription;


    if(subscription->generatornode.list == generator->alive)
    {
        if(descriptor->status & xdescriptorstatus_register)
        {
            if(xdescriptoreventgenerator_epoll_mod(generator, subscription) == xsuccess)
            {
                return xsuccess;
            }
        }
        else
        {
            if(xdescriptoreventgenerator_epoll_add(generator, subscription) == xsuccess)
            {
                return xsuccess;
            }
        }

        xdescriptoreventgeneratorsubscriptionlist_del(subscription);
    }
    else if(subscription->generatornode.list == xnil)
    {
        xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);

        if(xdescriptoreventgenerator_epoll_add(generator, subscription) == xsuccess)
        {
            return xsuccess;
        }
        xdescriptoreventgeneratorsubscriptionlist_del(subscription);
    }
    else
    {
        xassertion(subscription->generatornode.list, "");
    }
    return xfail;
}

extern xint64 xdescriptoreventgenerator_descriptor_update(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptoreventsubscription * subscription = descriptor->subscription;

    xassertion(subscription->generatornode.list != generator->alive, "");

    if(subscription->generatornode.list == generator->alive)
    {
        if(xdescriptoreventgenerator_epoll_mod(generator, subscription) == xsuccess)
        {
            return xsuccess;
        }
        xdescriptoreventgeneratorsubscriptionlist_del(subscription);
    }

    return xfail;
}

extern xint64 xdescriptoreventgenerator_descriptor_unregister(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(subscription->generatornode.list == generator->alive)
    {
        xdescriptoreventgenerator_epoll_del(generator, subscription);
        xdescriptoreventgeneratorsubscriptionlist_del(subscription);
    }
    return xsuccess;
}


extern xint64 xdescriptoreventgenerator_descriptor_dispatch(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xint64 ret = xfail;

    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(xdescriptoreventavail_open(descriptor)==xfalse && xdescriptoreventavail_rem(descriptor) == xfalse, "");
    
    if(xdescriptoreventavail_open(descriptor) || xdescriptoreventavail_rem(descriptor))
    {
        xdescriptoreventsubscription * subscription = descriptor->subscription;

        if(subscription->generatornode.list != generator->alive)
        {
            if(subscription->generatornode.list == xnil)
            {
                xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
            }
            else
            {
                return xsuccess;
            }
        }
        else
        {
            xassertion(xtrue, "");
        }     
    }
    else
    {
        xassertion(xtrue, "");
    }

    return ret;
}

extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(subscription->generatornode.generator != o, "");

    xdescriptor * descriptor = subscription->descriptor;

    subscription->generatornode.generator = o;

    if(xdescriptoreventavail_open(descriptor) || xdescriptoreventavail_rem(descriptor))
    {
        xdescriptoreventgenerator_descriptor_dispatch(o, descriptor);
    }
    else
    {
        xdescriptoreventdispatch_void(subscription->descriptor);
    }
}

extern void xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(subscription->generatornode.generator != o, "");

    xdescriptor * descriptor = subscription->descriptor;

    xdescriptoreventgenerator_descriptor_unregister(o, descriptor);
    if(subscription->generatornode.list)
    {
        xdescriptoreventgeneratorsubscriptionlist_del(subscription);
    }

    subscription->generatornode.generator = xnil;
}


extern void xdescriptoreventgenerator_sync(xdescriptoreventgenerator * o, xint32 on)
{
    if(on)
    {
        if(o->sync == xnil)
        {
            o->sync = xsyncnew(xsynctype_mutex);
        }
        if(o->alive->sync == xnil)
        {
            o->alive->sync = xsyncnew(xsynctype_mutex);
        }
        if(o->queue->sync == xnil)
        {
            o->queue->sync = xsyncnew(xsynctype_mutex);
        }
    }
    else
    {
        o->sync = xsyncrem(o->sync);
        o->alive->sync = xsyncrem(o->alive->sync);
        o->queue->sync = xsyncrem(o->queue->sync);
    }
}

extern void xdescriptoreventgenerator_alive_clear(xdescriptoreventgenerator * o)
{
    xdescriptoreventgeneratorsubscriptionlist_clear(o->alive);
}

extern void xdescriptoreventgenerator_queue_clear(xdescriptoreventgenerator * o)
{
    xdescriptoreventgeneratorsubscriptionlist_clear(o->queue);
}

extern void xdescriptoreventgenerator_on(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll_open((xdescriptoreventgenerator_epoll *) o);
}

extern void xdescriptoreventgenerator_off(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll_close((xdescriptoreventgenerator_epoll *) o);
}

static xint32 xdescriptoreventgenerator_epoll_open(xdescriptoreventgenerator_epoll * generator)
{
    xint32 ret = xfail;

    if(generator->f < 0)
    {
        generator->f = epoll_create(generator->max);

        if(generator->f >= 0)
        {
            __xsynclock(generator->alive->sync);
            xdescriptoreventsubscription * subscription = generator->alive->head;
            while(subscription)
            {
                xdescriptoreventdispatch_void(subscription->descriptor);
            }
            __xsyncunlock(generator->alive->sync);
        }
        else
        {
            xlogcaution("epoll_create(...) => %d", errno);
        }
    }
    else
    {
        ret = xsuccess;
    }

    return ret;
}

static xint32 xdescriptoreventgenerator_epoll_close(xdescriptoreventgenerator_epoll * generator)
{
    if(generator->f >= 0)
    {
        if(close(generator->f) != xsuccess)
        {
            xlogcaution("close(...) => %d", errno);
        }
        generator->f = xinvalid;
        __xsynclock(generator->alive->sync);
        xdescriptoreventsubscription * subscription = generator->alive->head;
        while(subscription)
        {
            subscription->descriptor->status &= (~xdescriptorstatus_register);
            subscription = subscription->generatornode.next;
        }
        __xsyncunlock(generator->alive->sync);
    }

    return xsuccess;
}

static xint32 xdescriptoreventgenerator_epoll_add(xdescriptoreventgenerator_epoll * generator, xdescriptoreventsubscription * subscription)
{
    xint32 ret = xfail;
    if(generator->f >= 0)
    {
        xdescriptor * descriptor = subscription->descriptor;
        xassertion(descriptor->handle.f < 0, "");
        if(descriptor->handle.f >= 0)
        {
            xassertion(descriptor->status & xdescriptorstatus_register, "");
            struct epoll_event event;
            event.events = (EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLET | EPOLLONESHOT);
            event.data.ptr = subscription;
            if(descriptor->status & xdescriptorstatus_connecting)
            {
                event.events |= EPOLLOUT;
            }
            if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
            {
                event.events |= EPOLLOUT;
            }
            if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
            {
                event.events |= EPOLLIN;
            }

            ret = epoll_ctl(generator->f, EPOLL_CTL_ADD, descriptor->handle.f, &event);

            if(ret == xsuccess)
            {
                descriptor->status |= xdescriptorstatus_register;
                xdescriptoron(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xsuccess);
            }
            else
            {
                if(errno == EEXIST)
                {
                    ret = epoll_ctl(generator->f, EPOLL_CTL_MOD, descriptor->handle.f, &event);
                    if(ret == xsuccess)
                    {
                        descriptor->status |= xdescriptorstatus_register;
                        xdescriptoron(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xsuccess);
                    }
                    else
                    {
                        xdescriptoreventdispatch_exception(subscription->descriptor, epoll_ctl, errno, xexceptiontype_sys, "");
                    }
                }
                else
                {
                    xdescriptoreventdispatch_exception(subscription->descriptor, epoll_ctl, errno, xexceptiontype_sys, "");
                }
            }
        }
    }
    else
    {
        // alive 에 등록되어 있다면 자동으로 등록되어지게 된다.
        // 그렇기 때문에, 성공을 출력하도록 하였다.
        ret = xsuccess;
    }
    return ret;
}

static xint32 xdescriptoreventgenerator_epoll_mod(xdescriptoreventgenerator_epoll * generator, xdescriptoreventsubscription * subscription)
{
    xint32 ret = xfail;
    if(generator->f >= 0)
    {
        xdescriptor * descriptor = subscription->descriptor;
        xassertion((descriptor->status & xdescriptorstatus_register) == xdescriptorstatus_void, "");
        if(descriptor->handle.f >= 0)
        {
            struct epoll_event event;
            event.events = (EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLET | EPOLLONESHOT);
            event.data.ptr = subscription;
            if(descriptor->status & xdescriptorstatus_connecting)
            {
                event.events |= EPOLLOUT;
            }
            if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
            {
                event.events |= EPOLLOUT;
            }
            if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
            {
                event.events |= EPOLLIN;
            }
            ret = epoll_ctl(generator->f, EPOLL_CTL_MOD, descriptor->handle.f, &event);
            if(ret == xsuccess)
            {
                descriptor->status |= xdescriptorstatus_register;
                xdescriptoron(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xsuccess);
            }
            else
            {
                if(errno == ENOENT)
                {
                    ret = epoll_ctl(generator->f, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                    if(ret == xsuccess)
                    {
                        descriptor->status |= xdescriptorstatus_register;
                        xdescriptoron(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xsuccess);
                    }
                    else
                    {
                        xdescriptoreventdispatch_exception(subscription->descriptor, epoll_ctl, errno, xexceptiontype_sys, "");
                    }
                }
                else
                {
                    xdescriptoreventdispatch_exception(subscription->descriptor, epoll_ctl, errno, xexceptiontype_sys, "");
                }
            }
        }
    }
    else
    {
        // alive 에 등록되어 있다면 자동으로 등록되어지게 된다.
        // 그렇기 때문에, 성공을 출력하도록 하였다.
        ret = xsuccess;
    }
    return ret;
}

static xint32 xdescriptoreventgenerator_epoll_del(xdescriptoreventgenerator_epoll * generator, xdescriptoreventsubscription * subscription)
{
    if(generator->f >= 0)
    {
        xdescriptor * descriptor = subscription->descriptor;
        if(descriptor->handle.f >= 0)
        {
            if(descriptor->status & xdescriptorstatus_register)
            {
                descriptor->status &= (~xdescriptorstatus_register);
                if(epoll_ctl(generator->f, EPOLL_CTL_DEL, descriptor->handle.f, xnil) != xsuccess)
                {
                    xassertion(xtrue, "");
                }
            }
            else
            {
                if(epoll_ctl(generator->f, EPOLL_CTL_DEL, descriptor->handle.f, xnil) == xsuccess)
                {
                    xassertion(xtrue, "");
                }
                // xassertion(xtrue, "");
            }
        }
    }
    return xsuccess;
}
