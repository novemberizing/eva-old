#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <x/thread.h>
#include <x/map.h>
#include <x/list.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);
    xrandominit();

    for(xuint32 i = 0; i < 16; i++)
    {
        printf("%u\n", i);
        xmap * map = xmapnew(xnil);
        xuint64 total = xrandomunsigned64(256);
        for(xuint64 i = 0; i < total; i++)
        {
            xval key = xvalunsigned64(xrandomunsigned64(256));
            xval value = key;
            xmapadd(map, key, value, xnil);
        }

        xuint64 n = xmapsize(map);
        total = xrandomunsigned64(256);
        for(xuint64 i = 0; i < total; i++)
        {
            xval value = xvalunsigned64(xrandomunsigned64(256));
            xmapdel(map, value, xnil);
        }
        xmaprem(map, xnil);
    }

    xmap * map = xmapnew(xnil);
    for(xuint64 i = 0; i < 4096; i++)
    {
//        printf("%lu\n", i);
        xmapadd(map, xvalunsigned64(i), xvalunsigned64(i), xnil);
    }
    xlist * leafs = xlistnew();
    for(xmapnode * node = xmapbegin(map); node != xnil; node = xmapnode_next(node))
    {
        // printf("%lu ", node->key.u64);
        if(xmapnode_left(node) == xnil && xmapnode_right(node) == xnil)
        {
            xlistpushback(leafs, xvalobject(node));
        }
    }
//    printf("\n");
    for(xlistnode * node = xlistbegin(leafs); node != xnil; node = xlistnext(node))
    {
        xdictionarynode * n = (xdictionarynode *) node->value.p;
        xperformancecheck(xmapget(map, n->key));
    }
    for(xuint64 i = 0; i < 1024; i++)
    {
        xval key = xvalunsigned64(xrandomunsigned64(4096));
        xmapnode * node = xmapget(map, key);
        if(node)
        {
            xval _key = xmapnodekey(node);
            xval value = xmapnodevalue(node);
            xassertion(_key.u64 != key.u64, "");
            xassertion(_key.u64 != value.u64, "");
        }
        // xmap
    }
    xlistrem(leafs, xnil);
    map = xmaprem(map, xnil);

    xlogterm();
    return 0;
}