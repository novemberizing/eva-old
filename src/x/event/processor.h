#ifndef   __NOVEMBERIZING_X__EVENT__PROCESSOR__H__
#define   __NOVEMBERIZING_X__EVENT__PROCESSOR__H__

#include <x/event.h>
#include <x/thread.h>

typedef void (*xeventprocessorfunc)(xeventprocessor *);

struct xeventprocessor
{
    /** INHERITED THREAD */
    void *                  handle;
    xeventprocessorfunc     func;
    xuint32                 status;
    xeventprocessorfunc     cancel;
    /** EVENT PROCESSOR MEMBER */
    xeventprocessor *       prev;
    xeventprocessor *       next;
    xeventprocessorpool *   pool;
};

extern xeventprocessor * xeventprocessor_new(xeventprocessorpool * pool);
extern xeventprocessor * xeventprocessor_rem(xeventprocessor * processor);

extern void xeventprocessor_cancel(xeventprocessor * processor);

extern void xeventprocessor_wakeup(xeventengine * engine, xint32 all);


#endif // __NOVEMBERIZING_X__EVENT__PROCESSOR__H__
