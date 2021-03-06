#ifndef   __NOVEMBERIZING_X__EVENT__GENERATOR_SET__H__
#define   __NOVEMBERIZING_X__EVENT__GENERATOR_SET__H__

#include <x/descriptor/event/generator.h>

struct xeventgeneratorset;

typedef struct xeventgeneratorset xeventgeneratorset;

struct xeventgeneratorset
{
    xdescriptoreventgenerator * descriptor;
};

extern void xeventgeneratorset_on(xeventgeneratorset * generators);
extern void xeventgeneratorset_off(xeventgeneratorset * generators);

extern void xeventgeneratorset_once(xeventgeneratorset * generators);

#endif // __NOVEMBERIZING_X__EVENT__GENERATOR_SET__H__
