#ifndef   __NOVEMBERIZING_X__CONSOLE__H__
#define   __NOVEMBERIZING_X__CONSOLE__H__

#include <x/std.h>
#include <x/descriptor.h>

struct xconsole;
struct xconsoledescriptor;
struct xconsoledescriptorevent;

typedef struct xconsole xconsole;
typedef struct xconsoledescriptor xconsoledescriptor;
typedef struct xconsoledescriptorevent xconsoledescriptorevent;

typedef xint64 (*xconsolesubscriber)(xconsole *, xuint64, void *, xint64);

struct xconsole
{
    xconsoledescriptor * in;
    xconsoledescriptor * out;
    xconsolesubscriber   on;
};

extern void xconsoledescriptor_term(void);
extern xdescriptor * xconsoledescriptorin_get(void);
extern xdescriptor * xconsoledescriptorout_get(void);
extern void xconsolesubscriber_set(xconsolesubscriber subscriber);

extern xint64 xconsolesubscriber_default(xconsole * console, xuint64 event, void * parameter, xint64 value);

extern xint64 xconsoleout_string(const char * s);
extern xint64 xconsolein_string(char * buffer, xuint64 size);

#endif // __NOVEMBERIZING_X__CONSOLE__H__
