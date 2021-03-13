#include <stdio.h>

#include "pool.h"

#include "../log.h"

extern xclientpool * xclientpool_new(xclientfactory factory, xclientreleaser * releaser, xclientpoolsubscriber on, xuint32 total)
{
    xlogfunction_start("%s(%p, %p, %u)", __func__, factory, releaser, total);

    xclientpool * pool = (xclientpool *) calloc(sizeof(xclientpool), 1);

    pool->create = factory;
    pool->release = releaser;
    pool->on = on;

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