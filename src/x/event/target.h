#ifndef   __NOVEMBERIZING_X__EVENT__TARGET__H__
#define   __NOVEMBERIZING_X__EVENT__TARGET__H__

#include <x/event.h>

/**
 * @struct      xeventtarget
 * @brief       이벤트 타겟 객체
 * @details     
 */
struct xeventtarget
{
    xeventtargetdestructor rem;             /**!< 이벤트 타겟 소멸자 */
    xeventsubscription *   subscription;    /**!< 이벤트 타겟의 서브스크립션: 이 값이 널이 아니면 이벤트가 이벤트 엔진에 등록되어 있음을 의미합니다. */
    xsync *                sync;            /**!< 이벤트 타겟의 동기화 객체 */
    xuint32                mask;            /**!< 이벤트 타겟의 마스크 */
    xuint32                status;          /**!< 이벤트 타겟의 상태 */
};

#endif // __NOVEMBERIZING_X__EVENT__TARGET__H__
