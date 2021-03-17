#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "map.h"

typedef xmap * (*xmapdestructor)(xmap *, xmapkeyvaluefunc);

struct xmap
{
    xmapdestructor         rem;
    xdictionarynode *      root;
    xuint64                size;
    xdictionarynodefactory create;
    xdictionarycmp         compare;
    xmapclearfunc          clear;
    xsync *                sync;
};

struct xmapnode;

typedef struct xmapnode xmapnode;

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

static xdictionarynode * xmapnodenew(xval key)
{
    xmapnode * node = (xmapnode *) calloc(sizeof(xmapnode), 1);

    node->key = key;
    node->color = xdictionarynodecolor_black;
    node->size = sizeof(xmapnode);

    return (xdictionarynode *) node;
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
}

extern xmap * xmapnew(xdictionarycmp comparator)
{
    xmap * map = (xmap *) xdictionarynew(comparator);

    map->create = xmapnodenew;
    map->clear  = __xmapclear;

    return map;
}

extern void xmapadd(xmap * map, xval key, xval value, xmapinsertioncallback callback)
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