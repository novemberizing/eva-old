#ifndef   __NOVEMBERIZING_X__SET__H__
#define   __NOVEMBERIZING_X__SET__H__

#include <x/dictionary.h>

struct xset;

typedef struct xset xset;

typedef void (*xsetclearfunc)(xset *, xvalfunc);

extern xset * xsetnew(xdictionarycmp comparator);
extern xset * xsetrem(xset * set, xvalfunc func);
extern xset * xsetclear(xset * set, xvalfunc func);

extern void xsetadd(xset * set, xval key);
extern xint32 xsetdel(xset * set, xval key);
extern xint32 xsethas(xset * set, xval key);

#endif // __NOVEMBERIZING_X__SET__H__
