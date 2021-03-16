#ifndef   __NOVEMBERIZING_X__LIST__H__
#define   __NOVEMBERIZING_X__LIST__H__

#include <x/std.h>
#include <x/sync.h>

struct xlist;
struct xlistnode;

typedef struct xlist xlist;
typedef struct xlistnode xlistnode;

typedef xlist * (*xlistdestructor)(xlist *);

struct xlist
{
    xlistdestructor rem;
    xlistnode *     head;
    xlistnode *     tail;
    xuint64         size;
    xsync *         sync;
};

// 리스트 노드는 은닉 시키자.
struct xlistnode
{
    xlistnode * prev;
    xlistnode * next;
    xlist *     list;
    xval        value;
};

extern xlist * xlistnew(void);
extern xlist * xlistrem(xlist * list);

extern void xlistdel(xlist * list, xlistnode * node);

extern void xlistpushfront(xlist * list, xval value);
extern void xlistpushback(xlist * list, xval value);

extern xlistnode * xlistpopfront(xlist * list);
extern xlistnode * xlistpopback(xlist * list);

extern void xlistinsertfront(xlist * list, xlistnode * node, xval value);
extern void xlistinsertback(xlist * list, xlistnode * node, xval value);

#endif // __NOVEMBERIZING_X__LIST__H__
