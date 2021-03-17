#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

#include "queue.h"

extern xqueue * xqueuenew(void)
{
    xqueue * queue = xlistnew();

    return queue;
}

extern xqueue * xqueuerem(xqueue * queue, xvalfunc func)
{
    queue = xlistrem(queue, func);
    return xnil;
}

extern void xqueuepush(xqueue * queue, xval value)
{
    xlistpushback(queue, value);
}

extern xval xqueuepop(xqueue * queue)
{
    xlistnode * node = xlistpopfront(queue);
    
    xassertion(node == xnil, "");
    xval value = node->value;

    free(node);

    return value;
}

extern xuint64 xqueuesize(xqueue * queue)
{
    return queue->size;
}

extern void xqueueclear(xqueue * queue, xvalfunc func)
{
    xlistclear(queue, func);
}

