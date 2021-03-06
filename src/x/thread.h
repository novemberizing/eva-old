/**
 * @file        x/thread.h
 * @brief       스레드 표준 라이브러리 헤더 파일입니다.
 * @details
 * 
 * @version     0.0.1
 * @date        2021. 02. 25.
 */
#ifndef   __NOVEMBERIZING_X__THREAD__H__
#define   __NOVEMBERIZING_X__THREAD__H__

#include <x/std.h>

#define xsynctype_mutex         (0)                 /**!< 뮤텍스 동기화 객체 타입 */
#define xsynctype_spinlock      (1)                 /**!< 스핀락 동기화 객체 타입  */

#define xsynctype_default       xsynctype_mutex     /**!< 기본 동기화 객체 타입: 뮤텍스 동기화 객체 타입 */

#define xthreadstatus_void      (0x00000000u)   /**!< 스레드 상태: 동작중이지 않음 */
#define xthreadstatus_on        (0x00000001u)   /**!< 스레드 상태: 동작중 */

struct xsync;
struct xthread;

typedef struct xsync xsync;
typedef struct xthread xthread;


typedef void (*xthreadfunc)(xthread *);         /**!< 기본 스레드 함수 타입 */

extern xthread * xthreadnew(xthreadfunc func, xuint64 size);
extern xthread * xthreadrem(xthread * o);

extern void xthreadcancel(xthread * o, xthreadfunc callback);
extern void xthreadrun(xthread * o);

extern xuint64 xthreadid(void);
extern xint32 xthreadcheck_rem(xthread * o);

extern xsync * xsyncnew(xuint32 type);
extern xsync * xsyncrem(xsync * o);
extern xsync * xsynccondinit(xsync * o);
extern xsync * xsynccondterm(xsync * o);

extern xint32 xsynclock(xsync * o);
extern xint32 xsyncunlock(xsync * o);
extern xint32 xsyncwait(xsync * o, xint64 second, xint64 nanosecond);
extern xint32 xsyncwakeup(xsync * o, xint32 all);

/**
 * @struct      xthread
 * @brief       스레드 구조체
 * @details     사용자가 스레드를 커스터마이즈 하려면
 *              아래의 구조체를 상속하여 사용하면 됩니다.
 * 
 *              ```
 *              struct xcustomizethread
 *              {
 *                  xhandle     handle;
 *                  void (*func)(struct xcustomizethread *);
 *                  xuint32     status;
 *                  void (*cancel)(struct xcustomizethread *);
 *                  
 *                  ...
 *              };
 *              struct xcustomizethread * o = xthreadnew((xthreadfunc) userthreadfunc, sizeof(struct xcustomizethread));
 *              o->userparam = ...;
 *              xthreadrun((xthread) o);
 *              ...
 *              ```
 */
struct xthread
{
    xhandle     handle; /**!< 스레드 핸들 */
    xthreadfunc func;   /**!< 사용자 스레드 함수 */
    xuint32     status; /**!< 스레드 상태 */
    xthreadfunc cancel; /**!< 스레드 취소 함수로 스레드 취소 상태를 나타냅니다. 즉, 이 변수가 널이 아니면 스레드는 종료되어져야 합니다. 사용자는 이 변수의 상태를 보고 스레드 함수를 종료시키도록 해야 합니다. */
};

#endif // __NOVEMBERIZING_X__THREAD__H__
