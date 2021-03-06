#ifndef   __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__

#include <x/event.h>

struct xeventsubscription
{
    xeventtarget *                        target;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;     } enginenode;
};

extern xeventsubscription * xeventsubscription_new(xeventengine * engine, xeventtarget * target, xuint64 size);
extern xeventsubscription * xeventsubscription_rem(xeventsubscription * subscription);

extern xeventsubscription * xeventsubscription_del(xeventsubscription * subscription);

#endif // __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__
