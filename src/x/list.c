#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

#include "list.h"

static xlistnode * xlistnodenew(xlist * list, xval value)
{
    xlistnode * node = (xlistnode *) calloc(sizeof(xlistnode), 1);

    node->list = list;
    node->value = value;

    return node;
}

static xlist * xlistdesctruct(xlist * list)
{
    if(list)
    {
        xassertion(list->size > 0 || list->head || list->tail, "");
        list->sync = xsyncrem(list->sync);
        free(list);
    }
    return list;
}

extern xlist * xlistnew(void)
{
    xlist * list = (xlist *) calloc(sizeof(xlist), 1);
    list->rem = xlistdesctruct;
    return list;
}

extern xlist * xlistrem(xlist * list)
{
    return list->rem(list);
}

extern void xlistdel(xlist * list, xlistnode * node)
{
    if(node)
    {
        if(node->list)
        {
            xlistnode * prev = node->prev;
            xlistnode * next = node->next;
            if(prev)
            {
                prev->next = next;
            }
            else
            {
                list->head = next;
            }
            if(next)
            {
                next->prev = prev;
            }
            else
            {
                list->tail = prev;
            }
            list->size = list->size - 1;
            free(node);
        }
    }
}

extern void xlistpushfront(xlist * list, xval value)
{
    if(list->head)
    {
        xlistnode * node = xlistnodenew(list, value);
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
    }
    else
    {
        list->head = list->tail = xlistnodenew(list, value);
    }
    list->size = list->size + 1;
}

extern void xlistpushback(xlist * list, xval value)
{
    if(list->tail)
    {
        xlistnode * node = xlistnodenew(list, value);
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    else
    {
        list->head = list->tail = xlistnodenew(list, value);
    }
    list->size = list->size + 1;
}

extern xlistnode * xlistpopfront(xlist * list)
{
    xlistnode * node = list->head;
    if(node)
    {
        list->head = node->next;
        if(list->head)
        {
            list->head->prev = xnil;
            node->next = xnil;
        }
        else
        {
            list->tail = xnil;
        }
        node->list = xnil;
        list->size = list->size - 1;
    }
    return node;
}

extern xlistnode * xlistpopback(xlist * list)
{
    xlistnode * node = list->tail;
    if(node)
    {
        list->tail = node->prev;
        if(list->tail)
        {
            list->tail->next = xnil;
            node->prev = xnil;
        }
        else
        {
            list->head = xnil;
        }
        node->list = xnil;
        list->size = list->size - 1;
    }
    return node;
}

extern void xlistinsertfront(xlist * list, xlistnode * node, xval value)
{
    xassertion(list == xnil || node == xnil, "");
    xassertion(list != node->list, "");

    xlistnode * prev = node->prev;
    if(prev)
    {
        xlistnode * o = xlistnodenew(list, value);
        prev->next = o;
        node->prev = o;
        o->prev = prev;
        o->next = node;
    }
    else
    {
        xlistnode * o = xlistnodenew(list, value);
        list->head->prev = o;
        o->next = list->head;
        list->head = o;
    }
    list->size = list->size + 1;
}

extern void xlistinsertback(xlist * list, xlistnode * node, xval value)
{
    xassertion(list == xnil || node == xnil, "");
    xassertion(list != node->list, "");

    xlistnode * next = node->next;
    if(next)
    {
        xlistnode * o = xlistnodenew(list, value);
        next->prev = o;
        node->next = o;
        o->prev = node;
        o->next = next;
    }
    else
    {
        xlistnode * o = xlistnodenew(list, value);
        list->tail->next = o;
        o->prev = list->tail;
        list->tail = o;
    }
    list->size = list->size + 1;
}