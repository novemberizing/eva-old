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
