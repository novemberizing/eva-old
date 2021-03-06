/**
 * @todo        문서화 및 정리(내부/외부 정리)
 */
#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>
#include <x/sync.h>

struct xevent;                  /**!< expose - all */

struct xeventtarget;            /**!< expose - all */
struct xeventsubscription;      /**!< expose - type */
struct xeventprocessor;         /**!< expose - type */
struct xeventprocessorpool;     /**!< expose - type */
struct xeventengine;            /**!< expose - type */
struct xeventqueue;             /**!< hidden */
struct xdescriptorevent;        /**!< hidden */

typedef struct xevent xevent;

typedef struct xdescriptorevent xdescriptorevent;

typedef struct xeventtarget xeventtarget;
typedef struct xeventsubscription xeventsubscription;

typedef struct xeventprocessor xeventprocessor;
typedef struct xeventprocessorpool xeventprocessorpool;
typedef struct xeventengine xeventengine;
typedef struct xeventqueue xeventqueue;

typedef xeventtarget * (*xeventtargetdestructor)(xeventtarget *);
typedef void (*xeventhandler)(xevent *);

/**
 * @struct      xevent
 * @brief       이벤트 구조체
 * 
 */
struct xevent
{
    xevent *      prev;     /** 이벤트 큐에서 이전 이벤트 - 이것을 은닉시키고 싶다. */
    xevent *      next;     /** 이벤트 큐에서 다음 이벤트 - 이것을 은닉시키고 싶다. */
    xeventqueue * queue;    /** 이벤트 큐 */
    xeventhandler on;       /** 이벤트 핸들러 */
};

#endif // __NOVEMBERIZING_X__EVENT__H__
