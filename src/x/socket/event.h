#ifndef   __NOVEMBERIZING_X__SOCKET__EVENT__H__
#define   __NOVEMBERIZING_X__SOCKET__EVENT__H__

#include <x/io.h>
#include <x/event.h>
#include <x/event/queue.h>
#include <x/socket.h>

struct xsocketevent;

typedef struct xsocketevent xsocketevent;

typedef void (*xsocketeventhandler)(xsocketevent *);

struct xsocketevent
{
    xevent *            prev;
    xevent *            next;
    xeventqueue *       queue;
    xsocketeventhandler on;
    xsocket *           descriptor;
};

#endif // __NOVEMBERIZING_X__SOCKET__EVENT__H__
