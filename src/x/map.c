#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "map.h"

struct xmapnode;

typedef struct xmapnode xmapnode;

struct xmapnode
{
    xuint32           color:1;
    xuint32           size:31;
    xdictionarynode * parent;
    xdictionarynode * left;
    xdictionarynode * right;
    xval              key;
    xval              value;
};

extern xmap * xmapnew(xdictionarycmp comparator)
{
    return (xmap *) xdictionarynew(comparator);
}

extern void xmapadd(xmap * map, xval key, xval value, xmapinsertioncallback callback)
{
    xmapnode * prev = xnil;
    xmapnode * node = (xmapnode *) xdictionaryadd(map, key, (xdictionarynode **) xaddressof(prev));
    if(prev)
    {
        if(callback)
        {
            callback(map, key, value, xtrue, xaddressof(prev->value));
        }
    }
    else
    {
        if(callback)
        {
            callback(map, key, value, xtrue, xnil);
        }
    }
    node->value = value;
}

extern xint32 xmapdel(xmap * map, xval key, xmapdeletioncallback callback)
{
    xmapnode * node = (xmapnode *) xdictionarydel(map, key);

    if(callback)
    {
        callback(map, key, node != xnil, node ? xaddressof(node->value) : xnil);
    }
    if(node != xnil)
    {
        free(node);
        return xtrue;
    }
    return xfalse;
}

extern xint32 xmaphas(xmap * map, xval key)
{
    xmapnode * node = (xmapnode *) xdictionaryget(map, key);

    return node != xnil;
}

