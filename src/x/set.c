#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "set.h"

static xdictionarynode * xsetnodefactory(xval key)
{
    xdictionarynode * node = (xdictionarynode *) calloc(sizeof(xdictionarynode), 1);

    node->color = xdictionarynodecolor_red;
    node->key   = key;
    
    return node;
}

extern xset * xsetnew(xdictionarycmp comparator)
{
    return (xset *) xdictionarynew(comparator);
}

extern xset * xsetrem(xset * set)
{
    return xdictionaryrem(set);
}

extern void xsetadd(xset * set, xval key)
{
    xdictionaryadd(set, key, xnil);
}

extern xint32 xsetdel(xset * set, xval key)
{
    xdictionarynode * node = xdictionarydel(set, key);
    if(node)
    {
        free(node);
        return xtrue;
    }
    return xfalse;
}

extern xint32 xsethas(xset * set, xval key)
{
    xdictionarynode * node = xdictionaryget(set, key);

    return node != xnil;
}