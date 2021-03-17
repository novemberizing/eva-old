#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread.h"
#include "dictionary.h"

#include "list.h"

static void xdictionarynode_swap(xdictionarynode * x, xdictionarynode * y)
{
    xval key = x->key;
    x->key = y->key;
    y->key = key;
}

extern xdictionarynode * xdictionarybegin(xdictionary * dictionary)
{
    return xdictionarynodemin_get(dictionary->root);
}

extern xdictionarynode * xdictionarynode_next(xdictionarynode * node)
{
    if(node->right)
    {
        return xdictionarynodemin_get(node->right);
    }
    else
    {
        xdictionarynode * parent = node->parent;
        if(parent)
        {
            if(parent->left == node)
            {
                return parent;
            }
            while(parent && parent->right == node)
            {
                node = parent;
                parent = parent->parent;
            }
            if(parent)
            {
                if(parent->left == node)
                {
                    return parent;
                }
                return xnil;
            }
        }
    }
    return xnil;
}

static xint32 __xdictionaryvalid(xdictionary * dictionary)
{
    if(dictionary->root)
    {
        xassertion(dictionary->root->color != xdictionarynodecolor_black, "");
        dictionary->root->reserved = 1;
        xuint32 blacknodecount = 0;
        xuint32 blacknodecountmax = 0;
        xdictionarynode * prev = xnil;
        
        for(xdictionarynode * node = xdictionarybegin(dictionary); node != xnil; node = xdictionarynode_next(node))
        {
            if(node->left == xnil && node->right == xnil)
            {
                blacknodecount = (node->color == xdictionarynodecolor_black ? 1 : 0);
                xdictionarynode * parent = node->parent;
                while(parent)
                {
                    blacknodecount = blacknodecount + (parent->color == xdictionarynodecolor_black ? 1 : 0);
                    if(parent->color == xdictionarynodecolor_red)
                    {
                        if(parent->left)
                        {
                            xassertion(parent->left->color == xdictionarynodecolor_red, "");
                        }
                        if(parent->right)
                        {
                            xassertion(parent->right->color == xdictionarynodecolor_red, "");
                        }
                    }
                    parent = parent->parent;
                }
                if(blacknodecountmax == 0)
                {
                    blacknodecountmax = blacknodecount;
                }
                else
                {
                    xassertion(blacknodecountmax != blacknodecount, "blacknodecountmax: %u, blacknodecount: %u", blacknodecountmax, blacknodecount);
                }
                if(prev == xnil)
                {
                    prev = node;
                }
                else
                {
                    xassertion(prev->key.i64 >= node->key.i64, "");
                }
            }
            // printf("%lu ", node->key.u64);
        }
        // printf("\n");
    }
}

#define xdictionaryvalid(dictionary)    __xdictionaryvalid(dictionary)


static xdictionary * xdictionarydestruct(xdictionary * dictionary, xdictionarynodefunc func)
{
    if(dictionary)
    {
        xdictionaryclear(dictionary, func);
        dictionary->sync = xsyncrem(dictionary->sync);
        free(dictionary);
    }
    return xnil;
}

static xint32 xdictionarynodecolor_get(xdictionarynode * node)
{
    return node ? node->color : xdictionarynodecolor_black;
}

static xdictionarynode * xdictionarynoderotate_left(xdictionary * dictionary, xdictionarynode * node)
{
    xdictionarynode * parent = node->parent;
    xdictionarynode * right  = node->right;
    xassertion(right == xnil, "");
    xdictionarynode * left   = right->left;

    right->left = node;
    node->parent = right;

    if(left)
    {
        left->parent = node;
    }
    node->right = left;

    if(parent)
    {
        if(parent->left == node)
        {
            parent->left = right;
        }
        else
        {
            parent->right = right;
        }
    }
    else
    {
        dictionary->root = right;
        dictionary->root->color = xdictionarynodecolor_black;
    }
    right->parent = parent;

    return right;
}

static xdictionarynode * xdictionarynoderotate_right(xdictionary * dictionary, xdictionarynode * node)
{
    xdictionarynode * parent = node->parent;
    xdictionarynode * left = node->left;
    xassertion(left == xnil, "");
    xdictionarynode * right = left->right;

    left->right = node;
    node->parent = left;

    if(right)
    {
        right->parent = node;
    }
    node->left = right;

    if(parent)
    {
        if(parent->left == node)
        {
            parent->left = left;
        }
        else
        {
            parent->right = left;
        }
    }
    else
    {
        dictionary->root = left;
        dictionary->root->color = xdictionarynodecolor_black;
    }
    left->parent = parent;

    return left;
}

static void xdictionarynodeadjust_insertion(xdictionary * dictionary, xdictionarynode * node)
{
    while(xtrue)
    {
        if(xdictionarynodecolor_get(node) == xdictionarynodecolor_black)
        {
            break;
        }
        if(xdictionarynodecolor_get(node->parent) == xdictionarynodecolor_black)
        {
            if(node->parent == xnil)
            {
                node->color = xdictionarynodecolor_black;
                dictionary->root = node;
            }
            break;
        }
        
        xdictionarynode * parent = node->parent;
        xdictionarynode * grandparent = parent->parent;
        xdictionarynode * uncle = grandparent->left == parent ? grandparent->right : grandparent->left;

        if(grandparent->left == parent)
        {
            uncle = grandparent->right;
            if(xdictionarynodecolor_get(uncle) == xdictionarynodecolor_red)
            {
                parent->color = xdictionarynodecolor_black;
                uncle->color = xdictionarynodecolor_black;
                grandparent->color = xdictionarynodecolor_red;
                node = grandparent;
                continue;
            }
            if(parent->right == node)
            {
                parent = xdictionarynoderotate_left(dictionary, parent);
                node = parent->left;
            }
            grandparent = xdictionarynoderotate_right(dictionary, grandparent);
            grandparent->color = xdictionarynodecolor_black;
            uncle = grandparent->right;
            uncle->color = xdictionarynodecolor_red;
            break;
        }
        else
        {
            uncle = grandparent->left;
            if(xdictionarynodecolor_get(uncle) == xdictionarynodecolor_red)
            {
                parent->color = xdictionarynodecolor_black;
                uncle->color = xdictionarynodecolor_black;
                grandparent->color = xdictionarynodecolor_red;
                node = grandparent;
                continue;
            }
            if(parent->left == node)
            {
                parent = xdictionarynoderotate_right(dictionary, parent);
                node = parent->right;
            }
            grandparent = xdictionarynoderotate_left(dictionary, grandparent);
            grandparent->color = xdictionarynodecolor_black;
            uncle = grandparent->left;
            uncle->color = xdictionarynodecolor_red;
            break;
        }
    }
}

static void xdictionarynodeadjust_deletion(xdictionary * dictionary, xdictionarynode * parent)
{
    xdictionarynode * node = xnil;
    xdictionarynode * sibling = xnil;
    while(xtrue)
    {
        sibling = parent->right;
        if(sibling != node)
        {
            if(xdictionarynodecolor_get(sibling) == xdictionarynodecolor_red)
            {
                xdictionarynoderotate_left(dictionary, parent);
                parent->color = xdictionarynodecolor_red;
                parent->parent->color = xdictionarynodecolor_black;
                sibling = parent->right;
            }
            if(xdictionarynodecolor_get(sibling->right) == xdictionarynodecolor_black)
            {
                if(xdictionarynodecolor_get(sibling->left) == xdictionarynodecolor_black)
                {
                    sibling->color = xdictionarynodecolor_red;
                    if(xdictionarynodecolor_get(parent) == xdictionarynodecolor_red)
                    {
                        parent->color = xdictionarynodecolor_black;
                    }
                    else
                    {
                        node = parent;
                        parent = node->parent;
                        if(parent)
                        {
                            continue;
                        }
                    }
                    break;
                }
                sibling = xdictionarynoderotate_right(dictionary, sibling);
            }
            xdictionarynoderotate_left(dictionary, parent);
            sibling->color = parent->color;
            sibling->right->color = xdictionarynodecolor_black;
            parent->color = xdictionarynodecolor_black;
            break;
        }
        else
        {
            sibling = parent->left;
            if(xdictionarynodecolor_get(sibling) == xdictionarynodecolor_red)
            {
                xdictionarynoderotate_right(dictionary, parent);
                parent->color = xdictionarynodecolor_red;
                parent->parent->color = xdictionarynodecolor_black;
                sibling = parent->left;
            }
            if(xdictionarynodecolor_get(sibling->left) == xdictionarynodecolor_black)
            {
                if(xdictionarynodecolor_get(sibling->right) == xdictionarynodecolor_black)
                {
                    sibling->color = xdictionarynodecolor_red;
                    if(xdictionarynodecolor_get(parent) == xdictionarynodecolor_red)
                    {
                        parent->color = xdictionarynodecolor_black;
                    }
                    else
                    {
                        node = parent;
                        parent = node->parent;
                        if(parent)
                        {
                            continue;
                        }
                    }
                    break;
                }
                sibling = xdictionarynoderotate_left(dictionary, sibling);
            }
            xdictionarynoderotate_right(dictionary, parent);
            sibling->color = parent->color;
            sibling->left->color = xdictionarynodecolor_black;
            parent->color = xdictionarynodecolor_black;
            break;
        }
    }
}

extern xdictionarynode * xdictionarynodemin_get(xdictionarynode * node)
{
    while(node && node->left)
    {
        node = node->left;
    }
    return node;
}

static xdictionarynode * xdictionarynodenew(xval key)
{
    xdictionarynode * node = (xdictionarynode *) calloc(sizeof(xdictionarynode), 1);

    node->key = key;
    node->color = xdictionarynodecolor_red;
    node->size = sizeof(xdictionarynode);

    return node;
}

extern xint32 xdictionarycompare(xval x, xval y)
{
    return (xint32) x.i64 - y.i64;
}

extern xdictionary * xdictionarynew(xdictionarycmp comparator)
{
    xdictionary * dictionary = (xdictionary *) calloc(sizeof(xdictionary), 1);

    dictionary->rem = xdictionarydestruct;
    dictionary->compare = comparator ? comparator : xdictionarycompare;
    dictionary->create = xdictionarynodenew;
    dictionary->swap = xdictionarynode_swap;

    return dictionary;
}

extern xdictionarynode * xdictionaryget(xdictionary * dictionary, xval key)
{
    xdictionarynode * node = dictionary->root;

    while(node)
    {
        xint32 diff = dictionary->compare(node->key, key);
        if(diff < 0)
        {
            node = node->right;

        }
        else if(diff > 0)
        {
            node = node->left;
        }
        else
        {
            return node;
        }
    }
    return node;
}

extern xdictionarynode * xdictionaryadd(xdictionary * dictionary, xval key, xdictionarynode ** prev)
{
    xdictionarynode * node = dictionary->root;
    if(node)
    {
        while(node)
        {
            xint32 diff = dictionary->compare(node->key, key);
            if(diff < 0)
            {
                if(node->right)
                {
                    node = node->right;
                    continue;
                }
                xdictionarynode * o = dictionary->create(key);
                o->color = xdictionarynodecolor_red;
                o->parent = node;
                node->right = o;
                xdictionarynodeadjust_insertion(dictionary, o);
                dictionary->size = dictionary->size + 1;
                if(prev)
                {
                    *prev = xnil;
                }
                xdictionaryvalid(dictionary);
                return o;
            }
            else if(diff > 0)
            {
                if(node->left)
                {
                    node = node->left;
                    continue;
                }
                xdictionarynode * o = dictionary->create(key);
                o->color = xdictionarynodecolor_red;
                o->parent = node;
                node->left = o;
                xdictionarynodeadjust_insertion(dictionary, o);
                dictionary->size = dictionary->size + 1;
                if(prev)
                {
                    *prev = xnil;
                }
                xdictionaryvalid(dictionary);
                return o;
            }
            else
            {
                if(prev)
                {
                    *prev = node;
                }
                return node;
            }
        }
    }
    else
    {
        dictionary->root = dictionary->create(key);
        dictionary->root->color = xdictionarynodecolor_black;
        dictionary->size = dictionary->size + 1;
        xdictionaryvalid(dictionary);
        return dictionary->root;
    }
    
    return node;
}

extern xdictionarynode * xdictionarydel(xdictionary * dictionary, xval key)
{
    xdictionarynode * node = xdictionaryget(dictionary, key);
    if(node)
    {
        // printf("node->key => %lu\n", node->key.u64);
        if(node->left && node->right)
        {
            xdictionarynode * successor = xdictionarynodemin_get(node->right);

            dictionary->swap(node, successor);

            if(successor->right)
            {
                xassertion(successor->right->color == xdictionarynodecolor_black, "");
                if(successor->parent->left == successor)
                {
                    successor->parent->left = successor->right;
                }
                else
                {
                    successor->parent->right = successor->right;
                }
                successor->right->color = xdictionarynodecolor_black;
                successor->right->parent = successor->parent;
                successor->right = xnil;
                successor->parent = xnil;
            }
            else
            {
                if(successor->parent->left == successor)
                {
                    successor->parent->left = xnil;
                }
                else
                {
                    successor->parent->right = xnil;
                }
                if(successor->color == xdictionarynodecolor_black)
                {
                    // PROBLEM
                    printf("= A =\n");
                    xdictionarynodeadjust_deletion(dictionary, successor->parent);
                }
                successor->parent = xnil;
            }
            dictionary->size = dictionary->size - 1;
            xdictionaryvalid(dictionary);
            return successor;
        }
        else if(node->left)
        {
            xdictionarynode * parent = node->parent;
            if(parent)
            {
                if(parent->left == node)
                {
                    parent->left = node->left;
                    node->left->parent = parent;
                }
                else
                {
                    parent->right = node->left;
                    node->left->parent = parent;
                }
                node->left->color = xdictionarynodecolor_black;
                node->parent = xnil;
            }
            else
            {
                dictionary->root = node->left;
                dictionary->root->color = xdictionarynodecolor_black;
                dictionary->root->parent = xnil;
            }
            node->left = xnil;
            dictionary->size = dictionary->size - 1;
            xdictionaryvalid(dictionary);
            return node;
        }
        else if(node->right)
        {
            // SINGLE NODE MUST RED - BECAUSE BLACK NODE COUNT IS NOT SAME
            xdictionarynode * parent = node->parent;
            if(parent)
            {
                if(parent->left == node)
                {
                    parent->left = node->right;
                    node->right->parent = parent;
                }
                else
                {
                    parent->right = node->right;
                    node->right->parent = parent;
                }
                node->right->color = xdictionarynodecolor_black;
                node->parent = xnil;
            }
            else
            {
                dictionary->root = node->right;
                dictionary->root->color = xdictionarynodecolor_black;
                dictionary->root->parent = xnil;
            }
            node->right = xnil;
            dictionary->size = dictionary->size - 1;
            xdictionaryvalid(dictionary);
            return node;
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
                if(node->color == xdictionarynodecolor_black)
                {
                    printf("= B =\n");
                    xdictionarynodeadjust_deletion(dictionary, node->parent);
                }
                node->parent = xnil;
            }
            else
            {
                dictionary->root = xnil;
            }
            dictionary->size = dictionary->size - 1;
            xdictionaryvalid(dictionary);
            return node;
        }
    }
    xdictionaryvalid(dictionary);
    return node;
}

extern xdictionary * xdictionaryrem(xdictionary * dictionary, xdictionarynodefunc func)
{
    if(dictionary)
    {
        dictionary->rem(dictionary, func);
    }
    return xnil;
}

static void __xdictionaryclear(xdictionary * dictionary, xdictionarynodefunc func)
{
    xdictionarynode * node = xdictionarynodemin_get(dictionary->root);
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
                func(node);
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
    dictionary->size = 0;
    dictionary->root = xnil;
}

extern void xdictionaryclear(xdictionary * dictionary, xdictionarynodefunc func)
{
    if(dictionary->clear)
    {
        dictionary->clear(dictionary, func);
    }
    else
    {
        __xdictionaryclear(dictionary, func);
    }
}