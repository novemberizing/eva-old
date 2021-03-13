#include <stdio.h>

#include "pool.h"
#include "./socket.h"

#include "../log.h"

extern xclientpool * xclientpool_new(xclientfactory factory, xclientreleaser * releaser, int domain, int type, int protocol, void * addr, xuint32 addrlen, xclientpoolsubscriber on, xuint32 total)
{
    xlogfunction_start("%s(%p, %p, %u)", __func__, factory, releaser, total);

    xclientpool * pool = (xclientpool *) calloc(sizeof(xclientpool), 1);

    pool->create = factory;
    pool->release = releaser;
    pool->on = on;

    pool->domain = domain;
    pool->type = type;
    pool->protocol = protocol;
    pool->addr = xobjectdup(addr, addrlen);
    pool->addrlen = addrlen;

    xclientpool_client_bulk_create(pool, total);

    xlogfunction_end("%s(...) => %p", __func__, pool);

    return pool;
}

extern xclientpool * xclientpool_rem(xclientpool * pool)
{
    xlogfunction_start("%s(%p)", __func__, pool);

    xassertion(pool == xnil, "");

    if(pool)
    {
        xassertion(pool->size > 0 || pool->head || pool->tail, ""); // must clear
        
        pool->sync = xsyncrem(pool->sync);
        pool->addr = xobjectrem(pool->addr);

        free(pool);
    }

    xlogfunction_end("%s(...) => %p", __func__, xnil);
    return xnil;
}

extern xclient * xclientpool_client_create(xclientpool * pool)
{
    xlogfunction_start("%s(%p)", __func__, pool);

    xclient * client = xnil;

    if(pool)
    {
        client = pool->create(pool);

        xassertion(client == xnil, "");

        if(client)
        {
            client->cntr = pool;
            
            client->prev = pool->tail;

            if(client->prev)
            {
                client->prev->next = client;
            }
            else
            {
                pool->head = client;
            }

            pool->tail = client;
            pool->size = pool->size + 1;
        }
    }

    xlogfunction_end("%s(...) => %p", __func__, client);
    return client;
}

extern xclient * xclientpool_pop(xclientpool * pool)
{
    xlogfunction_start("%s(%p)", __func__, pool);

    xclient * client = pool->head;

    if(client)
    {
        pool->head = client->next;

        if(pool->head)
        {
            pool->head->prev = xnil;
            client->next = xnil;
        }
        else
        {
            pool->tail = xnil;
        }
        client->cntr = xnil;
        pool->size = pool->size - 1;
    }

    xlogfunction_end("%s(...) => %p", __func__, client);
    return client;
}

extern xclient * xclientpool_del(xclientpool * pool, xclient * client)
{
    xlogfunction_start("%s(%p, %p)", __func__, pool, client);

    xasertion(client->cntr != pool, "");

    if(client->cntr == pool)
    {
        xclient * prev = client->prev;
        xclient * next = client->next;

        if(prev)
        {
            prev->next = next;
            client->prev = xnil;
        }
        else
        {
            pool->head = next;
        }
        if(next)
        {
            next->prev = prev;
            client->next = xnil;
        }
        else
        {
            pool->tail = prev;
        }
        pool->size = pool->size - 1;
        client->cntr = xnil;
    }

    xlogfunction_end("%s(...) =>", __func__, client);
    return client;
}

extern void xclientpool_client_release(xclientpool * pool, xclient * client)
{
    xlogfunction_start("%s(%p, %p)", __func__, pool, client);

    xassertion(pool != client->cntr, "");

    xclientpool_del(pool, client);
    pool->release(client);

    // 엔진이 존재하면 엔진에 등록해제하는 것 까지 하자.

    xlogfunction_end("%s(...)", __func__);
}

extern void xclientpool_client_bulk_create(xclientpool * pool, xuint64 total)
{
    xlogfunction_start("%s(%p, %lu)", __func__, pool, total);

    for(xuint64 i = 0; i < total; i++)
    {
        xclient * client = xclientpool_client_create(pool);
        // 엔진이 존재하면 엔진에 등록하는 것 까지 하자.
    }

    xlogfunction_end("%s(...)");
}