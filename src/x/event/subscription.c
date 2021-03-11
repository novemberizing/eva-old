#include <stdio.h>
#include <stdlib.h>

#include "subscription.h"

#include "engine.h"
#include "target.h"

#include "../thread.h"

extern xeventsubscription * xeventsubscription_new(xeventengine * engine, xeventtarget * target, xuint64 size)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, engine, target, size);

    xassertion(target == xnil || engine == xnil || size < sizeof(xeventsubscription), "");

    xeventsubscription * subscription = (xeventsubscription *) calloc(size, 1);

    xassertion(subscription == xnil, "");

    __xsynclock(engine->subscriptions.sync);
    subscription->target = target;
    subscription->target->subscription = subscription;
    

    subscription->enginenode.engine = engine;
    subscription->enginenode.prev = engine->subscriptions.tail;
    if(subscription->enginenode.prev)
    {
        subscription->enginenode.prev->enginenode.next = subscription;
    }
    else
    {
        engine->subscriptions.head = subscription;
    }
    engine->subscriptions.tail = subscription;
    engine->subscriptions.size = engine->subscriptions.size + 1;
    __xsyncunlock(engine->subscriptions.sync);

    xlogfunction_end("%s(...) => %p", __func__, subscription);
    return subscription;
}

extern xeventsubscription * xeventsubscription_rem(xeventsubscription * subscription)
{
    xlogfunction_start("%s(%p)", __func__, subscription);

    xassertion(subscription == xnil, "");
    xassertion(subscription->enginenode.engine || subscription->enginenode.next || subscription->enginenode.prev, "");

    if(subscription->target)
    {
        subscription->target->subscription = xnil;
    }
    free(subscription);

    xlogfunction_end("%s(...) => %p", __func__, xnil);
    return xnil;
}

extern xeventsubscription * xeventsubscription_del(xeventsubscription * subscription)
{
    xlogfunction_start("%s(%p)", __func__, subscription);

    xassertion(subscription == xnil, "");
    xassertion(subscription->enginenode.engine == xnil, "");

    xeventengine * engine     = subscription->enginenode.engine;

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

    xlogfunction_end("%s(...) => %p", __func__, subscription);
    return subscription;
}