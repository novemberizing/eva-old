#ifndef   __NOVEMBERIZING_X__EVA__CLI__H__
#define   __NOVEMBERIZING_X__EVA__CLI__H__

#include <x/console.h>

extern void xevacli_init(xeventengine * engine);

extern xint64 xevacli(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result);

#endif // __NOVEMBERIZING_X__EVA__CLI__H__
