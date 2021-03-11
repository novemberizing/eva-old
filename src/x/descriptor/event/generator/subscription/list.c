#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#include "../../subscription.h"

#include "../../../../thread.h"

/**
 * @fn          extern xdescriptoreventgeneratorsubscriptionlist * xdescriptoreventgeneratorsubscriptionlist_new(void)
 * @brief       디스크립터 이벤트 제네레이터 서브스크립션 리스트를 생성합니다.
 * @details     
 * 
 * @return      | xdescriptoreventgeneratorsubscriptionlist * | 디스크립터 이벤트 제네레이터 서브스크립션 리스트 |
 * 
 * @see         xdescriptoreventgeneratorsubscriptionlist
 *              calloc
 */
extern xdescriptoreventgeneratorsubscriptionlist * xdescriptoreventgeneratorsubscriptionlist_new(void)
{
    xlogfunction_start("%s()", __func__);
    xdescriptoreventgeneratorsubscriptionlist * list = calloc(sizeof(xdescriptoreventgeneratorsubscriptionlist), 1);

    xassertion(list == xnil, "");

    xlogfunction_end("%s(...) => %p", list);
    return list;
}

extern xdescriptoreventgeneratorsubscriptionlist * xdescriptoreventgeneratorsubscriptionlist_rem(xdescriptoreventgeneratorsubscriptionlist * list)
{
    xlogfunction_start("%s(%p)", __func__, list);
    xassertion(list == xnil || list->size > 0, "");

    list->sync = xsyncrem(list->sync);
    free(list);
    
    xlogfunction_end("%s(...) => %p", __func__, xnil);
    return xnil;
}

extern void xdescriptoreventgeneratorsubscriptionlist_push(xdescriptoreventgeneratorsubscriptionlist * list, xdescriptoreventsubscription * subscription)
{
    xlogfunction_start("%s(%p, %p)", __func__, list, subscription);

    xassertion(list == xnil || subscription == xnil, "list => %p, subscription => %p", list, subscription);
    xassertion(subscription->generatornode.generator == xnil, "subscription->generatornode.generator => %p", subscription->generatornode.generator);
    xassertion(subscription->generatornode.list || subscription->generatornode.prev || subscription->generatornode.next, "");

    subscription->generatornode.prev = list->tail;
    if(subscription->generatornode.prev)
    {
        subscription->generatornode.prev->generatornode.next = subscription;
    }
    else
    {
        list->head = subscription;
    }
    subscription->generatornode.list = list;
    list->tail = subscription;
    list->size = list->size + 1;

    xlogfunction_end("%s(...)", __func__);
}

extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptionlist_del(xdescriptoreventsubscription * subscription)
{
    xlogfunction_start("%s(%p)", __func__, subscription);
    xassertion(subscription == xnil || subscription->generatornode.generator == xnil || subscription->generatornode.list == xnil, "");

    xdescriptoreventgeneratorsubscriptionlist * list = subscription->generatornode.list;

    __xsynclock(list->sync);
    xdescriptoreventsubscription *              prev = subscription->generatornode.prev;
    xdescriptoreventsubscription *              next = subscription->generatornode.next;

    if(prev)
    {
        prev->generatornode.next = next;
        subscription->generatornode.prev = xnil;
    }
    else
    {
        list->head = next;
    }
    if(next)
    {
        next->generatornode.prev = prev;
        subscription->generatornode.next = xnil;
    }
    else
    {
        list->tail = prev;
    }
    list->size = list->size - 1;
    subscription->generatornode.list = xnil;

    __xsyncunlock(list->sync);

    xlogfunction_end("%s(...) => %p", __func__, next);
    return next;
}

extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptionlist_pop(xdescriptoreventgeneratorsubscriptionlist * list)
{
    xlogfunction_start("%s(%p)", __func__, list);
    xassertion(list == xnil, "");
    xdescriptoreventsubscription * subscription = list->head;
    if(subscription)
    {
        list->head = subscription->generatornode.next;
        if(list->head)
        {
            list->head->generatornode.prev = xnil;
            subscription->generatornode.next = xnil;
        }
        else
        {
            list->tail = xnil;
        }
        list->size = list->size - 1;
        subscription->generatornode.list = xnil;
    }

    xlogfunction_end("%s(...) => %p", __func__, subscription);
    return subscription;
}
