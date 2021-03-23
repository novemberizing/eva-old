#include <stdio.h>
#include <stdlib.h>

#include "../../thread.h"
#include "list.h"
#include "../pool.h"

extern xclientpoollist * xclientpoollist_new(void)
{
    xclientpoollist * list = (xclientpoollist *) calloc(sizeof(xclientpoollist), 1);

    return list;
}

extern xclientpoollist * xclientpoollist_rem(xclientpoollist * list)
{
    if(list)
    {
        xassertion(xtrue, "implement this");

        free(list);
    }
    return list;
}

extern void xclientpoollist_add(xclientpoollist * list, xclientpool * pool)
{
    if(list && pool)
    {
        if(pool->cntr == xnil)
        {
            pool->prev = list->tail;

            if(pool->prev)
            {
                pool->prev->next = pool;
            }
            else
            {
                list->head = pool;
            }
            list->tail = pool;
            list->size = list->size + 1;
        }
        else
        {
            xassertion(pool->cntr == list, "");
        }
    }
}

extern void xclientpoollist_del(xclientpoollist * list, xclientpool * pool)
{
    if(list && pool)
    {
        if(pool->cntr == list)
        {
            xclientpool * prev = pool->prev;
            xclientpool * next = pool->next;
            if(prev)
            {
                prev->next = next;
                pool->prev = xnil;
            }
            else
            {
                list->head = next;
            }
            if(next)
            {
                next->prev = prev;
                pool->next = xnil;
            }
            else
            {
                list->tail = prev;
            }
            list->size = list->size - 1;
            pool->cntr = xnil;
        }
        else
        {
            xassertion(pool->cntr != list, "");
        }
    }
}
