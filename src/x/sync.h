/**
 * 내부적으로 사용하는 것으로 사용자는 xsync 가 존재하는 것만
 * 확인하면 된다. 이 타입은 스레드 구현 헤더에 정의되어 있다.
 * 
 * 
 * @file        x/sync.h
 * @brief       동기화 객체의 타입, 메서드, 구조체를 정의한 헤더 파일입니다.
 * @details
 * 
 * @version     0.0.1
 * @date        2021. 02. 25.
 */
#ifndef   __NOVEMBERIZING_X__SYNC__H__
#define   __NOVEMBERIZING_X__SYNC__H__

#include <x/thread.h>

typedef xsync * (*xsyncdestructor)(xsync *);

/**
 * @struct      xsync
 * @brief       동기화 객체의 인터페이스 입니다.
 * 
 */
struct xsync
{
    xsyncdestructor rem;                            /**!< 소멸자입니다. 소멸자를 통해서 타입을 유추할 수 있습니다. */
    xint32  (*lock)(xsync *);                       /**!< 스레드 락을 수행합니다. */
    xint32  (*unlock)(xsync *);                     /**!< 스레드 언락을 수행합니다. */
    xint32  (*wait)(xsync *, xint64, xint64);       /**!< 수행을 주어진 시간에 맞추서 잠시 멈춥니다. */
    xint32  (*wakeup)(xsync *, xint32);             /**!< 멈춘 스레드가 존재하면 전체 혹은 하나를 깨우는 신호를 보냅니다. */
};

#define __xsynclock(o)                        (o ? o->lock(o) : xsuccess)
#define __xsyncunlock(o)                      (o ? o->unlock(o) : xsuccess)
#define __xsyncwait(o, second, nanosecond)    (o ? o->wait(o, second, nanosecond) : xsuccess)
#define __xsyncwakeup(o, all)                 (o ? o->wakeup(o, all) : xsuccess)



#endif // __NOVEMBERIZING_X__SYNC__H__
