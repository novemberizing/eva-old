#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"

#include "status.h"

#define xdescriptorstatus_void          0x00000000u

#define xdescriptorstatus_open          0x00000001u
#define xdescriptorstatus_in            0x00000002u
#define xdescriptorstatus_out           0x00000004u
#define xdescriptorstatus_close         0x00000008u
#define xdescriptorstatus_exception     0x00000010u
#define xdescriptorstatus_rem           0x00000020u
#define xdescriptorstatus_register      0x00000040u
#define xdescriptorstatus_flush         0x00000080u
#define xdescriptorstatus_readoff       0x00000100u
#define xdescriptorstatus_writeoff      0x00000200u
#define xdescriptorstatus_connecting    0x00000400u
#define xdescriptorstatus_create        0x00000800u
#define xdescriptorstatus_bind          0x00001000u
#define xdescriptorstatus_readend       0x00002000u
#define xdescriptorstatus_writeend      0x00004000u
#define xdescriptorstatus_listen        0x00008000u
#define xdescriptorstatus_connect       0x00010000u

#define xdescriptorstatus_alloff        (xdescriptorstatus_readoff | xdescriptorstatus_writeoff)

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
        case xdescriptorstatus_readend:     return xdescriptorstatuscheck_readend(descriptor);
        case xdescriptorstatus_writeend:    return xdescriptorstatuscheck_writeend(descriptor);
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
    if(descriptor->handle.f >= 0)
    {
        if(descriptor->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception))
        {
            return xfalse;
        }
        return descriptor->status & xdescriptorstatus_open;
    }

    return xfalse;
}

extern xint32 xdescriptorstatuscheck_in(xdescriptor * descriptor)
{
    if(descriptor->handle.f >= 0)
    {
        if(descriptor->status & xdescriptorstatus_open)
        {
            return (descriptor->status & xdescriptorstatus_readoff) == xdescriptorstatus_void;
        }
    }

    return xfalse;
}

extern xint32 xdescriptorstatuscheck_out(xdescriptor * descriptor)
{
    if(descriptor->handle.f >= 0)
    {
        if(descriptor->status & xdescriptorstatus_open)
        {
            return (descriptor->status & xdescriptorstatus_writeoff) == xdescriptorstatus_void;
        }
    }

    return xfalse;
}

extern xint32 xdescriptorstatuscheck_close(xdescriptor * descriptor)
{
    return descriptor->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception);
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
    return descriptor->handle.f >= 0 && (descriptor->status & xdescriptorstatus_register);
}

extern xint32 xdescriptorstatuscheck_flush(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_flush;
}

extern xint32 xdescriptorstatuscheck_readoff(xdescriptor * descriptor)
{
    return descriptor->handle.f < 0 || (descriptor->status & xdescriptorstatus_readoff);
}

extern xint32 xdescriptorstatuscheck_writeoff(xdescriptor * descriptor)
{
    return descriptor->handle.f < 0 || (descriptor->status & xdescriptorstatus_writeoff);
}

extern xint32 xdescriptorstatuscheck_connecting(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_connecting;
}

extern xint32 xdescriptorstatuscheck_create(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_create;
}
extern xint32 xdescriptorstatuscheck_bind(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_bind;
}

extern xint32 xdescriptorstatuscheck_readend(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_readend;
}

extern xint32 xdescriptorstatuscheck_writeend(xdescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_writeend;
}
extern xint32 xdescriptorstatuscheck_listen(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_listen;
}

extern xint32 xdescriptorstatuscheck_connect(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_connect;
}

extern xint32 xdescriptorstatuscheck_alloff(xdescriptor * descriptor)
{
    return descriptor->handle.f < 0 || (descriptor->status & xdescriptorstatus_alloff) == xdescriptorstatus_alloff;
}
