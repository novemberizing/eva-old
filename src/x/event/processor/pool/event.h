#ifndef   __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL_EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL_EVENT__H__

#include <x/event.h>

struct xeventprocessorpool_event;

typedef struct xeventprocessorpool_event xeventprocessorpool_event;

typedef void (*xeventprocessorpool_event_handler)(xeventprocessorpool_event *);

struct xeventprocessorpool_event
{
    /** INHERITED EVENT */
    xevent *                          prev;
    xevent *                          next;
    xeventqueue *                     queue;
    xeventprocessorpool_event_handler on;
    /** MEMBER */
    xeventprocessorpool *             pool;
    xuint64                           n;
};

extern void xeventprocessorpool_event_handler_add(xeventprocessorpool_event * event);
extern void xeventprocessorpool_event_handler_del(xeventprocessorpool_event * event);

extern xeventprocessorpool_event * xeventprocessorpool_event_new(xeventprocessorpool_event_handler handler, xeventprocessorpool * pool, xuint64 n);


#endif // __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL_EVENT__H__
