#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"
#include "pool.h"
#include "./socket.h"

#include "../log.h"

extern xclientpool * xclientpoolnew(xclientpoolobserver on, xuint64 size)
{
    xassertion(size < sizeof(xclientpool), "");
    xclientpool * pool = (xclientpool *) calloc(size, 1);

    pool->sync = xnil;
    pool->size = 0;
    pool->head = xnil;
    pool->tail = xnil;

    pool->on   = on;

    return pool;
}

extern xclientpool * xclientpoolrem(xclientpool * pool)
{
    if(pool == xnil)
    {
        free(pool);
    }
    return xnil;
}

extern void xclientpooladd(xclientpool * pool, xclient * client)
{
    xassertion(client == xnil || pool == xnil, "");
    xassertion(client->pool && client->pool != pool, "");

    if(client->pool == xnil)
    {
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
        client->pool = pool;
    }
}

extern void xclientpooldel(xclient * client)
{
    if(client->pool)
    {
        xclient * prev = client->prev;
        xclient * next = client->next;

        if(prev)
        {
            prev->next = next;
        }
        else
        {
            client->pool->head = next;
        }
        if(next)
        {
            next->prev = prev;
        }
        else
        {
            client->pool->tail = prev;
        }
        client->pool->size = client->pool->size - 1;
        client->pool = xnil;
    }
}

extern void xclientpoolpush(xclientpool * pool, xclient * client)
{
    xassertion(client == xnil || pool == xnil, "");
    xassertion(client->pool && client->pool != pool, "");

    if(pool && client)
    {
        if(client->pool == xnil)
        {
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
            client->pool = pool;
        }
    }
}

extern xclient * xclientpoolpop(xclientpool * pool)
{
    xclient * client = pool->head;

    if(client)
    {
        pool->head = client->next;
        if(pool->head)
        {
            pool->head->prev = xnil;
        }
        else
        {
            pool->tail = xnil;
        }
        pool->size = pool->size - 1;

        client->prev = xnil;
        client->next = xnil;
        client->pool = xnil;
    }

    return client;
}
