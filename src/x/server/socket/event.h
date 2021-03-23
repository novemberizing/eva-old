#ifndef   __NOVEMBERIZING_X__SERVER__SOCKET_EVENT__H__
#define   __NOVEMBERIZING_X__SERVER__SOCKET_EVENT__H__

#include <x/event.h>
#include <x/event/queue.h>
#include <x/server/socket.h>

struct xserversocketevent;

typedef struct xserversocketevent xserversocketevent;

typedef void (*xserversocketeventhandler)(xserversocketevent *);

struct xserversocketevent
{
    xevent *                  prev;
    xevent *                  next;
    xeventqueue *             queue;
    xserversocketeventhandler on;
    xserversocket *           descriptor;
};

#endif // __NOVEMBERIZING_X__SERVER__SOCKET_EVENT__H__

