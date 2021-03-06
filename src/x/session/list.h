#ifndef   __NOVEMBERIZING_X__SESSION__LIST__H__
#define   __NOVEMBERIZING_X__SESSION__LIST__H__

#include <x/io.h>

struct xsessionlist;

typedef struct xsessionlist xsessionlist;

struct xsessionlist
{
    xsession * head;
    xsession * tail;
    xuint64 size;
    xsync * sync;
};

#endif // __NOVEMBERIZING_X__SESSION__LIST__H__
