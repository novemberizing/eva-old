#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "posix.h"

static void * xthreadposix_routine(void * o);

/**
 * @fn          extern xthreadposix * xthreadposix_rem(xthreadposix * o)
 * @brief       POSIX 스레드를 메모리에서 제거합니다.
 * @details     이 함수는 pthread_join 에서 deadlock 이 발생할 수 있습니다.
 *              스레드의 메모리 해제는 스레드가 종료 상태일 때만 수행되어져야 합니다.
 * 
 *              또한, 스레드 종료 시에 스레드 취소 함수가 수행될 수 있는데,
 *              이러한 경우는 이미 종료된 스레드에 취소가 등록된 경우입니다.
 * 
 * @param       o | xthreadposix * | in | POSIX 스레드 객체 |
 * @return      | xthreadposix * | 언제나 널을 리턴합니다. | 
 * 
 * @exception   | `o == xnil` |
 *              | `xthreadcheck_rem((xthread *) o) == xfalse` |
 *              | `pthread_join(...) != xsuccess` |
 * 
 * @see         xthreadposix
 *              xthreadcheck_rem
 *              pthread_join
 *              xvalueof
 *              xobjectrem
 *              free
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 *              
 */
extern xthreadposix * xthreadposix_rem(xthreadposix * o)
{
    xassertion(o == xnil, "");
    xassertion(xthreadcheck_rem((xthread *) o) == xfalse, "");

    if(o->handle)
    {
        int ret = pthread_join(xvalueof(o->handle), xnil);

        xassertion(ret != xsuccess, "");

        o->handle = xobjectrem(o->handle);

        if(o->cancel)
        {
            o->cancel(o);
            o->cancel = xnil;
        }
    }
    free(o);
    return xnil;
}

/**
 * @fn          extern void xthreadposix_cancel(xthreadposix * o, xthreadposixfunc callback)
 * @brief       스레드 취소를 등록합니다.
 * @details     스레드 취소는 등록하는 것으로 이 함수는 종료됩니다.
 *              스레드 취소를 수행하도록 하려면 사용자가 스레드 함수를 만들 때,
 *              cancel 변수가 널이 아닌 경우 함수를 종료시키도록 로직을 구현해야 합니다.
 * 
 * 
 *              ```
 *              while(thread->cancel == xnil)
 *              {
 *                  ....
 *              }
 *              ```
 * 
 * @param       o | xthreadposix * | in | 스레드 객체 |
 * @param       callback | xthreadposixfunc | in | 스레드 콜백: 널이면 등록된 취소가 취소되는 것입니다. 취소 시키려면 널이 아닌 콜백을 등록해야 합니다. |
 * 
 * @see         xthreadposix
 *              xthreadposixfunc
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 */
extern void xthreadposix_cancel(xthreadposix * o, xthreadposixfunc callback)
{
    if(o->handle)
    {
        o->cancel = callback;
    }
}

/**
 * @fn          extern void xthreadposix_run(xthreadposix * o)
 * @brief       스레드를 실행시킵니다.
 * @details     핸들이 널이 아닌 경우는 스레드 함수를 이미 실행된 스레드로
 *              예외를 발생시킵니다.
 *              
 * @param       o | xthreadposix * | in | 스레드 객체 |
 * 
 * @see         xthreadposix
 *              calloc
 *              pthread_t
 *              xthreadstatus_on
 *              xthreadposix_routine
 *              xobjectrem
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 */
extern void xthreadposix_run(xthreadposix * o)
{
    xassertion(o->handle, "");

    o->handle = calloc(sizeof(pthread_t), 1);
    o->status |= xthreadstatus_on;

    int ret = pthread_create(o->handle, xnil, xthreadposix_routine, o);

    xassertion(ret != xsuccess, "");

    if(ret != xsuccess)
    {
        o->status &= (~xthreadstatus_on);
        o->handle = xobjectrem(o->handle);
    }
}

/**
 * @fn          static void * xthreadposix_routine(void * o)
 * @brief       스레드 루틴입니다.
 * @details     스레드 루틴은 사용자가 등록한 스레드 함수를 수행하고,
 *              그 함수가 종료되면 상태를 OFF 으로 변경 한 후에
 *              cancel 이 등록되어 있다면 cancel 콜백을 수행합니다.
 * 
 * @param       o | void * | in | 스레드 객체 |
 * @return      | void * | 언제나 널을 리턴합니다. |
 * 
 * @see         xthreadposix
 *              xthreadstatus_on
 */
static void * xthreadposix_routine(void * o)
{
    xthreadposix * thread = (xthreadposix *) o;

    thread->func(thread);

    thread->status &= (~xthreadstatus_on);

    if(thread->cancel)
    {
        thread->cancel(thread);
        thread->cancel = xnil;
    }

    return xnil;
}

/**
 * @fn          extern xuint64 xthreadposix_id(void)
 * @brief       현재 스레드의 아이디를 리턴합니다.
 * @details     리눅스는 64 비트 양의 정수형이 아이디입니다.
 *              다른 OS 에 대한 고민을 해야 합니다.
 * 
 * @return      | xuint64 | 스레드 아이디 |
 * 
 * @see         pthread_self
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 */
extern xuint64 xthreadposix_id(void)
{
    return pthread_self();
}
