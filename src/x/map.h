#ifndef   __NOVEMBERIZING_X__MAP__H__
#define   __NOVEMBERIZING_X__MAP__H__

#include <x/dictionary.h>

struct xmap;
struct xmapnode;

typedef struct xmap xmap;
typedef struct xmapnode xmapnode;

typedef void (*xmapinsertioncallback)(xmap *, xval, xval, xint32, xval *);
typedef void (*xmapdeletioncallback)(xmap *, xval, xint32, xval *);
typedef void (*xmapcheckcallback)(xmap *, xval, xint32);

typedef void (*xmapkeyvaluefunc)(xval *, xval *);
typedef void (*xmapclearfunc)(xmap *, xmapkeyvaluefunc);

extern xmap * xmapnew(xdictionarycmp comparator);
extern xmap * xmaprem(xmap * map, xmapkeyvaluefunc func);
extern xmap * xmapclear(xmap * map, xmapkeyvaluefunc func);

extern xmapnode * xmapadd(xmap * map, xval key, xval value, xmapinsertioncallback callback);
extern xint32 xmapdel(xmap * map, xval key, xmapdeletioncallback callback);
extern xint32 xmaphas(xmap * map, xval key);
extern xmapnode * xmapget(xmap * map, xval key);
extern xval xmapnodekey(xmapnode * node);
extern xval xmapnodevalue(xmapnode * node);

extern xmapnode * xmapbegin(xmap * map);
extern xmapnode * xmapnode_next(xmapnode * node);
extern xuint64 xmapsize(xmap * map);
extern xmapnode * xmapnode_left(xmapnode * node);
extern xmapnode * xmapnode_right(xmapnode * node);

#endif // __NOVEMBERIZING_X__MAP__H__
