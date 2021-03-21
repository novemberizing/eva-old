#include "status.h"

extern xint32 xdescriptorstatuscheck(xdescriptor * descriptor, xuint32 status)
{
    switch(status)
    {
        case xdescriptorstatus_void:        return xdescriptorstatuscheck_void(descriptor);
        case xdescriptorstatus_open:        return xdescriptorstatuscheck_open(descriptor);
        case xdescriptorstatus_in:          return xdescriptorstatuscheck_in(descriptor);
        case xdescriptorstatus_out:         return xdescriptorstatuscheck_out(descriptor);
        case xdescriptorstatus_close:       return xdescriptorstatuscheck_close(descriptor);
        case xdescriptorstatus_exception:   return xdescriptorstatuscheck_exception(descriptor);
        case xdescriptorstatus_rem:         return xdescriptorstatuscheck_rem(descriptor);
        case xdescriptorstatus_register:    return xdescriptorstatuscheck_register(descriptor);
        case xdescriptorstatus_flush:       return xdescriptorstatuscheck_flush(descriptor);
        case xdescriptorstatus_readoff:     return xdescriptorstatuscheck_readoff(descriptor);
        case xdescriptorstatus_writeoff:    return xdescriptorstatuscheck_writeoff(descriptor);
        case xdescriptorstatus_connecting:  return xdescriptorstatuscheck_connecting(descriptor);
        case xdescriptorstatus_create:      return xdescriptorstatuscheck_create(descriptor);
        case xdescriptorstatus_bind:        return xdescriptorstatuscheck_bind(descriptor);
        case xdescriptorstatus_end:         return xdescriptorstatuscheck_end(descriptor);
        case xdescriptorstatus_listen:      return xdescriptorstatuscheck_listen(descriptor);
        case xdescriptorstatus_connect:     return xdescriptorstatuscheck_connect(descriptor);
        case xdescriptorstatus_alloff:      return xdescriptorstatuscheck_alloff(descriptor);
        default: xassertion(xtrue, "");     return xfalse;
    }
}

extern xint32 xdescriptorstatuscheck_void(xdescriptor * descriptor)
{
    return descriptor->status == xdescriptorstatus_void;
}

extern xint32 xdescriptorstatuscheck_open(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    if(descriptor->handle.f < 0)
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_open;
}

extern xint32 xdescriptorstatuscheck_in(xdescriptor * descriptor)
{
    if(descriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    if(descriptor->handle.f < 0)
    {
        return xfalse;
    }
    if(descriptor->status & (xdescriptorstatus_open | xdescriptorstatus_connecting))
    {
        return (descriptor->status & xdescriptorstatus_readoff) == xdescriptorstatus_void;
    }
}

extern xint32 xdescriptorstatuscheck_out(xdescriptor * descriptor)
{
    if(descriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    if(descriptor->handle.f < 0)
    {
        return xfalse;
    }
    if(descriptor->status & (xdescriptorstatus_open | xdescriptorstatus_connecting))
    {
        return (descriptor->status & xdescriptorstatus_writeoff) == xdescriptorstatus_void;
    }
}

extern xint32 xdescriptorstatuscheck_close(xdescriptor * descriptor)
{
    return descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_rem | xdescriptorstatus_exception);
}

extern xint32 xdescriptorstatuscheck_exception(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_exception;
}

extern xint32 xdescriptorstatuscheck_rem(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_rem;
}

extern xint32 xdescriptorstatuscheck_register(xdescriptor * descriptor)
{
    return descriptor->handle.f >= 0 && descriptor->status & xdescriptorstatus_register;
}
extern xint32 xdescriptorstatuscheck_flush(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_flush;
}

extern xint32 xdescriptorstatuscheck_readoff(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_readoff;
}

extern xint32 xdescriptorstatuscheck_writeoff(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_writeoff;
}

extern xint32 xdescriptorstatuscheck_connecting(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_connecting;
}

extern xint32 xdescriptorstatuscheck_create(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_create;
}

extern xint32 xdescriptorstatuscheck_bind(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_bind;
}

extern xint32 xdescriptorstatuscheck_end(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_end;
}

extern xint32 xdescriptorstatuscheck_listen(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_listen;
}

extern xint32 xdescriptorstatuscheck_connect(xdescriptor * descriptor)
{
    if(xdescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_connect;
}

extern xint32 xdescriptorstatuscheck_alloff(xdescriptor * descriptor)
{
    return (descriptor->status & xdescriptorstatus_alloff) == xdescriptorstatus_alloff;
}
