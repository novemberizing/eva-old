#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__

#include <x/io.h>
#include <x/event.h>
#include <x/descriptor.h>
#include <x/descriptor/event/subscription.h>
#include <x/descriptor/event/generator/subscription/list.h>

struct xdescriptoreventgenerator
{
    xeventengine *                              engine;
    xsync *                                     sync;
    xdescriptoreventgeneratorsubscriptionlist * alive;
    xdescriptoreventgeneratorsubscriptionlist * queue;
};

extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine);
extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o);

extern void xdescriptoreventgenerator_once(xdescriptoreventgenerator * o);
extern void xdescriptoreventgenerator_queue_once(xdescriptoreventgenerator * o);

extern xint64 xdescriptoreventgenerator_descriptor_register(xdescriptoreventgenerator * o, xdescriptor * descriptor);
extern xint64 xdescriptoreventgenerator_descriptor_update(xdescriptoreventgenerator * o, xdescriptor * descriptor);
extern xint64 xdescriptoreventgenerator_descriptor_unregister(xdescriptoreventgenerator * o, xdescriptor * descriptor);

extern xint64 xdescriptoreventgenerator_descriptor_dispatch(xdescriptoreventgenerator * o, xdescriptor * descriptor);

extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);
extern void xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);

extern void xdescriptoreventgenerator_sync(xdescriptoreventgenerator * o, xint32 on);

extern void xdescriptoreventgenerator_on(xdescriptoreventgenerator * o);
extern void xdescriptoreventgenerator_off(xdescriptoreventgenerator * o);

extern void xdescriptoreventgenerator_alive_clear(xdescriptoreventgenerator * o);
extern void xdescriptoreventgenerator_queue_clear(xdescriptoreventgenerator * o);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__
