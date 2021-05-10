#ifndef   __NOVEMBERIZING_X__CONSOLE__H__
#define   __NOVEMBERIZING_X__CONSOLE__H__

#include <x/std.h>
#include <x/stream.h>
#include <x/descriptor.h>

#define xconsolestatus_void     0x00000000u
#define xconsolestatus_wait     0x00000001u
#define xconsolestatus_flush    0x00000002u

struct xconsole;
struct xconsoledescriptor;
struct xconsoledescriptorevent;

typedef struct xconsole xconsole;
typedef struct xconsoledescriptor xconsoledescriptor;
typedef struct xconsoledescriptorevent xconsoledescriptorevent;

typedef xint64 (*xconsoleobserver)(xconsole *, xconsoledescriptor *, xuint32, xdescriptorparam, xint64);

extern xconsoledescriptor * xconsoledescriptorin_get(void);
extern xconsoledescriptor * xconsoledescriptorout_get(void);

extern void xconsoleinit(xconsoleobserver on);
extern void xconsoleterm(void);

extern void xconsoleout(const char * format, ...);
extern void xconsoleoutv(const char * format, va_list ap);

extern void xconsolestatus_set(xuint32 value);
extern void xconsolestatus_add(xuint32 status);
extern void xconsolestatus_del(xuint32 status);
extern xuint32 xconsolestatus_get(void);

extern void xconsoleflush(void);

#endif // __NOVEMBERIZING_X__CONSOLE__H__
