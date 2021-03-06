#include <stdio.h>
#include <stdlib.h>

#include "event.h"

#include "../engine.h"
#include "../processor.h"
#include "../processor/pool.h"
#include "../../descriptor.h"
#include "../../thread.h"

/**
 * @fn          extern xeventprocessor_event * xeventprocessor_event_new(xeventprocessor_event_handler handler, xeventprocessor * processor)
 * @brief       이벤트 프로세서와 관련된 이벤트를 생성합니다.
 * @details     이 이벤트는 동적할당으로 생성되기 때문에 반드시 해제를 해주어야 합니다.
 * 
 * @param       handler   | xeventprocessor_event_handler | in | 이벤트 핸들러 |
 * @param       processor | xeventprocessor *             | in | 이벤트 프로세서 |
 * 
 * @return      | xeventprocessor_event * | 이벤트 프로세서 이벤트 객체 |
 * 
 * @see         xeventprocessor_event_handler,
 *              xeventprocessor,
 *              xeventprocessor_event,
 *              calloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xeventprocessor_event * xeventprocessor_event_new(xeventprocessor_event_handler handler, xeventprocessor * processor)
{
    xeventprocessor_event * o = (xeventprocessor_event *) calloc(sizeof(xeventprocessor_event), 1);

    o->on        = handler;
    o->processor = processor;

    return o;
}

/**
 * @fn          extern void xeventprocessor_event_rem(xeventprocessor_event * event)
 * @brief       이벤트 프로세서 종료 핸들러
 * @details     이벤트 프로세서는 이벤트 엔진의 메인 스레드에서 처리되어야 합니다.
 *              그렇기 때문에, 다시 시도가 필요한 경우, 즉 이벤트 프로세서가 제거 가능 상태가 아닌 경우
 *              메인 이벤트 큐에 현재의 이벤트를 다시 삽입합니다.
 *              제거가 가능한 경우 이벤트 프로세서를 제거하고 메모리 상에서 객체를 해제합니다.
 * 
 * @param       event | xeventprocessor_event * | in | 이벤트 프로세서 객체 |
 */
extern void xeventprocessor_event_handler_rem(xeventprocessor_event * event)
{
    xeventprocessor * processor = event->processor;
    
    if(xthreadcheck_rem((xthread *) processor))
    {
        xeventprocessor_rem(processor);

        free(event);
    }
    else
    {
        xeventprocessorpool * pool = processor->pool;
        xeventengine * engine = pool->engine;
        xeventengine_main_push(engine, (xevent *) event);
    }
}