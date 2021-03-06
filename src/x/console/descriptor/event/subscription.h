#ifndef   __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT_SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT_SUBSCRIPTION__H__

#include <x/io.h>
#include <x/event.h>
#include <x/event/subscription.h>
#include <x/console/descriptor.h>
#include <x/descriptor/event/generator/subscription/list.h>

struct xconsoledescriptoreventsubscription;

typedef struct xconsoledescriptoreventsubscription xconsoledescriptoreventsubscription;

struct xconsoledescriptoreventsubscription
{
    xconsoledescriptor *                                         descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};

#endif // __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT_SUBSCRIPTION__H__
