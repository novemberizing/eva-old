#ifndef   __NOVEMBERIZING_X__STACK__H__
#define   __NOVEMBERIZING_X__STACK__H__

#include <x/list.h>

typedef struct xlist xstack;

extern xstack * xstacknew(void);
extern xstack * xstackrem(xstack * stack, xvalfunc func);
extern void xstackpush(xstack * stack, xval value);
extern xval xstackpop(xstack * stack);
extern xuint64 xstacksize(xstack * stack);
extern void xstackclear(xstack * stack, xvalfunc func);

#endif // __NOVEMBERIZING_X__STACK__H__
