#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT__H__

#include <x/event.h>
#include <x/descriptor.h>

typedef void (*xdescriptoreventhandler)(xdescriptorevent *);

struct xdescriptorevent
{
    /** INHERITED EVENT */
    xevent *                prev;
    xevent *                next;
    xeventqueue *           queue;
    xdescriptoreventhandler on;
    /** DESCRIPTOR EVENT MEMBER */
    xdescriptor *           descriptor;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT__H__
