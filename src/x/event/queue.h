#ifndef   __NOVEMBERIZING_X__EVENT__QUEUE__H__
#define   __NOVEMBERIZING_X__EVENT__QUEUE__H__

#include <x/event.h>
#include <x/sync.h>

/**
 * @struct      xeventqueue
 * @brief       이벤트 큐 객체
 * 
 * 
 */
struct xeventqueue
{
    xevent * head;      /**!< 이벤트 큐의 헤드 이벤트 */
    xevent * tail;      /**!< 이벤트 큐의 마지막 이벤트 */
    xuint64  size;      /**!< 이벤트 큐의 사이즈 */
    xsync *  sync;      /**!< 이벤트 큐의 동기화 객체 */
};

extern xeventqueue * xeventqueue_new(void);
extern xeventqueue * xeventqueue_rem(xeventqueue * queue);

extern void xeventqueue_push(xeventqueue * queue, xevent * event);
extern xevent * xeventqueue_pop(xeventqueue * queue);

extern void xeventqueue_once(xeventqueue * queue);
extern void xeventqueue_clear(xeventqueue * queue);

#endif // __NOVEMBERIZING_X__EVENT__QUEUE__H__
