#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>
#include <x/stack.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);
    xrandominit();

    xstack * stack = xstacknew();

    xuint64 size = 0;
    xuint64 total = xrandomunsigned64(128);

    for(xuint64 i = 0; i < total; i++)
    {
        xstackpush(stack, xvalinteger64(xrandominteger64(0)));
    }

    total = xrandomunsigned64(128);

    for(xuint64 i = 0; i < total; i++)
    {
        if(xstacksize(stack) > 0)
        {
            xstackpop(stack);
        }
    }

    // atex

    xstackrem(stack, xnil);
    xlogterm();
    return 0;
}