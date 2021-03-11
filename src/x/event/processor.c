#include <stdio.h>
#include <stdlib.h>

#include "processor.h"

#include "engine.h"

#include "processor/pool.h"
#include "processor/event.h"

#include "../thread.h"

static void xeventprocessor_loop(xeventprocessor * processor);
static void xeventprocessor_exit(xeventprocessor * processor);

/**
 * @fn      extern xeventprocessor * xeventprocessor_new(xeventprocessorpool * pool)
 * @brief   이벤트 프로세서를 생성합니다.
 * @details 이벤트는 생성과 동시에 풀에 등록되며,
 *          자동으로 실행됩니다.
 * 
 * @param   pool | xeventprocessorpool * | in | 이벤트 프로세서 풀 |
 * 
 * @return  | xeventprocessor * | 이벤트 프로세서 객체 |
 * 
 * @exception   `pool == xnil`
 * 
 * @see         xeventprocessorpool,
 *              xeventprocessor,
 *              xthread,
 *              xeventprocessor_loop,
 *              xthreadrun,
 *              calloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xeventprocessor * xeventprocessor_new(xeventprocessorpool * pool)
{
    xlogfunction_start("%s(%p)", __func__, pool);

    xassertion(pool == xnil, "");

    xeventprocessor * processor = (xeventprocessor *) calloc(sizeof(xeventprocessor), 1);

    processor->func             = xeventprocessor_loop;
    processor->pool             = pool;

    processor->prev             = pool->tail;
    if(processor->prev)
    {
        processor->prev->next   = processor;
    }
    else
    {
        pool->head              = processor;
    }
    pool->size                  = pool->size + 1;

    xthreadrun((xthread *) processor);

    xlogfunction_end("%s(...) => %p", __func__, processor);
    return processor;
}

/**
 * @fn          extern xeventprocessor * xeventprocessor_rem(xeventprocessor * processor)
 * @brief       이벤트 프로세서를 메모리 상에서 제거합니다.
 * @details     이벤트 포로세서를 메모리 상에서 제거 하기 전에, 이벤트 포로세서가 속해 있는 풀에서 제거하고, 스레드를 종료합니다.
 *              이벤트 프로세서는 이미 종료되어서, 제거 가능한 상태여야 합니다.
 * 
 * @param       processor | xeventprocessor * | in | 이벤트 프로세서 객체 |
 * @return      | xeventprocessor * | 항상 널을 리턴합니다. |
 * 
 * @exception   `xthreadcheck_rem(processor) == xfalse`
 *              `processor == xnil`
 * 
 * @see         xthreadcheck_rem,
 *              xthreadrem,
 *              xeventprocessorpool,
 *              xeventprocessor,
 *              xthread
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xeventprocessor * xeventprocessor_rem(xeventprocessor * processor)
{
    xlogfunction_start("%s(%p)", __func__, processor);
    xassertion(processor == xnil, "");
    xassertion(xthreadcheck_rem((xthread *) processor) == xfalse, "");

    xeventprocessorpool * pool = processor->pool;

    if(pool)
    {
        xeventprocessor * prev = processor->prev;
        xeventprocessor * next = processor->next;

        if(prev)
        {
            prev->next = next;
        }
        else
        {
            pool->head = next;
        }

        if(next)
        {
            next->prev = prev;
        }
        else
        {
            pool->tail = prev;
        }

        pool->size = pool->size - 1;
    }

    xeventprocessor * ret = (xeventprocessor *) xthreadrem((xthread *) processor);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

/**
 * @fn          extern void xeventprocessor_cancel(xeventprocessor * processor)
 * @brief       이벤트 프로세서를 종료합니다.
 * @details     이벤트 프로세서의 종료는 이벤트 엔진의 메인 프로세서에서 동작합니다.
 *              즉, 이 함수를 호출한다고 하여도 이벤트 프로세서가 바로 종료되지 않습니다.
 *              이 함수는 호출하면 `cancel` 함수가 등록되는 것으로 끝나게 됩니다.
 * 
 * @param       processor | xeventprocessor * | in | 이벤트 프로세서 |
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 * 
 * @see         xeventprocessor,
 *              xeventprocessor_exit
 */
extern void xeventprocessor_cancel(xeventprocessor * processor)
{
    xlogfunction_start("%s(%p)", __func__, processor);
    if(processor->handle)
    {
        processor->cancel = xeventprocessor_exit;
    }

    xlogfunction_end("%s(...)", __func__);
}

/**
 * @fn          extern void xeventprocessor_wakeup(xeventengine * engine, xint32 all)
 * @brief       이벤트 프로세스를 깨웁니다.
 * @details     처리할 이벤트가 존재하지 않아서, 종료 중인 이벤트 프로세스가 존재하면
 *              이벤트 프로세스를 깨웁니다.
 * 
 * @param       engine | xeventengine * | in | 이벤트 엔진 객체 |
 * @param       all    | xint32         | in | 단일 혹은 전체 프로세서 시그널 전송 파라미터 |
 * 
 * @see         xeventengine,
 *              __xsynclock,
 *              __xsyncwakeup,
 *              __xsyncunlock
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 * 
 * @exception   | `engine == xnil` | 엔진 객체가 널이면 예외를 발생시킵니다. |
 */
extern void xeventprocessor_wakeup(xeventengine * engine, xint32 all)
{
    xlogfunction_start("%s(%p, %d)", __func__, engine, all);
    xassertion(engine == xnil, "");

    __xsynclock(engine->queue->sync);
    __xsyncwakeup(engine->queue->sync, all);
    __xsyncunlock(engine->queue->sync);

    xlogfunction_end("%s(...)", __func__);
}

/**
 * @fn      static void xeventprocessor_loop(xeventprocessor * processor)
 * @brief   이벤트 프로세서의 루프 함수입니다.
 * @details 이벤트 프로세서의 루프함수는 프로세스가 취소 상태가 아니면
 *          큐에서 이벤트를 꺼내서 처리하는 로직을 계속 수행합니다.
 *          큐에 이벤트가 존재하지 않으면 이벤트가 존재할 때까지 대기 상태에 머무르게 됩니다.
 * 
 * @param   processor   | xeventprocessor * | 이벤트 프로세스 객체 |
 * 
 *              이벤트 프로세스 객체의 멤버로 이벤트 프로세서가 속한
 *              프로세스 풀과 이벤트 엔진의 참조가 멤버로 속해 있습니다.
 * 
 * @see     xeventprocessor,
 *          xeventprocessorpool,
 *          xeventengine,
 *          xeventqueue,
 *          __xsynclock,
 *          __xsyncwait,
 *          __xsyncunlock,
 *          xeventqueue_pop,
 *          
 * @version 0.0.1
 * @date    2021. 02. 18.
 */
static void xeventprocessor_loop(xeventprocessor * processor)
{
    xlogfunction_start("%s(%p)", __func__, processor);

    xeventprocessorpool * pool = processor->pool;
    xeventengine *      engine = pool->engine;
    xeventqueue *        queue = engine->queue;
    
    while(processor->cancel == xnil)
    {
        __xsynclock(queue->sync);
        if(queue->size == 0)
        {
            __xsyncwait(queue->sync, 0, 0);
            if(processor->cancel)
            {
                __xsyncunlock(queue->sync);
                break;
            }
        }
        xevent * event = xeventqueue_pop(queue);
        __xsyncunlock(queue->sync);
        if(event)
        {
            event->on(event);
        }
    }

    xlogfunction_end("%s(...)", __func__);
}

/**
 * @fn      static void xeventprocessor_exit(xeventprocessor * processor)
 * @brief   이벤트 프로세서 객체의 종료 이벤트를 이벤트 엔진의 메인 큐에 삽입합니다.
 * @details 이벤트 포로세서의 종료는 항상 메인에서 수행되어야 합니다.
 *          
 * @param   processor | xeventprocessor * | 이벤트 프로세서 객체 |
 * 
 * @see     xeventprocessorpool,
 *          xeventengine,
 *          xeventprocessor_event,
 *          xeventprocessor_event_new,
 *          xeventprocessor_event_handler_rem,
 *          xeventengine_main_push
 * 
 * @version 0.0.1
 * @date    2021. 02. 19.
 */
static void xeventprocessor_exit(xeventprocessor * processor)
{
    xlogfunction_start("%s(%p)", __func__, processor);

    xeventprocessorpool *    pool = processor->pool;
    xeventengine *         engine = pool->engine;
    xeventprocessor_event * event = xeventprocessor_event_new(xeventprocessor_event_handler_rem, processor);


    xeventengine_main_push(engine, (xevent *) event);

    xlogfunction_end("%s(...)", __func__);
}