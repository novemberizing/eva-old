#ifndef   __NOVEMBERIZING_X__CLIENT_POOL__H__
#define   __NOVEMBERIZING_X__CLIENT_POOL__H__

#include <x/client.h>

struct xclientpool;

typedef struct xclientpool xclientpool;

typedef xint64 (*xclientpoolobserver)(xclientpool *, xclient *, xuint64, xdescriptorparam, xint64);

struct xclientpool
{
    xclientpoollist *   cntr;
    xclientpool *       prev;
    xclientpool *       next;
    xclientpoolobserver on;
    xsync *             sync;
    xuint64             size;

    xclient *           head;
    xclient *           tail;
};

extern xclientpool * xclientpoolnew(xclientpoolobserver on, xuint64 size);
extern xclientpool * xclientpoolrem(xclientpool * pool);

extern void xclientpooldel(xclient * client);
extern void xclientpooladd(xclientpool * pool, xclient * client);
extern void xclientpoolpush(xclientpool * pool, xclient * client);
extern xclient * xclientpoolpop(xclientpool * pool);

extern xclient * xclientpoolnext(xclient * client);

#endif // __NOVEMBERIZING_X__CLIENT_POOL__H__
