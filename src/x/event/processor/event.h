/**
 * 이벤트프로세서 이벤트 객체는 단순한 커맨드 타입의 객체이다.
 * 지우는 것을 구현한 이벤트이다.
 * 
 * 
 * 그렇다고 타겟을 
 */
#ifndef   __NOVEMBERIZING_X__EVENT__PROCESSOR_EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__PROCESSOR_EVENT__H__

#include <x/event.h>

struct xeventprocessor_event;

typedef struct xeventprocessor_event xeventprocessor_event;

typedef void (*xeventprocessor_event_handler)(xeventprocessor_event *);

struct xeventprocessor_event
{
    /** INHERITED EVENT */
    xevent *                      prev;
    xevent *                      next;
    xeventqueue *                 queue;
    xeventprocessor_event_handler on;
    /** MEMBER */
    xeventprocessor *             processor;
};

extern void xeventprocessor_event_handler_rem(xeventprocessor_event * event);

extern xeventprocessor_event * xeventprocessor_event_new(xeventprocessor_event_handler handler, xeventprocessor * processor);

#endif // __NOVEMBERIZING_X__EVENT__PROCESSOR_EVENT__H__
