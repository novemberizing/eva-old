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

static xint32 xdescriptoreventgenerator_epoll_open(xdescriptoreventgenerator_epoll * generator);
static xint32 xdescriptoreventgenerator_epoll_close(xdescriptoreventgenerator_epoll * generator);

extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) calloc(sizeof(xdescriptoreventgenerator_epoll), 1);

    generator->alive       = xdescriptoreventgeneratorsubscriptionlist_new();
    generator->queue       = xdescriptoreventgeneratorsubscriptionlist_new();
    generator->engine      = engine;
    generator->sync        = xnil;
    generator->f           = xinvalid;
    generator->max         = 1024;
    generator->millisecond = 1;
    generator->events      = (struct epoll_event *) malloc(sizeof(struct epoll_event) * generator->max);

    return (xdescriptoreventgenerator *) generator;
}

extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(generator == xnil, "");

    if(generator)
    {
        generator->alive = xdescriptoreventgeneratorsubscriptionlist_rem(generator->alive);
        generator->queue = xdescriptoreventgeneratorsubscriptionlist_rem(generator->queue);

        if(generator->f >= 0)
        {
            if(close(generator->f) != xsuccess)
            {
                xlogcaution("%d", errno);
            }
            generator->f = xinvalid;
        }

        generator->events = xobjectrem(generator->events);

        free(generator);
    }

    return xnil;
}

extern void xdescriptoreventgenerator_once(xdescriptoreventgenerator * o)
{
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
                    subscription->descriptor->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(subscription->descriptor->exception), epoll_wait, generator->events[i].events, xexceptiontype_sys, "");
                    xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_exception);
                }
                if(generator->events[i].events & EPOLLOUT)
                {
                    subscription->descriptor->status |= xdescriptorstatus_out;
                    if(subscription->descriptor->status & xdescriptorstatus_connecting)
                    {
                        xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_connecting);
                    }
                    xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_out);
                }
                if(generator->events[i].events & EPOLLIN)
                {
                    subscription->descriptor->status |= xdescriptorstatus_in;
                    xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_in);
                }

                xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_void);
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
            if(descriptor->status & xdescriptorstatus_rem)
            {
                xassertion(xdescriptoreventavail_rem(descriptor) == xfalse, "");

                descriptor->process(descriptor, xdescriptoreventtype_rem);
            }
            else
            {
                xassertion(xdescriptoreventavail_open(descriptor) == xfalse, "");

                descriptor->process(descriptor, xdescriptoreventtype_open);

                xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_void);
            }
            __xsynclock(generator->queue->sync);
            continue;
        }
        break;
    }

    __xsyncunlock(generator->queue->sync);
}

extern xint64 xdescriptoreventgenerator_descriptor_register(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xint64 ret = xfail;

    if(xdescriptorstatuscheck_open(descriptor))
    {
        if(generator->f >= 0)
        {
            if(descriptor->status & xdescriptorstatus_register)
            {
                ret = xdescriptoreventgenerator_epoll_mod(generator->f, descriptor->subscription);
            }
            else
            {
                ret = xdescriptoreventgenerator_epoll_add(generator->f, descriptor->subscription);
            }
        }

        xassertion(descriptor->subscription && (generator->alive != descriptor->subscription->generatornode.list), "");
    }

    return ret;
}

extern xint64 xdescriptoreventgenerator_descriptor_update(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xint64 ret = xfail;

    if(xdescriptorstatuscheck_open(descriptor))
    {
        if(generator->f >= 0)
        {
            if(descriptor->status & xdescriptorstatus_register)
            {
                ret = xdescriptoreventgenerator_epoll_mod(generator->f, descriptor->subscription);
            }
            else
            {
                ret = xdescriptoreventgenerator_epoll_add(generator->f, descriptor->subscription);
            }
        }

        xassertion(descriptor->subscription && (generator->alive != descriptor->subscription->generatornode.list), "");
    }

    return ret;
}

extern xint64 xdescriptoreventgenerator_descriptor_unregister(xdescriptoreventgenerator * o, xdescriptor * descriptor)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;
    xassertion(xtrue, "");
}

static xint32 xdescriptoreventgenerator_epoll_open(xdescriptoreventgenerator_epoll * generator)
{
    xassertion(generator == xnil, "");

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
                xdescriptoreventsubscription * next = subscription->generatornode.next;
                subscription->descriptor->status &= (~xdescriptorstatus_register);
                subscription->descriptor->status |= xdescriptorstatus_out;

                xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_void);

                subscription = next;
            }
            __xsyncunlock(generator->alive->sync);
            ret = xsuccess;
        }
        else
        {
            xassertion(xtrue, "");
            ret = xfail;
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
    xint32 ret = xfail;

    if(generator->f >= 0)
    {
        if(close(generator->f) != xsuccess)
        {
            xassertion(xtrue, "");
        }
        generator->f = xinvalid;
    }

    __xsynclock(generator->alive->sync);
    xdescriptoreventsubscription * subscription = generator->alive->head;
    while(subscription)
    {
        subscription->descriptor->status &= (~xdescriptorstatus_register);
        xdescriptoron(subscription->descriptor, xdescriptoreventtype_unregister, xdescriptorparamgen(xnil), xsuccess);
        subscription = subscription->generatornode.next;
    }
    __xsyncunlock(generator->alive->sync);

    return ret;
}

extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;
    xdescriptor * descriptor = subscription->descriptor;

    xassertion(descriptor->subscription->generatornode.list, "");

    if(xdescriptorstatuscheck_open(descriptor))
    {
        xdescriptornonblock(descriptor, xtrue);

        xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
        xdescriptoreventdispatch(descriptor, xdescriptoreventtype_void);
    }
    else
    {
        if(xdescriptoreventavail_open(descriptor) || xdescriptoreventavail_rem(descriptor))
        {
            xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
        }
        else
        {
            xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
            xdescriptoreventdispatch(descriptor, xdescriptoreventtype_void);
        }
    }
}

extern void xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptor * descriptor = subscription->descriptor;

    if(descriptor->handle.f >= 0)
    {
        if(descriptor->status & xdescriptorstatus_register)
        {
            xdescriptoreventgenerator_epoll_del(generator->f, subscription);
        }
    }

    return xsuccess;

//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     xdescriptor * descriptor = subscription->descriptor;

//     if(descriptor->handle.f >= 0)
//     {
//         if(descriptor->status & xdescriptorstatus_register)
//         {
//             xdescriptoreventgenerator_epoll_unregister(generator->f, subscription, xtrue);
//             descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xfalse);
//         }
//     }
//     if(subscription->generatornode.list)
//     {
//         xdescriptoreventgeneratorsubscriptionlist_del(subscription);
//     }
}


// extern xint64 xdescriptoreventgenerator_descriptor_register(xdescriptoreventgenerator * o, xdescriptor * descriptor)
// {
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;
//     xassertion(generator == xnil, "");
// }

// extern xint64 xdescriptoreventgenerator_descriptor_update(xdescriptoreventgenerator * o, xdescriptor * descriptor);
// extern xint64 xdescriptoreventgenerator_descriptor_unregister(xdescriptoreventgenerator * o, xdescriptor * descriptor);


// static xint32 xdescriptoreventgenerator_epoll_register(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
// {
//     xlogfunction_start("%s(%d, %p, %d)", __func__, subscrption, force);

//     xassertion(subscrption == xnil || subscrption->descriptor == xnil, "");

//     if(epollfd >= 0)
//     {
//         xdescriptor * descriptor = subscrption->descriptor;

//         if(descriptor->handle.f >= 0)
//         {
//             if(descriptor->status & xdescriptorstatus_exception)
//             {
//                 xlogfunction_end("%s(...) => %d", __func__, xfail);
//                 return xfail;
//             }
//             if(descriptor->status & xdescriptorstatus_close)
//             {
//                 xlogfunction_end("%s(...) => %d", __func__, xfail);
//                 return xfail;
//             }
//             // 아래의 로직은 고민스럽다.
//             if((descriptor->status & xdescriptorstatus_register) == xdescriptorstatus_void || force)
//             {
//                 struct epoll_event event;

//                 event.data.ptr = subscrption;
//                 event.events = (EPOLLERR | EPOLLPRI | EPOLLHUP | EPOLLRDHUP | EPOLLONESHOT | EPOLLET);

//                 if(descriptor->status & xdescriptorstatus_connecting)
//                 {
//                     event.events |= EPOLLOUT;
//                 }
//                 else
//                 {
//                     if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
//                     {
//                         event.events |= EPOLLOUT;
//                     }
//                     if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
//                     {
//                         event.events |= EPOLLIN;
//                     }
//                 }

//                 int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);

//                 if(force)
//                 {
//                     if(errno == EEXIST)
//                     {
//                         if(epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event) == xsuccess)
//                         {
//                             descriptor->status |= xdescriptorstatus_register;
//                             xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//                             return xsuccess;
//                         }
//                     }
//                 }
//                 if(ret != xsuccess)
//                 {
//                     xexceptionset(xaddressof(descriptor->exception), epoll_ctl, errno, xexceptiontype_sys, "");

//                     // xdescriptorexception_set(descriptor)
//                     xdescriptoreventdispatch(descriptor, xdescriptoreventtype_exception);

//                     xlogfunction_end("%s(...) => %d", __func__, xfail);
//                     return xfail;
//                 }

//                 descriptor->status |= xdescriptorstatus_register;

//                 xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//                 return xsuccess;
//             }
//         }
//         // TODO: 예외를 발생시킬 때 참조할 수 있는 것을 설정하도록 한다.
//         descriptor->status |= xdescriptorstatus_exception;

//         xlogfunction_end("%s(...) => %d", __func__, xfail);
//         return xfail;
//     }

//     xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//     return xsuccess;
// }

// static inline xint32 xdescriptoreventgenerator_epoll_unregister(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
// {
//     xlogfunction_start("%s(%d, %p, %d)", __func__, subscrption, force);
//     if(epollfd >= 0)
//     {
//         xdescriptor * descriptor = subscrption->descriptor;
//         if(descriptor->handle.f >= 0)
//         {
//             if((descriptor->status & xdescriptorstatus_register) || force)
//             {
//                 int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);

//                 descriptor->status &= (~xdescriptorstatus_register);

//                 xassertion(ret != xsuccess, "");

//                 ret = (ret == xsuccess ? xsuccess : xexceptionno(errno));
//                 xlogfunction_end("%s(...) => %d", __func__, ret);
//                 return ret;
//             }
//         }
//     }
//     xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//     return xsuccess;
// }

// static inline xint32 xdescriptoreventgenerator_epoll_update(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
// {
//     xlogfunction_start("%s(%d, %p, %d)", __func__, epollfd, subscrption, force);

//     if(epollfd >= 0)
//     {
//         xdescriptor * descriptor = subscrption->descriptor;
//         if(descriptor->handle.f >= 0)
//         {
//             if(descriptor->status & xdescriptorstatus_exception)
//             {
//                 xlogfunction_end("%s(...) => %d", __func__, xfail);
//                 return xfail;
//             }
//             if(descriptor->status & xdescriptorstatus_close)
//             {
//                 xlogfunction_end("%s(...) => %d", __func__, xfail);
//                 return xfail;
//             }
//             struct epoll_event event;
//             event.data.ptr = subscrption;
//             event.events = (EPOLLHUP | EPOLLERR | EPOLLRDHUP | EPOLLPRI | EPOLLET | EPOLLONESHOT);

//             if(descriptor->status & xdescriptorstatus_connecting)
//             {
//                 event.events |= EPOLLOUT;
//             }
//             else
//             {
//                 if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
//                 {
//                     event.events |= EPOLLOUT;
//                 }
//                 if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
//                 {
//                     event.events |= EPOLLIN;
//                 }
//             }

//             if(descriptor->status & xdescriptorstatus_register)
//             {
//                 int ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
//                 if(ret != xsuccess)
//                 {
//                     if(force)
//                     {
//                         if(errno == ENOENT)
//                         {
//                             if(epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event) == xsuccess)
//                             {
//                                 xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//                                 return xsuccess;
//                             }
//                         }
//                     }
//                     if(ret != xsuccess)
//                     {
//                         descriptor->status |= xdescriptorstatus_exception;
//                         descriptor->exception.func = epoll_ctl;
//                         descriptor->exception.number = errno;
//                         xlogfunction_end("%s(...) => %d", __func__, xfail);
//                         return xfail;
//                     }
//                     xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//                     return xsuccess;
//                 }
//                 xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//                 return xsuccess;
//             }
//             else
//             {
//                 int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
//                 if(ret != xsuccess)
//                 {
//                     if(force)
//                     {
//                         if(errno == EEXIST)
//                         {
//                             if(epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event) == xsuccess)
//                             {
//                                 descriptor->status |= xdescriptorstatus_register;
//                                 xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//                                 return xsuccess;
//                             }
//                         }
//                     }
//                     if(ret != xsuccess)
//                     {
//                         descriptor->status |= xdescriptorstatus_exception;
//                         descriptor->exception.func = epoll_ctl;
//                         descriptor->exception.number = errno;
//                         xlogfunction_end("%s(...) => %d", __func__, xfail);
//                         return xfail;
//                     }
//                     descriptor->status |= xdescriptorstatus_register;
//                     xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//                     return xsuccess;
//                 }
//                 descriptor->status |= xdescriptorstatus_register;
//                 xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//                 return xsuccess;
//             }
//         }
//         xlogfunction_end("%s(...) => %d", __func__, xfail);
//         return xfail;
//     }
//     xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//     return xsuccess;
// }

// static inline xint32 xdescriptoreventgenerator_epoll_open(xdescriptoreventgenerator_epoll * generator)
// {
//     xdebugonly(xlogfunction_start("%s(%p)", __func__, generator));
//     if(generator->f < 0)
//     {
//         generator->f = epoll_create(generator->max);

//         if(generator->f >= 0)
//         {
//             __xsynclock(generator->alive->sync);
//             xdescriptoreventsubscription * subscription = generator->alive->head;
//             while(subscription)
//             {
                
//                 if(subscription->descriptor->handle.f >= 0)
//                 {
//                     if(xdescriptoreventgenerator_epoll_register(generator->f, subscription, xtrue) == xsuccess)
//                     {
//                         subscription = subscription->generatornode.next;
//                         continue;
//                     }
//                 }
//                 xassertion(xtrue, "implement this");
//             }
//             __xsyncunlock(generator->alive->sync);
//         }
//         else
//         {
//             xassertion(generator->f < 0, "");
//             xlogfunction_end("%s(...) => %d", __func__, xfail);
//             return xfail;
//         }
//     }
//     xdebugonly(xlogfunction_end("%s(...) => %d", __func__, xsuccess));
//     return xsuccess;
// }



// extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, o, subscription);

//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;
//     xdescriptor * descriptor = subscription->descriptor;

//     if(descriptor->handle.f >= 0)
//     {
//         xdescriptornonblock(descriptor, xtrue);
//         if((descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
//         {
//             if((descriptor->status & xdescriptorstatus_close) == xdescriptorstatus_void)
//             {
//                 if(descriptor->status & xdescriptorstatus_open)
//                 {
//                     int ret = xdescriptoreventgenerator_epoll_register(generator->f, subscription, xfalse);
//                     if(ret == xsuccess)
//                     {
//                         descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xtrue);
//                         xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
//                     }
//                     xlogfunction_end("%s(...)", __func__);
//                     return;
//                 }
//             }
//         }
//     }

//     xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
//     xlogfunction_end("%s(...)", __func__);
// }

// extern void xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, o, subscription);
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     xdescriptor * descriptor = subscription->descriptor;

//     if(descriptor->handle.f >= 0)
//     {
//         if(descriptor->status & xdescriptorstatus_register)
//         {
//             xdescriptoreventgenerator_epoll_unregister(generator->f, subscription, xtrue);
//             descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xfalse);
//         }
//     }
//     if(subscription->generatornode.list)
//     {
//         xdescriptoreventgeneratorsubscriptionlist_del(subscription);
//     }

//     xlogfunction_end("%s(...)", __func__);
// }

// extern void xdescriptoreventgenerator_once(xdescriptoreventgenerator * o)
// {
//     xdebugonly(xlogfunction_start("%s(%p)", __func__, o));  // repeat infinte
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     if(xdescriptoreventgenerator_epoll_open(generator) == xsuccess)
//     {
//         xdescriptoreventgenerator_queue_once(o);

//         int nfds = epoll_wait(generator->f, generator->events, generator->max, generator->millisecond);

//         if(nfds >= 0)
//         {
//             for(int i = 0; i < nfds; i++)
//             {
//                 xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) generator->events[i].data.ptr;

//                 if(generator->events[i].events & (EPOLLERR | EPOLLPRI | EPOLLRDHUP | EPOLLHUP))
//                 {
//                     xexceptionset(xaddressof(subscription->descriptor->exception), epoll_wait, generator->events[i].events, xexceptiontype_descriptor, ""); 
//                     xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_exception);
//                     continue;
//                 }
//                 if(generator->events[i].events & EPOLLOUT)
//                 {
//                     if(subscription->descriptor->status & xdescriptorstatus_connecting)
//                     {
//                         xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_connecting);
//                         continue;
//                     }
//                     xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_out);
//                 }
//                 if(generator->events[i].events & EPOLLIN)
//                 {
//                     xdescriptoreventdispatch(subscription->descriptor, xdescriptoreventtype_in);
//                 }
//             }
//         }
//         else
//         {
//             if(errno != EINTR)
//             {
//                 int ret = close(generator->f);
//                 xassertion(ret != xsuccess, "");
//                 generator->f = xinvalid;
//             }
//         }
//     }

//     xdebugonly(xlogfunction_end("%s(...)", __func__));  // repeat infinite
// }

// extern void xdescriptoreventgenerator_queue_once(xdescriptoreventgenerator * o)
// {
//     xdebugonly(xlogfunction_start("%s(%p)", __func__, o));
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     __xsynclock(generator->queue->sync);
//     xuint64 total = generator->queue->size;
//     for(xuint64 i = 0; i < total; i++)
//     {
//         xdescriptoreventsubscription * subscription = xdescriptoreventgeneratorsubscriptionlist_pop(generator->queue);
//         if(subscription)
//         {
//             __xsyncunlock(generator->queue->sync);
//             xdescriptor * descriptor = subscription->descriptor;
//             if(descriptor->status & xdescriptorstatus_rem)
//             {
//                 descriptor->process(descriptor, xdescriptoreventtype_rem);

//                 __xsynclock(generator->queue->sync);
//                 continue;
//             }

//             if(descriptor->process(descriptor, xdescriptoreventtype_open) == xsuccess)
//             {
//                 if(xdescriptoreventgenerator_descriptor_register(generator, descriptor) == xsuccess)
//                 {

//                 }
//             }
//             __xsynclock(generator->queue->sync);
//         }
//         if(subscription)
//         {
//             __xsyncunlock(generator->queue->sync);

//             xdescriptor * descriptor = subscription->descriptor;

//             if(descriptor->status & xdescriptorstatus_rem)
//             {
//                 descriptor->process(descriptor, xdescriptoreventtype_rem);

//                 __xsynclock(generator->queue->sync);
//                 continue;
//             }

//             if(descriptor->process(descriptor, xdescriptoreventtype_open) == xsuccess)
//             {
//                 __xsynclock(generator->alive->sync);
//                 xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
//                 __xsyncunlock(generator->alive->sync);
//             }
                
                
//             if(descriptor->status & (xdescriptorstatus_exception | xdescriptorstatus_close | xdescriptorstatus_rem))
//             {
//                 xassertion(descriptor->status & xdescriptorstatus_register, "");
//                 if(descriptor->handle.f >= 0)
//                 {
//                     xassertion(descriptor->status & xdescriptorstatus_close, "");
//                     close
//                     xdescriptoreventprocess(descriptor, xdescriptoreventtype_close);
//                 }


//             }
            
//             if(xdescriptoreventprocess(descriptor, xdescriptoreventtype_open) == xsuccess)
//             {
//                 __xsynclock(generator->alive->sync);
//                 xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
//                 __xsyncunlock(generator->alive->sync);
//                 if(xdescriptoreventprocess(descriptor, xdescriptoreventtype_register) >= 0)
//                 {
//                     __xsynclock(generator->queue->sync);
//                     continue;
//                 }
//                 if(subscription->generatornode.list)
//                 {
//                     xdescriptoreventgeneratorsubscriptionlist_del(subscription);
//                 }
//             }
//             __xsynclock(generator->queue->sync);
//             xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
//             continue;
//         }
//         break;
//     }
//     __xsyncunlock(generator->queue->sync);

//     xdebugonly(xlogfunction_end("%s(...)", __func__));
// }

// extern void xdescriptoreventgenerator_sync(xdescriptoreventgenerator * o, xint32 on)
// {
//     xlogfunction_start("%s(%p, %d)", __func__, o, on);
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     if(on)
//     {
//         if(generator->alive->sync)
//         {
//             generator->alive->sync = xsyncnew(xsynctype_default);
//         }
//         if(generator->queue->sync)
//         {
//             generator->queue->sync = xsyncnew(xsynctype_default);
//         }
        
//     }
//     else
//     {
//         generator->alive->sync = xsyncrem(generator->alive->sync);
//         generator->queue->sync = xsyncrem(generator->queue->sync);
//     }

//     xlogfunction_end("%s(...)", __func__);
// }

// extern void xdescriptoreventgenerator_on(xdescriptoreventgenerator * o)
// {
//     xlogfunction_start("%s(%p)", __func__, o);
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     xdescriptoreventgenerator_epoll_open(generator);

//     xlogfunction_end("%s(...)", __func__);
// }

// extern void xdescriptoreventgenerator_off(xdescriptoreventgenerator * o)
// {
//     xlogfunction_start("%s(%p)", __func__, o);
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     if(generator->f)
//     {
//         int ret = close(generator->f);
//         xassertion(ret != xsuccess, "");
//         generator->f = xinvalid;
//     }

//     generator->events = xobjectrem(generator->events);
//     // alive session unregister set

//     xdescriptoreventgenerator_alive_clear(o);
//     xdescriptoreventgenerator_queue_clear(o);

//     xlogfunction_end("%s(...)", __func__);
// }

// extern void xdescriptoreventgenerator_alive_clear(xdescriptoreventgenerator * generator)
// {
//     xlogfunction_start("%s(%p)", __func__, generator);

//     xdescriptoreventsubscription * subscription = generator->alive->head;
//     while(subscription)
//     {
//         xdescriptoreventsubscription * next = xdescriptoreventgeneratorsubscriptionlist_pop(generator->alive);

//         xdescriptor * descriptor = subscription->descriptor;
//         descriptor->status &= (~xdescriptorstatus_register);
//         descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xfalse);

//         subscription->generatornode.generator = xnil;
        
//         subscription = next;
//     }

//     xlogfunction_end("%s(...)", __func__);
// }

// extern void xdescriptoreventgenerator_queue_clear(xdescriptoreventgenerator * generator)
// {
//     xlogfunction_start("%s(%p)", __func__, generator);
//     xdescriptoreventsubscription * subscription = generator->alive->head;
//     while(subscription)
//     {
//         xdescriptoreventsubscription * next = xdescriptoreventgeneratorsubscriptionlist_pop(generator->alive);

//         xdescriptor * descriptor = subscription->descriptor;

//         subscription->generatornode.generator = xnil;
        
//         subscription = next;
//     }

//     xlogfunction_end("%s(...)", __func__);
// }

// extern xint64 xdescriptoreventgenerator_descriptor_update(xdescriptoreventgenerator * o, xdescriptor * descriptor)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, o, descriptor);
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     xdescriptoreventsubscription * subscription = descriptor->subscription;

//     xassertion(o != subscription->generatornode.generator, "");
//     xassertion(descriptor->handle.f < 0, "");
//     xassertion(generator->alive != subscription->generatornode.list, "");

//     xint64 ret = xdescriptoreventgenerator_epoll_update(generator->f, subscription, xtrue);

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// extern xint64 xdescriptoreventgenerator_descriptor_unregister(xdescriptoreventgenerator * o, xdescriptor * descriptor)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, o, descriptor);

//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     xdescriptoreventsubscription * subscription = descriptor->subscription;

//     xassertion(o != subscription->generatornode.generator, "");
//     xassertion(descriptor->handle.f < 0, "");

//     if(generator->alive == subscription->generatornode.list)
//     {
//         if(xdescriptoreventgenerator_epoll_unregister(generator->f, subscription, xtrue) == xsuccess)
//         {
//             descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xtrue);
//         }
//     }

//     xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//     // TODO: IMPLEMENT LOGIC
//     return xsuccess;
// }

// extern xint64 xdescriptoreventgenerator_descriptor_dispatch(xdescriptoreventgenerator * o, xdescriptor * descriptor)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, o, descriptor);
//     xint64 ret = xfail;

//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;
//     xdescriptoreventsubscription * subscription = descriptor->subscription;

//     if(generator->alive == subscription->generatornode.list)
//     {
//         xassertion(xtrue, "");
//     }
//     else if(generator->queue == subscription->generatornode.list)
//     {
//         ret = xsuccess;
//     }
//     else
//     {
//         xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
//     }


//     xlogfunction_end("%s(...) => %d", __func__, xsuccess);
//     // TODO: IMPLEMENT LOGIC
//     return xsuccess;
// }