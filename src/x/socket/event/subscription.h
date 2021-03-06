#ifndef   __NOVEMBERIZING_X__SOCKTE__EVENT_SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__SOCKTE__EVENT_SUBSCRIPTION__H__

#include <x/event/subscription.h>
#include <x/event/engine.h>
#include <x/descriptor/event/subscription.h>
#include <x/descriptor/event/generator.h>
#include <x/descriptor/event/generator/subscription/list.h>

struct xsocketeventsubscription;

typedef struct xsocketeventsubscription xsocketeventsubscription;

struct xsocketeventsubscription
{
    xsocket *                                                    descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};

#endif // __NOVEMBERIZING_X__SOCKTE__EVENT_SUBSCRIPTION__H__
