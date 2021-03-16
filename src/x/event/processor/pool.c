#include <stdio.h>
#include <stdlib.h>


#include "pool.h"

#include "../engine.h"
#include "../processor.h"
#include "../../thread.h"

/**
 * @fn          extern xeventprocessorpool * xeventprocessorpool_new(xeventengine * engine, xuint64 n)
 * @brief       이벤트 프로세서 풀을 생성합니다.
 * @details     아밴트 프로세서 풀을 생성하고 주어진 갯수만큼 이벤트 프로세서를 생성합니다.
 * 
 * @param       engine | xeventengine * | 이벤트 엔진 |
 * @param       n      | xuint64        | 이벤트 프로세서 갯수 |
 * 
 * @return      | xeventprocessorpool * | 이벤트 프로세서 풀 객체 |
 * 
 * @see         xeventprocessorpool,
 *              xeventengine,
 *              calloc,
 *              xeventprocessorpoll_add
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 * 
 * @exception   | `engine == xnil` | 엔진 객체가 없으면 예외를 발생시킵니다. |
 */
extern xeventprocessorpool * xeventprocessorpool_new(xeventengine * engine, xuint64 n)
{
    xlogfunction_start("%s(%p, %lu)", __func__, engine, n);
    xassertion(engine == xnil, "");

    xeventprocessorpool * o = (xeventprocessorpool *) calloc(sizeof(xeventprocessorpool), 1);

    o->engine = engine;

    xeventprocessorpool_add(o, n);

    xlogfunction_end("%s(...) => %p", __func__, o);
    return o;
}

/**
 * @fn          extern xeventprocessorpool * xeventprocessorpool_rem(xeventprocessorpool * pool)
 * @brief       이벤트 프로세서 풀을 메모리 상에서 제거합니다.
 * @details     이벤트 프로세서 풀 안에 프로세서가 존재하지 않아야 합니다.
 * 
 * @param       pool | xeventprocessorpool * | in | 이벤트 프로세서 풀 |
 * 
 * @return      | xeventprocessorpool * | 이벤트 프로세서 풀로 항상 널을 리턴합니다. |
 * 
 * @see         xeventprocessorpool_removable,
 *              free,
 *              xeventprocessorpool
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xeventprocessorpool * xeventprocessorpool_rem(xeventprocessorpool * pool)
{
    xlogfunction_start("%s(%p)", __func__, pool);
    if(pool)
    {
        xassertion(!xeventprocessorpool_removable(pool), "");

        free(pool);
    }
    xlogfunction_end("%s() => %p", __func__, xnil);
    return xnil;
}

/**
 * @fn          extern void xeventprocessorpool_add(xeventprocessorpool * pool, xuint64 n)
 * @brief       이벤트 프로세서 풀에 이벤트 프로세서를 주어진 갯수 만큼 생성합니다.
 * @details     이벤트 프로세서 풀의 생성은 엔진 객체의 메인 스레드에서 수행되어야 합니다.
 *              또한, 이벤트 프로세서를 생성할 때, 내부 함수에서 풀에 등록하기 때문에,
 *              프로세서 하나의 리턴 값은 생성 여부를 체크하는 것으로 사용할 수 있고,
 *              큰 의미를 두지 않아도 됩니다.
 * 
 * @param       pool | xeventprocessorpool * | in | 이벤트 프로세서 풀 |
 * @param       n    | xuint64               | in | 이벤트 프로세서 풀 갯수 |
 * 
 * @see         xeventprocessorpool,
 *              xeventprocessor_new
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 * 
 */
extern void xeventprocessorpool_add(xeventprocessorpool * pool, xuint64 n)
{
    xlogfunction_start("%s(%p, %lu)", __func__, pool, n);
    for(xuint64 i = 0; i < n; i++)
    {
        xeventprocessor_new(pool);
    }
    xlogfunction_end("%s(...)", __func__);
}

/**
 * @fn          extern void xeventprocessorpool_del(xeventprocessorpool * pool, xuint64 n)
 * @brief       이벤트 프로세서 풀에서 이벤트 프로세서를 삭제합니다.
 * @details     이 함수는 이벤트 엔진의 메인 함수에서 수행되어져야 합니다.
 *              현재 등록된 갯수보다 파라미터가 크다면, 전체를 삭제하게 됩니다.
 *              그리고 이벤트 프로세서는 대기 상태에 있을 수 있기 때문에,
 *              모든 설정을 마친 후에 전체 이벤트 프로세서에 시그널을 전송합니다.
 * 
 * @todo        큰 의미는 없지만 특정 이벤트 프로세서에만 시그널을 전송할 수 있는 방법을 찾아 보자.
 * 
 * @param       pool | xeventprocessorpool * | in | 이벤트 포로세서 풀 객체 |
 * @param       n    | xuint64               | in | 삭제하고자 하는 갯수 |
 * 
 * @see         xeventprocessorpool,
 *              xeventprocessor,
 *              xeventprocessor_cancel,
 *              xeventprocessor_wakeup
 */
extern void xeventprocessorpool_del(xeventprocessorpool * pool, xuint64 n)
{
    xlogfunction_start("%s(%p, %lu)", __func__, pool, n);
    xeventprocessor * processor = pool->head;
    for(xuint64 i = 0; i < n && processor; i++)
    {
        if(processor->cancel == xnil)
        {
            xeventprocessor_cancel(processor);
            // 궁극적으로는 CANCEL 함수에서 엔진의 메인 큐에 REM 을 호출하도록 되어 있다.
            i = i + 1;
        }
        processor = processor->next;
    }

    xeventprocessor_wakeup(pool->engine, xtrue);

    xlogfunction_end("%s(...)", __func__);
}

/**
 * @fn          extern xint32 xeventprocessorpool_removable(xeventprocessorpool * pool)
 * @brief       이벤트 프로세서 풀의 제거 가능 여부를 체크하는 함수
 * @details     객체가 널이거나 혹은 풀에 등록된 크기가 0이면 제거가 가능한 상태입니다.
 * 
 * @param       pool | xeventprocessorpool * | 이벤트 프로세서 풀 객체 |
 * 
 * @return      | xint32 | 이벤트 프로세서 풀 제거 가능 여부 |
 * 
 *                  1(TRUE): 제거 가능
 *                  0(FALSE): 제거 불가능
 * 
 * @see         xeventprocessorpool
 */
extern xint32 xeventprocessorpool_removable(xeventprocessorpool * pool)
{
    xlogfunction_start("%s(%p)", __func__, pool);
    xint32 ret = (pool == xnil || (pool->size == 0));

    xlogfunction_end("%s(...) => %d", __func__, ret);
    return ret;
}

extern xuint64 xeventprocessorpool_size(xeventprocessorpool * pool)
{
    xdebugonly(xlogfunction_start("%s(%p)", __func__, pool));
    xuint64 ret = (pool ? pool->size : 0);
    xdebugonly(xlogfunction_end("%s(...) => %lu", ret));
}

extern void xeventprocessorpool_on(xeventprocessorpool * pool)
{
    xlogfunction_start("%s(%p)", __func__, pool);
    // 프로세서는 생성과 동시에 실행이 된다.

    xlogfunction_end("%s(...)", __func__);
}

/**
 * 프로세서 풀에는 동기화 객체가 존재하지 않는다.
 * 
 * @deprecated
 */
extern void xeventprocessorpool_sync(xeventprocessorpool * pool, xint32 on)
{
    xlogfunction_start("%s(%p, %d)", __func__, pool, on);
    if(on)
    {
        xassertion(pool == xnil, "");
    }
    else
    {
    }
    xlogfunction_end("%s(...)", __func__);
}