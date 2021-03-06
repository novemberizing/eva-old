#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__

#include <x/io.h>
#include <x/event.h>
#include <x/event/subscription.h>

#include <x/descriptor/event/generator/subscription/list.h>

struct xdescriptoreventsubscription
{
    xdescriptor *                                                descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__
