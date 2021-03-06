#ifndef   __NOVEMBERIZING_X__THREAD__POSIX__H__
#define   __NOVEMBERIZING_X__THREAD__POSIX__H__

#include <pthread.h>

#include <x/thread.h>

struct xthreadposix;

typedef struct xthreadposix xthreadposix;

typedef void (*xthreadposixfunc)(xthreadposix *);       /** POSIX 스레드 함수 타입 */

/**
 * @struct      xthreadposix
 * @brief       POSIX 스레드 구조체
 * @details     이 구조체는 xthread 와 동일합니다.
 * 
 */
struct xthreadposix
{
    pthread_t *      handle;        /**!< 스레드 핸들 */
    xthreadposixfunc func;          /**!< POSIX 스레드 함수 */
    xuint32          status;        /**!< 스레드 상태 */
    xthreadposixfunc cancel;        /**!< POSIX 스레드 종료 함수 */
};

extern xthreadposix * xthreadposix_rem(xthreadposix * o);

extern void xthreadposix_cancel(xthreadposix * o, xthreadposixfunc cancel);
extern void xthreadposix_run(xthreadposix * o);
extern xuint64 xthreadposix_id(void);

#endif // __NOVEMBERIZING_X__THREAD__POSIX__H__
