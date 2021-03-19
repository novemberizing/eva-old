#include "subscription.h"

extern xdescriptoreventsubscription * xdescriptoreventsubscription_rem(xdescriptoreventsubscription * subscription)
{
    if(subscription)
    {
        xeventengine * engine = subscription->enginenode.engine;
        xeventengine_descriptor_unregister(engine, subscription->descriptor);
        free(subscription);
    }
    return xnil;
}