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