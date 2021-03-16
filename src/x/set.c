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

extern void xsetadd(xset * set, xval key)
{
    xdictionarynode * node = xdictionarynodeadd(set, key, xsetnodefactory);
    xassertion(node == xnil, "");
}

extern void xsetdel(xset * set, xval key)
{
    xdictionarynode * node = xdictionarynodedel(set, key);
    free(node);
}

extern xint32 xsethas(xset * set, xval key)
{
    xdictionarynode * node = xdictionarynodeget(set, key);

    return node != xnil;
}