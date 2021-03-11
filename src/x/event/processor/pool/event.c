#include "event.h"

#include "../pool.h"
#include "../../processor.h"

/**
 * @fn          extern xeventprocessorpool_event * xeventprocessorpool_event_new(xeventprocessorpool_event_handler handler, xeventprocessorpool * pool)
 * @brief       이벤트 프로세서 풀과 관련된 이벤트를 생성합니다.
 * @details     이벤트 프로세서 풀과 관련된 이벤트는 동적할당으로 생성되기 때문에,
 *              이벤트 수행 완료 시에 이벤트를 삭제해야 합니다.
 * 
 * @param       handler | xeventprocessorpool_event_handler | in | 이벤트 핸들러 |
 * @param       pool    | xeventprocessorpool *             | in | 이벤트 프로세서 풀 |
 * @param       n       | xuint64                           | in | 이벤트 생성, 추가, 삭제 시에만 사용하는 파라미터 |
 * 
 * @return      | xeventprocessorpool_event * | 이벤트 프로세서 풀 이벤트 객체 |
 * 
 * @see         xeventprocessorpool_event,
 *              xeventprocessorpool_event_handler,
 *              xeventprocessorpool,
 *              calloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 *              
 */
extern xeventprocessorpool_event * xeventprocessorpool_event_new(xeventprocessorpool_event_handler handler, xeventprocessorpool * pool, xuint64 n)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, handler, pool, n);
    xeventprocessorpool_event * o = (xeventprocessorpool_event *) calloc(sizeof(xeventprocessorpool_event), 1);

    o->on   = handler;

    o->pool = pool;
    o->n    = n;

    xlogfunction_end("%s(...) => %p", __func__, o);
    return o;
}

/**
 * @fn          extern void xeventprocessorpool_event_handler_add(xeventprocessorpool_event * event)
 * @brief       이벤트 프로세스 풀에 이벤트 프로세스 추가 이벤트 핸들러
 * @details     이벤트 엔진의 메인 스레드에서 수행되어야 하는 핸들러입니다.
 *              다시 수행할 필요가 없으므로 이벤트 처리 후에 이벤트를 메모리 상에서 해제합니다.
 *              언제 생성되는지는 체크할 수 없습니다.
 *              이벤트 프로세서가 생성이되고 실행되면, 자동으로 이벤트를 처리하게 됩니다.
 *              
 * @param       event | xeventprocessorpool_event * | 이벤트 객체 |
 * 
 * @see         xeventprocessorpool_event,
 *              xeventprocessorpool_add,
 *              free
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 */
extern void xeventprocessorpool_event_handler_add(xeventprocessorpool_event * event)
{
    xlogfunction_start("%s(%p)", __func__, event);
    xeventprocessorpool_add(event->pool, event->n);

    free(event);

    xlogfunction_end("%s(...)", __func__);
}

/**
 * @fn          extern void xeventprocessorpool_event_handler_del(xeventprocessorpool_event * event)
 * @brief       이벤트 프로세서 풀에서 이벤트 프로세서 제거 이벤트 핸들러
 * @details     이벤트는 처리 후에 메모리 상에서 해제합니다.
 *              다시 처리해야할 필요가 없기 때문에, 한 번 호출로 이벤트 프로세서 제거를 되었다고 판단합니다.
 *              이벤트 프로세서의 종료 시점은 크게 중요하지 않습니다.
 *              이 핸들러 역시, 정해진 갯수만큼 이벤트 프로세서 취소를 호출하고 그 수행을 성공했다고 판단합니다.
 * 
 * @param       event | xeventprocessorpool_event * | in | 이벤트 프로세스 풀 이벤트 객제 |
 * 
 * @see         xeventprocessorpool_event,
 *              xeventprocessorpool_del,
 *              free
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 */
extern void xeventprocessorpool_event_handler_del(xeventprocessorpool_event * event)
{
    xlogfunction_start("%s(%p)", __func__, event);
    xeventprocessorpool_del(event->pool, event->n);

    free(event);

    xlogfunction_end("%s(...)", __func__);
}
