#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_DISPATCH__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_DISPATCH__H__

#include <x/io.h>

extern void xdescriptoreventdispatch_exception(xdescriptor * descriptor, void * func, xuint32 number, xuint32 type, const char * message);
extern void xdescriptoreventdispatch_connecting(xdescriptor * descriptor);
extern void xdescriptoreventdispatch_out(xdescriptor * descriptor);
extern void xdescriptoreventdispatch_in(xdescriptor * descriptor);
extern void xdescriptoreventdispatch_void(xdescriptor * descriptor);

#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT_DISPATCH__H__
