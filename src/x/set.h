#ifndef   __NOVEMBERIZING_X__SET__H__
#define   __NOVEMBERIZING_X__SET__H__

#include <x/dictionary.h>

struct xset;

typedef struct xdictionary xset;

extern xset * xsetnew(xdictionarycmp comparator);

extern void xsetadd(xset * set, xval key);
extern xint32 xsetdel(xset * set, xval key);
extern xint32 xsethas(xset * set, xval key);

#endif // __NOVEMBERIZING_X__SET__H__
