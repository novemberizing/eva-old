#ifndef   __NOVEMBERIZING_X__EVA__H__
#define   __NOVEMBERIZING_X__EVA__H__

#include <x/std.h>

struct xeva;

typedef struct xeva xeva;

struct xeva
{
};

extern void xevalog(const char * path, xuint32 types);

extern xint32 xevarun(void);
extern xint32 xevainit(int argc, char ** argv);
extern void xevalogpath_set(const char * dir);

#endif // __NOVEMBERIZING_X__EVA__H__
