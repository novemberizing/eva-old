/**
 * @fn          x/thread.c
 * @brief       스레드 표준 라이브러리 구현 파일입니다.
 * @details     스레드의 구현은 운영체제마다 상이하기 때문에,
 *              운영체제별로 구현된 함수를 호출하도록 합니다.
 *              현재는 POSIX 스레드로 구현이 되어 있습니다.
 * 
 * @version     0.0.1
 * @date        2021. 02. 25.
 */
#include <stdlib.h>
#include <stdio.h>

#include "thread.h"
#include "sync.h"

#include "thread/posix.h"

/**
 * @fn          extern xthread * xthreadnew(xthreadfunc func, xuint64 size)
 * @brief       스레드 객체를 생성합니다.
 * @details     사용자가 재정의한 스레드 객체의 경우 그 객체의 크기를 파라미터로 전달해야 합니다.
 *              사이즈는 `sizeof(xthread)` 보다 크거나 같아야 합니다.
 * 
 * @param       func | xthreadfunc | in | 스레드 함수 |
 * @param       size | xuint64     | in | 스레드 객체의 실제 크기로 `sizeof(xthread)` 보다 커야 합니다. |
 * 
 * @return      | xthread * | 스레드 객체 주소 |
 * 
 * @exception   | `func == xnil`          |
 *              | `size < sizeof(xthread) |
 * 
 * @see         xthread
 *              xthreadfunc
 *              calloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 *              
 */
extern xthread * xthreadnew(xthreadfunc func, xuint64 size)
{
    xlogfunction_start("%s(%p, %lu)", __func__, func, size);

    xassertion(func == xnil || size < sizeof(xthread), "");

    xthread * o = (xthread *) calloc(size, 1);

    o->func     = func;

    xlogfunction_end("%s(...) => %p", __func__, o);
    return o;
}

/**
 * @fn          extern xthread * xthreadrem(xthread * o)
 * @brief       스레드를 메모리 상에서 해제합니다.
 * @details     OS 에 알맞는 스레드 객체 해제 함수를 호출합니다.
 * 
 * @param       o | xthread * | in | 스레드 객체 |
 * @return      | xthread * | 언제나 널을 리턴합니다. 메모리에서 해제되었기 때문입니다. |
 * 
 * @see         xthread
 *              xthreadposix_rem
 *              xthreadposix
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 * 
 */
extern xthread * xthreadrem(xthread * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xthread * ret = (xthread *) xthreadposix_rem((xthreadposix *) o);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

/**
 * @fn          extern xint32 xthreadcheck_rem(xthread * o)
 * @brief       스레드가 종료될 수 있음을 체크합니다.
 * @details     스레드는 그 상태가 OFF 이어야만 제거될 수 있습니다.
 *              
 * @param       o | xthread * | in | 스레드 객체 |
 * 
 * @return      | xint32 | 스레드 제거 가능 여부 |
 * 
 *                  1(TRUE): 스레드 제거 가능
 *                  0(FALSE): 스레드 제거 불가능 (현재 동작 중)
 * 
 * @see         xthread
 *              xthreadstatus_on
 *              xthreadstatus_void
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 */
extern xint32 xthreadcheck_rem(xthread * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xint32 ret = (o->status & xthreadstatus_on) == xthreadstatus_void;

    xlogfunction_end("%s(...) => %d", __func__, ret);
    return ret;
}

/**
 * @fn          extern void xthreadcancel(xthread * o, xthreadfunc callback)
 * @brief       스레드 취소 상태 및 콜백을 등록합니다.
 * @details     스레드의 취소 상태와 콜백이 등록되었다고 하여서 스레드가 바로 종료되는 것은 아닙니다.
 *              또한, 스레드 구현 시에 사용자가 cancel 상태를 무시하고 함수를 정의하면,
 *              취소 상태가 반영되지 않아서, 스레드 함수가 종료되지 않은 이상 스레드 취소 콜백은
 *              수행되지 않을 것입니다.
 *              사용자는 콜백함수의 등록 여부를 스레드 취소 신호로 판단하고 함수를 정의해야 합니다.
 * 
 *              ```
 *              void userdefinedthreadfunc(xthread * o)
 *              {
 *                  ...
 *                  while(o->cancel == xnil)
 *                  {
 *                      ...
 *                  }
 *                  ...
 *              }
 *              ```
 * 
 * @param       o        | xthread * | in | 스레드 객체 |
 * @param       callback | xthreadfunc | in | 스레드 취소 콜백 |
 * 
 * @see         xthread
 *              xthreadfunc
 *              xthreadposix
 *              xthreadposixfunc
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 */
extern void xthreadcancel(xthread * o, xthreadfunc callback)
{
    xlogfunction_start("%s(%p, %p)", __func__, o, callback);

    xthreadposix_cancel((xthreadposix *) o, (xthreadposixfunc) callback);

    xlogfunction_end("%s(...)", __func__);
}

/**
 * @fn          extern void xthreadrun(xthread * o)
 * @brief       스레드를 실행 시킵니다.
 * @details     OS 에 따라서 적절한 구현 함수가 수행됩니다.
 * 
 * @param       o | xthread * | 스레드 객체 |
 * 
 * @see         xthread
 *              xthreadposix
 *              xthreadposix_run
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 */
extern void xthreadrun(xthread * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xthreadposix_run((xthreadposix *) o);

    xlogfunction_end("%s(...)", __func__);
}

/**
 * @fn          extern xuint64 xthreadid(void)
 * @brief       현재 스레드의 스레드 아이디를 리턴합니다.
 * @details     리눅스 스레드는 64 BIT UNSIGNED INTEGER 형틀 리턴합니다.
 *              다른 OS 들에 대해서도 유사하도록 구현해야 합니다.
 * 
 * @return      | xuint64 | 스레드 아이디 |
 * 
 * @see         xthreadposix_id
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 * 
 */
extern xuint64 xthreadid(void)
{
    xlogfunction_start("%s()", __func__);
    xint64 ret = xthreadposix_id();
    xlogfunction_end("%s() => %ld", __func__, ret);
    return ret;
}

extern xint32 xsynclock(xsync * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xint32 ret = __xsynclock(o);
    xlogfunction_end("%s(...) => %d", __func__, ret);
    return ret;
}

extern xint32 xsyncunlock(xsync * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xint32 ret = __xsyncunlock(o);
    xlogfunction_end("%s(...) => %d", __func__, ret);
    return ret;
}

extern xint32 xsyncwait(xsync * o, xint64 second, xint64 nanosecond)
{
    xlogfunction_start("%s(%p, %ld, %ld)", __func__, o, second, nanosecond);
    xint32 ret = __xsyncwait(o, second, nanosecond);
    xlogfunction_end("%s(...) => %d", __func__, ret);
    return ret;
}

extern xint32 xsyncwakeup(xsync * o, xint32 all)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, all);
    xint32 ret = __xsyncwakeup(o, all);
    xlogfunction_end("%s(...) => %d", __func__, ret);
    return ret;
}
