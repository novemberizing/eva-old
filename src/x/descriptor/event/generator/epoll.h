#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_EPOLL__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_EPOLL__H__

#include <sys/types.h>
#include <sys/epoll.h>

#include <x/descriptor/event/generator.h>
#include <x/descriptor/event/generator/subscription/list.h>

struct xdescriptoreventgenerator_epoll;

typedef struct xdescriptoreventgenerator_epoll xdescriptoreventgenerator_epoll;

struct xdescriptoreventgenerator_epoll
{
    /** INHERITED DESCRIPTOR EVENT GENERATOR */
    xeventengine *                              engine;
    xsync *                                     sync;
    xdescriptoreventgeneratorsubscriptionlist * alive;
    xdescriptoreventgeneratorsubscriptionlist * queue;
    xclientpoollist *                           clientpoollist;
    /** MEMBER */
    xint32                                      f;
    xint32                                      max;
    xint32                                      millisecond;
    struct epoll_event *                        events;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_EPOLL__H__
