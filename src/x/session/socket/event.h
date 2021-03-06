#ifndef   __NOVEMBERIZING_X__SESSION__SOCKET_EVENT__H__
#define   __NOVEMBERIZING_X__SESSION__SOCKET_EVENT__H__

#include <x/event.h>
#include <x/event/queue.h>
#include <x/session/socket.h>

struct xsessionsocketevent;

typedef struct xsessionsocketevent xsessionsocketevent;

typedef void (*xsessionsocketeventhandler)(xsessionsocketevent *);

struct xsessionsocketevent
{
    xevent *                   prev;
    xevent *                   next;
    xeventqueue *              queue;
    xsessionsocketeventhandler on;
    xsessionsocket *           descriptor;
};


#endif // __NOVEMBERIZING_X__SESSION__SOCKET_EVENT__H__
