#include "generator.h"

#include "../../event/engine.h"
#include "../../client/socket.h"
#include "../../client/pool.h"
#include "../../client/pool/list.h"

extern void xdescriptoreventgenerator_clientpool_add(xdescriptoreventgenerator * o, xclientpool * pool)
{
    if(o->clientpoollist == xnil)
    {
        o->clientpoollist = xclientpoollist_new();
    }
    xclientpoollist_add(o->clientpoollist, pool);
    for(xclient * client = pool->head; client != xnil; client = xclientpool_next(client))
    {
        xdescriptor * descriptor = client->descriptor;

        descriptor->subscription = (xdescriptoreventsubscription *) xeventengine_client_register(o->engine, client);
    }
}

extern void xdescriptoreventgenerator_clientpool_del(xdescriptoreventgenerator * o, xclientpool * pool)
{
    xassertion(o->clientpoollist == xnil, "");

    if(o->clientpoollist)
    {
        xassertion(o->clientpoollist != pool->cntr, "");
        if(o->clientpoollist == pool->cntr)
        {
            xclientpoollist_del(pool->cntr, pool);
            for(xclient * client = pool->head; client != xnil; client = xclientpool_next(client))
            {
                xeventengine_client_unregister(o->engine, client);
                if(client->descriptor)
                {
                    client->descriptor->subscription = xobjectrem(client->descriptor->subscription);
                }
            }
        }
    }
}