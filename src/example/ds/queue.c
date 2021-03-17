#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>
#include <x/queue.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);
    xrandominit();

    xqueue * queue = xqueuenew();

    xuint64 size = 0;
    xuint64 total = xrandomunsigned64(128);

    for(xuint64 i = 0; i < total; i++)
    {
        xqueuepush(queue, xvalinteger64(xrandominteger64(0)));
    }

    total = xrandomunsigned64(128);

    for(xuint64 i = 0; i < total; i++)
    {
        if(xqueuesize(queue) > 0)
        {
            xqueuepop(queue);
        }
    }

    // atex

    xqueuerem(queue, xnil);
    xlogterm();
    return 0;
}