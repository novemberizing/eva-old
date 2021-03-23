#include "../../event/engine.h"

#include "dispatch.h"

extern void xdescriptoreventdispatch_exception(xdescriptor * descriptor, void * func, xuint32 number, xuint32 type, const char * message)
{
    descriptor->status |= xdescriptorstatus_exception;
    xexceptionset(xaddressof(descriptor->exception), func, number, type, message);
    xdescriptoron(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), xfail);
}

extern void xdescriptoreventdispatch_connecting(xdescriptor * descriptor)
{
    if(xeventengine_descriptor_dispatch(descriptor, xdescriptoreventtype_connecting) != xsuccess)
    {
        descriptor->process(descriptor, xdescriptoreventtype_connecting);
    }
}

extern void xdescriptoreventdispatch_out(xdescriptor * descriptor)
{
    if(xeventengine_descriptor_dispatch(descriptor, xdescriptoreventtype_out) != xsuccess)
    {
        descriptor->process(descriptor, xdescriptoreventtype_out);
    }
}

extern void xdescriptoreventdispatch_in(xdescriptor * descriptor)
{
    if(xeventengine_descriptor_dispatch(descriptor, xdescriptoreventtype_in) != xsuccess)
    {
        descriptor->process(descriptor, xdescriptoreventtype_in);
    }
}

extern void xdescriptoreventdispatch_void(xdescriptor * descriptor)
{
    if(xeventengine_descriptor_dispatch(descriptor, xdescriptoreventtype_void) != xsuccess)
    {
        descriptor->process(descriptor, xdescriptoreventtype_void);
    }
}