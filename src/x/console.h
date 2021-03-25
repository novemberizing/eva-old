#ifndef   __NOVEMBERIZING_X__CONSOLE__H__
#define   __NOVEMBERIZING_X__CONSOLE__H__

#include <x/std.h>
#include <x/stream.h>
#include <x/descriptor.h>

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

// struct xconsole
// {
//     xconsoledescriptor * in;
//     xconsoledescriptor * out;
//     xconsolesubscriber   on;
// };


// struct xconsole;
// struct xconsoledescriptor;
// struct xconsoledescriptorevent;

// typedef struct xconsole xconsole;
// typedef struct xconsoledescriptor xconsoledescriptor;
// typedef struct xconsoledescriptorevent xconsoledescriptorevent;

// typedef xint64 (*xconsolesubscriber)(xconsole *, xconsoledescriptor *, xuint32, xdescriptorparam, xint64);

// struct xconsole
// {
//     xconsoledescriptor * in;
//     xconsoledescriptor * out;
//     xconsolesubscriber   on;
// };

// extern xconsole * xconsoleinit(xconsolesubscriber on);
// extern void xconsoleterm(void);


// // 아래의 메서드들 중에 CONSOLE IN/OUT, FLUSH 를 제외하고 모두 숨기자.

// extern xconsole * xconsoleget(void);


// extern xdescriptor * xconsoledescriptorin_get(void);
// extern xdescriptor * xconsoledescriptorout_get(void);
// extern void xconsolesubscriber_set(xconsolesubscriber subscriber);

// extern xint64 xconsolesubscriber_default(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam, xint64 value);

// extern xint64 xconsoleout_string(const char * s);
// extern xint64 xconsolein_string(char * buffer, xuint64 size);

// extern void xconsolein_flush(void);
// extern void xconsoleout_flush(void);

// extern xstream * xconsoledescriptorstream_get(xconsoledescriptor * descriptor);

#endif // __NOVEMBERIZING_X__CONSOLE__H__
