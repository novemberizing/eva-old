#include <stdlib.h>
#include <stdio.h>


#include "engine.h"

#include "../thread.h"
#include "../descriptor.h"
#include "../console/descriptor.h"
#include "../descriptor/event/generator.h"
#include "../server.h"
#include "../server/socket.h"
#include "../session.h"
#include "../session/socket.h"

#include "./processor/pool.h"
#include "../descriptor/event/subscription.h"


static void xeventenginecallback_internal(xeventengine * engine, xuint32 status);

extern xeventengine * xeventengine_new(void)
{
    xlogfunction_start("%s()", __func__);
    xeventengine * engine = (xeventengine *) calloc(sizeof(xeventengine), 1);

    engine->main  = xeventqueue_new();
    engine->queue = xeventqueue_new();

    engine->generators.descriptor = xdescriptoreventgenerator_new(engine);

    xlogfunction_end("%s(...) => %p", __func__, engine);
    return engine;
}

extern void xeventengine_cancel(xeventengine * engine, xeventenginefunc callback)
{
    if(engine)
    {
        engine->cancel = callback;
    }
}

extern xint32 xeventengine_run(xeventengine * engine)
{
    xlogfunction_start("%s(%p)", __func__, engine);
    xassertion(engine == xnil, "");

    if(engine->on == xnil)
    {
        engine->on = xeventenginecallback_internal;

        xeventengine_sync(engine, xeventprocessorpool_size(engine->processors));

        __xsynclock(engine->sync);
        // xeventengine_generators_on(engine);
        xeventgeneratorset_on(xaddressof(engine->generators));
        xeventprocessorpool_on(engine->processors);
        while(engine->cancel == xnil)
        {
            // 어느 시점에 ENGINE SYNC 의 UNLOCK/LOCK 을 수행해야 하는지 확인할 필요가 있다.
            __xsyncunlock(engine->sync);

            xeventqueue_once(engine->main);

            xeventgeneratorset_once(xaddressof(engine->generators));

            if(xeventprocessorpool_size(engine->processors) == 0)
            {
                xeventqueue_once(engine->queue);
            }

            __xsynclock(engine->sync);
        }
        xeventgeneratorset_off(xaddressof(engine->generators));
        xeventqueue_clear(engine->queue);
        xeventqueue_clear(engine->main);

        engine->on(engine, xeventenginestatus_off);
        engine->on = xnil;
        __xsyncunlock(engine->sync);
        xeventengine_sync(engine, xfalse);
        engine->queue = xeventqueue_rem(engine->queue);
        engine->main = xeventqueue_rem(engine->main);
        xeventgeneratorset_rem(xaddressof(engine->generators));
        
        // 아래의 로직은 ENEING SUBSCRIPTIONS 리스트를 클리어 하는 것이다.
        // 함수화 시켜 놓을 필요가 있다.
        while(engine->subscriptions.head)
        {
            xeventsubscription * next = engine->subscriptions.head->enginenode.next;
            // TODO: 아래의 로직은 복잡하다. 그렇기 때문에, 작은 DEL 을 구현해야 한다.
            // POP 같은 메서드
            xeventsubscription_del(engine->subscriptions.head);
            engine->subscriptions.head = next;
        }

        free(engine);
    }

    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}

extern void xeventengine_sync(xeventengine * engine, xint32 on)
{
    xlogfunction_start("%s(%p, $d)", __func__, engine, on);
    if(on)
    {
        if(engine->sync == xnil)
        {
            engine->sync = xsyncnew(xsynctype_default);
        }
    }
    else
    {
        xassertion(xeventprocessorpool_size(engine->processors) > 0, "");
        engine->sync = xsyncrem(engine->sync);
    }
    __xsynclock(engine->sync);

    xeventprocessorpool_sync(engine->processors, on);
    xdescriptoreventgenerator_sync(engine->generators.descriptor, on);
    if(on)
    {
        if(engine->subscriptions.sync == xnil)
        {
            engine->subscriptions.sync = xsyncnew(xsynctype_default);
        }
        if(engine->queue->sync == xnil)
        {
            engine->queue->sync = xsyncconditioninit(xsyncnew(xsynctype_default));
        }
        if(engine->main->sync == xnil)
        {
            engine->main->sync = xsyncnew(xsynctype_default);
        }
    }
    else
    {
        engine->subscriptions.sync = xsyncrem(engine->subscriptions.sync);
        engine->queue->sync = xsyncrem(engine->queue->sync);
        engine->main->sync = xsyncrem(engine->main->sync);
    }

    __xsyncunlock(engine->sync);

    xlogfunction_end("%s(...)", __func__);
}

extern xeventsubscription * xeventengine_session_register(xeventengine * engine, xsession * session)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, session);

    xassertion(engine == xnil || session == xnil || session->descriptor == xnil, "");
    xassertion(session->descriptor->subscription, "");   // 이 로직을 어떻게 처리해야할까?

    xsessionsocketeventsubscription * subscription = (xsessionsocketeventsubscription *) xeventsubscription_new(engine, (xeventtarget *) session->descriptor, sizeof(xsessionsocketeventsubscription));

    subscription->generatornode.generator = engine->generators.descriptor;

    xdescriptoreventgenerator_register(engine->generators.descriptor, (xdescriptoreventsubscription *) subscription);

    xlogfunction_end("%s(...) => %p", (xeventsubscription *) subscription);
    return (xeventsubscription *) subscription;
}

extern xeventsubscription * xeventengine_session_unregister(xeventengine * engine, xsession * session)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, session);

    xeventsubscription * ret = (xeventsubscription *) xeventengine_descriptor_unregister(engine, (xdescriptor *) session->descriptor);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

extern xeventsubscription * xeventengine_client_register(xeventengine * engine, xclient * client)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, client);

    xassertion(engine == xnil || client == xnil || client->descriptor == xnil, "");
    xassertion(client->descriptor->subscription, "");   // 이 로직을 어떻게 처리해야할까?

    xsessionsocketeventsubscription * subscription = (xsessionsocketeventsubscription *) xeventsubscription_new(engine, (xeventtarget *) client->descriptor, sizeof(xsessionsocketeventsubscription));

    subscription->generatornode.generator = engine->generators.descriptor;

    xdescriptoreventgenerator_register(engine->generators.descriptor, (xdescriptoreventsubscription *) subscription);

    xlogfunction_end("%s(...) => %p", (xeventsubscription *) subscription);
    return (xeventsubscription *) subscription;
}

extern xeventsubscription * xeventengine_client_unregister(xeventengine * engine, xclient * client)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, client);

    xeventsubscription * ret = (xeventsubscription *) xeventengine_descriptor_unregister(engine, (xdescriptor *) client->descriptor);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

extern xeventsubscription * xeventengine_server_register(xeventengine * engine, xserver * server)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, server);

    xassertion(engine == xnil || server == xnil || server->descriptor == xnil, "");
    xassertion(server->descriptor->subscription, "");   // 이 로직을 어떻게 처리해야할까?

    xserversocketeventsubscription * subscription = (xserversocketeventsubscription *) xeventsubscription_new(engine, (xeventtarget *) server->descriptor, sizeof(xserversocketeventsubscription));

    subscription->generatornode.generator = engine->generators.descriptor;

    xdescriptoreventgenerator_register(engine->generators.descriptor, (xdescriptoreventsubscription *) subscription);

    xlogfunction_end("%s(...) => %p", __func__, subscription);
    return (xeventsubscription *) subscription;
}

extern xeventsubscription * xeventengine_server_unregister(xeventengine * engine, xserver * server)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, server);
    xeventsubscription * ret = (xeventsubscription *) xeventengine_descriptor_unregister(engine, (xdescriptor *) server->descriptor);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}


extern xeventsubscription * xeventengine_descriptor_register(xeventengine * engine, xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, descriptor);
    xassertion(engine == xnil || descriptor == xnil, "");

    xassertion(descriptor->subscription, "");   // 이 로직은 어떻게 처리해야 할까?

    xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) xeventsubscription_new(engine, (xeventtarget *) descriptor, sizeof(xdescriptoreventsubscription));

    subscription->generatornode.generator = engine->generators.descriptor;

    xdescriptoreventgenerator_register(engine->generators.descriptor, subscription);

    xlogfunction_end("%s(...) => %p", __func__, subscription);
    return (xeventsubscription *) subscription;
}

extern xeventsubscription * xeventengine_descriptor_unregister(xeventengine * engine, xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p, %p)", __func__, descriptor);
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(subscription->enginenode.engine == engine)
    {
        xdescriptoreventgenerator_unregister(engine->generators.descriptor, subscription);

        xeventsubscription * prev = subscription->enginenode.prev;
        xeventsubscription * next = subscription->enginenode.next;

        if(prev)
        {
            prev->enginenode.next = next;
            subscription->enginenode.prev = xnil;
        }
        else
        {
            engine->subscriptions.head = next;
        }

        if(next)
        {
            next->enginenode.prev = prev;
            subscription->enginenode.next = xnil;
        }
        else
        {
            engine->subscriptions.tail = prev;
        }

        engine->subscriptions.size = engine->subscriptions.size - 1;

        subscription->enginenode.engine = xnil;
    }
    else
    {
        xassertion(subscription->enginenode.engine != engine ,"");
    }

    xlogfunction_end("%s(...) => %p", __func__, subscription);
    return (xeventsubscription *) subscription;
}

extern void xeventengine_main_push(xeventengine * engine, xevent * event)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, event);
    xassertion(engine == xnil || engine->main == xnil || event == xnil, "");

    __xsynclock(engine->main->sync);
    xeventqueue_push(engine->main, event);
    __xsyncunlock(engine->main->sync);

    xlogfunction_end("%s(...)", __func__);
}

extern void xeventengine_queue_push(xeventengine * engine, xevent * event)
{
    xlogfunction_start("%s(%p, %p)", __func__, engine, event);
    xassertion(engine == xnil || engine->queue == xnil || event == xnil, "");

    /**
     * 이벤트 큐는 항상 WAKEUP 을 수행하도록 하였다.
     * 다만, 이벤트 프로세서의 카운트가 존재할 경우만 WAKEUP 을 수행하도록 하고 싶다.
     * TODO: 고민할 것,... 시그널을 보내는 것도 아깝기는 하다.
     */
    __xsynclock(engine->queue->sync);
    xeventqueue_push(engine->queue, event);
    __xsyncwakeup(engine->queue->sync, xfalse);
    __xsyncunlock(engine->queue->sync);

    xlogfunction_end("%s(...)", __func__);
}

static void xeventenginecallback_internal(xeventengine * engine, xuint32 status)
{
    xlogfunction_start("%s(%p, %u)", __func__, engine, status);
    // TODO: 

    xlogfunction_end("%s(...)", __func__);
}

/**
 * 
 */
extern xint32 xeventengine_descriptor_dispatch(xdescriptor * descriptor, xuint32 event)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);
    xassertion(descriptor == xnil, "");

    xdescriptoreventsubscription * subscription = descriptor->subscription;
    if(subscription)
    {
        xeventengine * engine = subscription->enginenode.engine;

        xassertion(engine == xnil, "");
        if(xeventprocessorpool_size(engine->processors) > 0)
        {
            if(descriptor->event.queue == xnil)
            {
                xeventengine_queue_push(engine, (xevent *) xaddressof(descriptor->event));
            }
            xlogfunction_end("%s(...) => %d", __func__, xsuccess);
            return xsuccess;
        }
    }

    xlogfunction_end("%s(...) => %d", __func__, xfail);
    return xfail;
}
