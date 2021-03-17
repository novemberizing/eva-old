#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "set.h"

typedef xset * (*xsetdestructor)(xset *, xvalfunc);

struct xset
{
    xsetdestructor         rem;
    xdictionarynode *      root;
    xuint64                size;
    xdictionarynodefactory create;
    xdictionarycmp         compare;
    xsetclearfunc          clear;
    xsync *                sync;
};

static xdictionarynode * xsetnodefactory(xval key)
{
    xdictionarynode * node = (xdictionarynode *) calloc(sizeof(xdictionarynode), 1);

    node->color = xdictionarynodecolor_red;
    node->key   = key;
    
    return node;
}

static void __xsetclear(xset * set, xvalfunc func)
{
    xdictionarynode * node = xdictionarynodemin_get(set->root);
    if(func)
    {
        while(node)
        {
            if(node->right)
            {
                node = xdictionarynodemin_get(node->right);
            }
            else
            {
                xdictionarynode * parent = node->parent;
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
                func(xaddressof(node->key));
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
                node = xdictionarynodemin_get(node->right);
            }
            else
            {
                xdictionarynode * parent = node->parent;
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
    set->size = 0;
    set->root = xnil;
}

extern xset * xsetnew(xdictionarycmp comparator)
{
    xset * set = (xset *) xdictionarynew(comparator);

    set->clear = __xsetclear;

    return set;
}

/**
 * 캡쳐가 동작하지 않으니 조금 ... 고민스럽다.
 */
extern xset * xsetrem(xset * set, xvalfunc func)
{
    return set->rem(set, func);
}

extern void xsetadd(xset * set, xval key)
{
    xdictionaryadd((xdictionary *) set, key, xnil);
}

extern xint32 xsetdel(xset * set, xval key)
{
    xdictionarynode * node = xdictionarydel((xdictionary *) set, key);
    if(node)
    {
        free(node);
        return xtrue;
    }
    return xfalse;
}

extern xint32 xsethas(xset * set, xval key)
{
    xdictionarynode * node = xdictionaryget((xdictionary *) set, key);

    return node != xnil;
}

extern xset * xsetclear(xset * set, xvalfunc func)
{
    set->clear(set, func);
}
