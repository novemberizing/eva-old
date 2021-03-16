#ifndef   __NOVEMBERIZING_X__EVA__H__
#define   __NOVEMBERIZING_X__EVA__H__

#include <x/std.h>
#include <x/console.h>

struct xeva;

typedef struct xeva xeva;

extern void xevaconfiglogpath_set(const char * path);
extern void xevaconfiglogtypes_set(xuint32 types);
extern void xevaconfiglogtypes_add(xuint32 type);
extern void xevaconfiglogtypes_del(xuint32 type);

extern void xevaconfigloginit(char * path, xuint32 types);

extern xint32 xevarun(int argc, char ** argv);

extern void xevaquit(void);

// 아래의 함수는 설정하지 말자. (노출 시키지 말자.)
extern xint64 xevacli(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 value);

#endif // __NOVEMBERIZING_X__EVA__H__
