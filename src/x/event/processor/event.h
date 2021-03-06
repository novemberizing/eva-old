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
