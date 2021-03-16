#ifndef   __NOVEMBERIZING_X__MAP__H__
#define   __NOVEMBERIZING_X__MAP__H__

#include <x/dictionary.h>

struct xmap;

typedef struct xdictionary xmap;

typedef void (*xmapinsertioncallback)(xmap *, xval, xval, xint32, xval *);
typedef void (*xmapdeletioncallback)(xmap *, xval, xint32, xval *);
typedef void (*xmapcheckcallback)(xmap *, xval, xint32);

extern xmap * xmapnew(xdictionarycmp comparator);
extern xmap * xmaprem(xmap * map);

extern void xmapadd(xmap * map, xval key, xval value, xmapinsertioncallback callback);
extern xint32 xmapdel(xmap * map, xval key, xmapdeletioncallback callback);
extern xint32 xmaphas(xmap * map, xval key);

#endif // __NOVEMBERIZING_X__MAP__H__
