#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#include "../thread.h"

/**
 * @fn          extern xeventqueue * xeventqueue_new(void)
 * @brief       이벤트 큐를 생성합니다.
 * @details     이벤트 큐의 생성 시에 동기화 객체는 생성하지 않습니다.
 * 
 * @return      | xeventqueue * | 이벤트 큐 |
 * 
 * @see         xeventqueue,
 *              calloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 * 
 * @exception   | `queue == xnil` | 생성된 이벤트 큐가 널이면 예외를 발생시킵니다. |
 */
extern xeventqueue * xeventqueue_new(void)
{
    xlogfunction_start("%s()", __func__);
    xeventqueue * queue = (xeventqueue *) calloc(sizeof(xeventqueue), 1);

    xassertion(queue == xnil, "");

    xlogfunction_end("%s(...) => %p", __func__, queue);
    return queue;
}

/**
 * @fn          extern xeventqueue * xeventqueue_rem(xeventqueue * queue)
 * @brief       이벤트 큐를 메모리 상에서 삭제합니다.
 * @details     이벤트 큐의 삭제 시에 이벤트 큐의 데이터가 존재하면 안됩니다.
 * 
 * @param       queue   | xeventqueue * | in | 이벤트 큐 |
 * @return      | xeventqueue * | 삭제된 이벤트 큐 객체로 항상 널을 리턴합니다. |
 * 
 * @see         xsyncrem,
 *              xeventqueue
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 * 
 * @exception   | `queue->size > 0` | 큐에 아이템이 존재하면 예외를 발생시킵니다. |
 */
extern xeventqueue * xeventqueue_rem(xeventqueue * queue)
{
    xlogfunction_start("%s(%p)", __func__, queue);
    if(queue)
    {
        xassertion(queue->size > 0, "");

        queue->sync = xsyncrem(queue->sync);
    }

    xlogfunction_end("%s(...) => %p", __func__, queue);
    return xnil;
}

/**
 * @fn          extern void xeventqueue_push(xeventqueue * queue, xevent * event)
 * @brief       이벤트를 큐에 삽입합니다.
 * @details     스레드 세이프티를 보장하려면 외부에서 LOCK/UNLOCK 을 호출해야 합니다.
 * 
 * @param       queue   | xeventqueue * | 이벤트 큐 |
 * @param       event   | xevent *      | 이벤트 |
 * 
 * @see         xeventqueue,
 *              xevent
 *              
 * @version     0.0.1
 * @date        2021. 02. 19.
 * 
 * @exception   | `queue == xnil`        |
 *              | `event == xnil`        |
 *              | `event->queue != xnil` |
 *              | `event->prev != xnil`  |
 *              | `event->next != xnil`  |
 */
extern void xeventqueue_push(xeventqueue * queue, xevent * event)
{
    xassertion(queue == xnil || event == xnil, "");

    xassertion(event->queue || event->prev || event->next, "");

    event->prev = queue->tail;
    if(event->prev)
    {
        event->prev->next = event;
    }
    else
    {
        queue->head = event;
    }
    queue->tail = event;
    queue->size = queue->size + 1;
}

/**
 * @fn          extern xevent * xeventqueue_pop(xeventqueue * queue)
 * @brief       이벤트 큐에서 데이터를 가지고 옮닙다.
 * @details     스레드 세이프티를 보장하려면, 이 함수를 호출 하는 곳에서 LOCK/UNLOCK
 *              을 호출해야 합니다.
 * 
 * @param       queue | xeventqueue * | in | 이벤트 큐 |
 * @return      | xevent * | 이벤트 |
 *              
 *                  이벤트가 존재하지 않으면 널을 리턴합니다.
 * 
 * @see         xevent,
 *              xeventqueue
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 */
extern xevent * xeventqueue_pop(xeventqueue * queue)
{
    xevent * event = queue->head;

    if(event)
    {
        queue->head = event->next;
        if(queue->head)
        {
            queue->head->prev = xnil;
        }
        else
        {
            queue->tail = xnil;
        }
        queue->size = queue->size - 1;

        event->next  = xnil;
        event->queue = xnil;
    }

    return event;
}

extern void xeventqueue_once(xeventqueue * queue)
{
    xassertion(queue == xnil, "");

    __xsynclock(queue->sync);
    xuint64 total = queue->size;
    for(xuint64 i = 0; i < total; i++)
    {
        xevent * event = xeventqueue_pop(queue);
        if(event)
        {
            __xsyncunlock(queue->sync);
            xassertion(event->on == xnil, "");
            event->on(event);
            __xsynclock(queue->sync);
            continue;
        }
        break;
    }
    __xsyncunlock(queue->sync);
}

extern void xeventqueue_clear(xeventqueue * queue)
{
    __xsynclock(queue->sync);
    while(queue->size > 0)
    {
        xevent * event = xeventqueue_pop(queue);
        __xsyncunlock(queue->sync);
        if(event)
        {
            event->on(event);
        }
        __xsynclock(queue->sync);
    }
    __xsyncunlock(queue->sync);
}
