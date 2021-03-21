#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_SUBSCRIPTION_LIST__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_SUBSCRIPTION_LIST__H__

#include <x/io.h>
#include <x/sync.h>

struct xdescriptoreventgeneratorsubscriptionlist;
typedef struct xdescriptoreventgeneratorsubscriptionlist xdescriptoreventgeneratorsubscriptionlist;

struct xdescriptoreventgeneratorsubscriptionlist
{
    xdescriptoreventsubscription * head;
    xdescriptoreventsubscription * tail;
    xsync *                        sync;
    xuint64                        size;
};

extern xdescriptoreventgeneratorsubscriptionlist * xdescriptoreventgeneratorsubscriptionlist_new(void);
extern xdescriptoreventgeneratorsubscriptionlist * xdescriptoreventgeneratorsubscriptionlist_rem(xdescriptoreventgeneratorsubscriptionlist * list);

extern void xdescriptoreventgeneratorsubscriptionlist_clear(xdescriptoreventgeneratorsubscriptionlist * list);
extern void xdescriptoreventgeneratorsubscriptionlist_push(xdescriptoreventgeneratorsubscriptionlist * list, xdescriptoreventsubscription * subscription);
extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptionlist_pop(xdescriptoreventgeneratorsubscriptionlist * list);
extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptionlist_del(xdescriptoreventsubscription * subscription);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_SUBSCRIPTION_LIST__H__
