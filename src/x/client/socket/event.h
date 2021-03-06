#ifndef   __NOVEMBERIZING_X__CLIENT__SOCKET_EVENT__H__
#define   __NOVEMBERIZING_X__CLIENT__SOCKET_EVENT__H__

#include <x/event.h>
#include <x/event/queue.h>
#include <x/client/socket.h>

struct xclientsocketevent;

typedef struct xclientsocketevent xclientsocketevent;

typedef void (*xclientsocketeventhandler)(xclientsocketevent *);

struct xclientsocketevent
{
    xevent *                  prev;
    xevent *                  next;
    xeventqueue *             queue;
    xclientsocketeventhandler on;
    xclientsocket *           descriptor;
};

#endif // __NOVEMBERIZING_X__CLIENT__SOCKET_EVENT__H__
