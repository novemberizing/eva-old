#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

#include "stack.h"

extern xstack * xstacknew(void)
{
    xstack * stack = xlistnew();

    return stack;
}

extern xstack * xstackrem(xstack * stack, xvalfunc func)
{
    stack = xlistrem(stack, func);

    return stack;
}

extern void xstackpush(xstack * stack, xval value)
{
    xlistpushfront(stack, value);
}

extern xval xstackpop(xstack * stack)
{
    xlistnode * node = xlistpopfront(stack);

    xassertion(node == xnil, "");

    xval value = node->value;

    free(node);

    return value;
}

extern xuint64 xstacksize(xstack * stack)
{
    return xlistsize(stack);
}

extern void xstackclear(xstack * stack, xvalfunc func)
{
    xlistclear(stack, func);
}