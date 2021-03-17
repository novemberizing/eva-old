#ifndef   __NOVEMBERIZING_X__QUEUE__H__
#define   __NOVEMBERIZING_X__QUEUE__H__

#include <x/list.h>

typedef struct xlist xqueue;

extern xqueue * xqueuenew(void);
extern xqueue * xqueuerem(xqueue * queue, xvalfunc func);
extern void xqueuepush(xqueue * queue, xval value);
extern xval xqueuepop(xqueue * queue);
extern xuint64 xqueuesize(xqueue * queue);
extern void xqueueclear(xqueue * queue, xvalfunc func);

#endif // __NOVEMBERIZING_X__QUEUE__H__
