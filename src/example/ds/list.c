#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>
#include <x/list.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);
    xrandominit();

    xlist * list = xlistnew();
    xuint64 size = 0;
    xuint64 total = xrandomunsigned64(128);

    for(xuint64 i = 0; i < total; i++)
    {
        xlistpushback(list, xvalunsigned64(xrandomunsigned64(0)));
    }
    xassertion(xlistsize(list) != total, "");
    size = size + total;
    total = xrandomunsigned64(128);
    for(xuint64 i = 0; i < total; i++)
    {
        xlistpushfront(list, xvalunsigned64(xrandomunsigned64(0)));
    }
    xassertion(xlistsize(list) != total + size, "");
    size = size + total;

    total = xrandomunsigned64(64);
    for(xuint64 i = 0; i < total; i++)
    {
        xlistnode * node = xlistpopfront(list);
        if(node)
        {
            size = size - 1;
            free(node);
        }
    }
    xassertion(xlistsize(list) != size, "");

    total = xrandomunsigned64(64);
    for(xuint64 i = 0; i < total; i++)
    {
        xlistnode * node = xlistpopback(list);
        if(node)
        {
            size = size - 1;
            free(node);
        }
    }
    xassertion(xlistsize(list) != size, "");

    total = xrandomunsigned64(64);
    for(xuint64 i = 0; i < total; i++)
    {
        xlistnode * node = xlistget(list, xrandomunsigned64(xlistsize(list)));
        if(node)
        {
            xlistinsertfront(list, node, xvalunsigned64(xrandomunsigned64(0)));
            xassertion(size + 1 != xlistsize(list), "");
            size = size + 1;
        }
    }
    xassertion(xlistsize(list) != size, "");

    total = xrandomunsigned64(64);
    for(xuint64 i = 0; i < total; i++)
    {
        xlistnode * node = xlistget(list, xrandomunsigned64(xlistsize(list)));
        if(node)
        {
            xlistinsertback(list, node, xvalunsigned64(xrandomunsigned64(0)));
            xassertion(size + 1 != xlistsize(list), "");
            size = size + 1;
        }
    }
    xassertion(xlistsize(list) != size, "");

    total = xrandomunsigned64(64);
    for(xuint64 i = 0; i < total; i++)
    {
        xlistnode * node = xlistget(list, xrandomunsigned64(xlistsize(list)));
        if(node)
        {
            xlistdel(list, node);
            xassertion(size - 1 != xlistsize(list), "");
            size = size - 1;
        }
    }
    xassertion(xlistsize(list) != size, "");

    xlistrem(list, xnil);
    xlogterm();
    return 0;
}
