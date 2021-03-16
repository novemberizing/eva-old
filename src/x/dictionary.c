#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread.h"
#include "dictionary.h"

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
    while(xtrue)
    {
        // parent is not null
        xdictionarynode * node = xnil;
        xdictionarynode * sibling = xnil;
        if(parent->left == node)
        {
            sibling = parent->right;
            if(xdictionarynodecolor_get(sibling) == xdictionarynodecolor_red)
            {
                xdictionarynoderotate_left(dictionary, parent);
                parent = node->parent;
                parent->color = xdictionarynodecolor_red;
                parent->parent->color = xdictionarynodecolor_black;
                sibling = parent->right;
            }
            if(xdictionarynodecolor_get(sibling->right))
            {
                if(xdictionarynodecolor_get(sibling->left))
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
                parent = node->parent;
                parent->color = xdictionarynodecolor_red;
                parent->parent->color = xdictionarynodecolor_black;
                sibling = parent->left;
            }
            if(xdictionarynodecolor_get(sibling->left))
            {
                if(xdictionarynodecolor_get(sibling->right))
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

static xdictionarynode * xdictionarynode_min(xdictionarynode * node)
{
    while(node && node->left)
    {
        node = node->left;
    }
    return node;
}

extern xdictionary * xdictionarynew(xdictionarycmp comparator)
{
    xdictionary * dictionary = (xdictionary *) calloc(sizeof(xdictionary), 1);

    dictionary->compare = comparator;

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
    while(node)
    {
        xint32 diff = dictionary->compare(node->key, key);
        if(diff < 0)
        {
            if(node->right)
            {
                node = node->right;
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
            return o;
        }
        else if(diff > 0)
        {
            if(node->left)
            {
                node = node->left; 
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
    return node;
}

extern xdictionarynode * xdictionarydel(xdictionary * dictionary, xval key)
{
    xdictionarynode * node = xdictionaryget(dictionary, key);
    if(node)
    {
        if(node->left && node->right)
        {
            xdictionarynode * successor = xdictionarynode_min(node->right);

            xdictionarynode * parent = successor->parent;
            xdictionarynode * left = successor->left;
            xdictionarynode * right = successor->right;

            successor->parent = node->parent;
            successor->left = node->left;
            successor->right = node->right;

            node->parent = parent;
            node->left = left;
            node->right = right;

            if(node->right)
            {
                if(parent->left == node)
                {
                    parent->left = node->right;
                }
                else
                {
                    parent->right = node->right;
                }
                node->right->parent = parent;
                node->right = xnil;
                node->parent = xnil;
            }
            else
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
                    xdictionarynodeadjust_deletion(dictionary, node->parent);
                }
                node->parent = xnil;
            }
            dictionary->size = dictionary->size - 1;
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
                    parent->right = node->right;
                    node->right->parent = parent;
                }
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
                    parent->right = node->left;
                    node->left->parent = parent;
                }
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
                    xdictionarynodeadjust_deletion(dictionary, node->parent);
                }
                node->parent = xnil;
            }
            else
            {
                dictionary->root = xnil;
            }
            dictionary->size = dictionary->size - 1;

            return node;
        }
    }
    return node;
}
