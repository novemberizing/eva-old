#ifndef   __NOVEMBERIZING_X__EVENT__SUBSCRIPTION_LIST__H__
#define   __NOVEMBERIZING_X__EVENT__SUBSCRIPTION_LIST__H__

#include <x/event/subscription.h>

struct xeventsubscriptionlist;

typedef struct xeventsubscriptionlist xeventsubscriptionlist;

struct xeventsubscriptionlist
{
    xeventsubscription * head;
    xeventsubscription * tail;
    xsync * sync;
    xuint64 size;
};

#endif // __NOVEMBERIZING_X__EVENT__SUBSCRIPTION_LIST__H__
