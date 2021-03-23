#ifndef   __NOVEMBERIZING_X__CLIENT_POOL_LIST__H__
#define   __NOVEMBERIZING_X__CLIENT_POOL_LIST__H__

#include <x/io.h>

struct xclientpoollist;

typedef struct xclientpoollist xclientpoollist;

struct xclientpoollist
{
    xclientpool * head;
    xclientpool * tail;
    xsync * sync;
    xuint64 size;
};

extern xclientpoollist * xclientpoollist_new(void);
extern xclientpoollist * xclientpoollist_rem(xclientpoollist * list);

extern void xclientpoollist_add(xclientpoollist * list, xclientpool * pool);


#endif // __NOVEMBERIZING_X__CLIENT_POOL_LIST__H__
