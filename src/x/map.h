#ifndef   __NOVEMBERIZING_X__MAP__H__
#define   __NOVEMBERIZING_X__MAP__H__

#include <x/std.h>

struct xmap;
struct xmapnode;

typedef struct xmap xmap;
typedef struct xmapnode xmapnode;
typedef xint32 (*xmapnodecmp)(xval, xval);

struct xmap
{
    xmapnode * root;
    xuint64 size;
    xmapnodecmp compare;
};

struct xmapnode
{
    xuint32 color;
    xmapnode * parent;
    xmapnode * left;
    xmapnode * right;
    xval key;
};

extern xmap * xmapnew(xmapnodecmp comparator);

extern xmap * xmapadd(xmap * map, xval key);
extern xmap * xmapdel(xmap * map, xval key);
extern xmap * xmapget(xmap * map, xval key);

#endif // __NOVEMBERIZING_X__MAP__H__
