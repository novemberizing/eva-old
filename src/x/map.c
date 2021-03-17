#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "map.h"

typedef xmap * (*xmapdestructor)(xmap *, xmapkeyvaluefunc);

typedef void (*xmapnodeswap)(xmapnode *, xmapnode *);



struct xmap
{
    xmapdestructor         rem;
    xdictionarynode *      root;
    xuint64                size;
    xdictionarynodefactory create;
    xdictionarycmp         compare;
    xmapnodeswap           swap;
    xmapclearfunc          clear;
    xsync *                sync;
};



struct xmapnode
{
    xuint32    color:1;
    xuint32    size:31;
    xmapnode * parent;
    xmapnode * left;
    xmapnode * right;
    xval       key;
    xval       value;
};

static void xmapnode_swap(xmapnode * x, xmapnode * y)
{
    xval key = x->key;
    xval value = x->value;

    x->key = y->key;
    x->value = y->value;

    y->key = key;
    y->value = value;
}

static xdictionarynode * xmapnodenew(xval key)
{
    xmapnode * node = (xmapnode *) calloc(sizeof(xmapnode), 1);

    node->key = key;
    node->color = xdictionarynodecolor_black;
    node->size = sizeof(xmapnode);

    return (xdictionarynode *) node;
}

extern xmapnode * xmapget(xmap * map, xval key)
{
    return (xmapnode *) xdictionaryget((xdictionary *) map, key);
}

extern xmap * xmaprem(xmap * map, xmapkeyvaluefunc func)
{
    return map->rem(map, func);
}

static void __xmapclear(xmap * map, xmapkeyvaluefunc func)
{
    xmapnode * node = (xmapnode *) xdictionarynodemin_get((xdictionarynode *) map->root);
    if(func)
    {
        while(node)
        {
            if(node->right)
            {
                node = (xmapnode *) xdictionarynodemin_get((xdictionarynode *) node->right);
            }
            else
            {
                xmapnode * parent = node->parent;
                if(parent)
                {
                    if(parent->left == node)
                    {
                        parent->left = xnil;
                    }
                    else
                    {
                        parent->right = xnil;
                    }
                }
                node->parent = xnil;
                func(xaddressof(node->key), xaddressof(node->value));
                free(node);
                node = parent;
            }
        }
    }
    else
    {
        while(node)
        {
            if(node->right)
            {
                node = (xmapnode *) xdictionarynodemin_get((xdictionarynode *) node->right);
            }
            else
            {
                xmapnode * parent = node->parent;
                if(parent)
                {
                    if(parent->left == node)
                    {
                        parent->left = xnil;
                    }
                    else
                    {
                        parent->right = xnil;
                    }
                }
                free(node);
                node = parent;
            }
        }
    }
    map->size = 0;
    map->root = xnil;
}

extern xmap * xmapnew(xdictionarycmp comparator)
{
    xmap * map = (xmap *) xdictionarynew(comparator);

    map->create = xmapnodenew;
    map->clear  = __xmapclear;
    map->swap   = xmapnode_swap;

    return map;
}

extern xmapnode * xmapadd(xmap * map, xval key, xval value, xmapinsertioncallback callback)
{
    xmapnode * prev = xnil;
    xmapnode * node = (xmapnode *) xdictionaryadd((xdictionary *) map, key, (xdictionarynode **) xaddressof(prev));
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

    return prev;
}

extern xint32 xmapdel(xmap * map, xval key, xmapdeletioncallback callback)
{
    xmapnode * node = (xmapnode *) xdictionarydel((xdictionary *) map, key);

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
    xmapnode * node = (xmapnode *) xdictionaryget((xdictionary *) map, key);

    return node != xnil;
}

extern xmap * xmapclear(xmap * map, xmapkeyvaluefunc func)
{
    map->clear(map, func);
}

extern xval xmapnodekey(xmapnode * node)
{
    return node->key;
}

extern xval xmapnodevalue(xmapnode * node)
{
    return node->value;
}

extern xmapnode * xmapbegin(xmap * map)
{
    return (xmapnode *) xdictionarybegin((xdictionary *) map);
}

extern xmapnode * xmapnode_next(xmapnode * node)
{
    return (xmapnode *) xdictionarynode_next((xdictionarynode *) node);
}

extern xuint64 xmapsize(xmap * map)
{
    return map->size;
}

extern xmapnode * xmapnode_left(xmapnode * node)
{
    return node->left;
}

extern xmapnode * xmapnode_right(xmapnode * node)
{
    return node->right;
}