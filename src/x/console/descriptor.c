#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../thread.h"
#include "descriptor.h"

static xint32 xconsoledescriptorstatuscheck_void(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_open(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_in(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_out(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_close(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_exception(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_rem(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_register(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_flush(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_readoff(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_writeoff(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_opening(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_create(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_bind(xconsoledescriptor * descriptor);
static xint32 xconsoledescriptorstatuscheck_alloff(xconsoledescriptor * descriptor);

extern xconsoledescriptor * xconsoledescriptordestruct(xconsoledescriptor * descriptor)
{
    if(descriptor)
    {
        descriptor->subscription = xdescriptoreventsubscription_rem(descriptor->subscription);
        descriptor->stream       = xstreamrem(descriptor->stream);
        descriptor->sync         = xsyncrem(descriptor->sync);
    }
    return xnil;
}

extern xint32 xconsoledescriptorstatuscheck(xconsoledescriptor * descriptor, xuint32 status)
{
    xint32 ret = xfalse;
    switch(status)
    {
        case xdescriptorstatus_void:        xconsoledescriptorstatuscheck_void(descriptor);         break;
        case xdescriptorstatus_open:        xconsoledescriptorstatuscheck_open(descriptor);         break;
        case xdescriptorstatus_in:          xconsoledescriptorstatuscheck_in(descriptor);           break;
        case xdescriptorstatus_out:         xconsoledescriptorstatuscheck_out(descriptor);          break;
        case xdescriptorstatus_close:       xconsoledescriptorstatuscheck_close(descriptor);        break;
        case xdescriptorstatus_exception:   xconsoledescriptorstatuscheck_exception(descriptor);    break;
        case xdescriptorstatus_rem:         xconsoledescriptorstatuscheck_rem(descriptor);          break;
        case xdescriptorstatus_register:    xconsoledescriptorstatuscheck_register(descriptor);     break;
        case xdescriptorstatus_flush:       xconsoledescriptorstatuscheck_flush(descriptor);        break;
        case xdescriptorstatus_readoff:     xconsoledescriptorstatuscheck_readoff(descriptor);      break;
        case xdescriptorstatus_writeoff:    xconsoledescriptorstatuscheck_writeoff(descriptor);     break;
        case xdescriptorstatus_opening:     xconsoledescriptorstatuscheck_opening(descriptor);      break;
        case xdescriptorstatus_create:      xconsoledescriptorstatuscheck_create(descriptor);       break;
        case xdescriptorstatus_bind:        xconsoledescriptorstatuscheck_bind(descriptor);         break;
        case xdescriptorstatus_alloff:      xconsoledescriptorstatuscheck_alloff(descriptor);       break;
        default: xassertion(xtrue, "");     ret = xfalse;                                           break;
    }
    return ret;
}

static xint32 xconsoledescriptorstatuscheck_void(xconsoledescriptor * descriptor)
{
    return descriptor->status == xdescriptorstatus_void;
}

static xint32 xconsoledescriptorstatuscheck_open(xconsoledescriptor * descriptor)
{
    if(xconsoledescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_open;
}

static xint32 xconsoledescriptorstatuscheck_in(xconsoledescriptor * descriptor)
{
    if(xconsoledescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_in;
}

static xint32 xconsoledescriptorstatuscheck_out(xconsoledescriptor * descriptor)
{
    if(xconsoledescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_out;
}
static xint32 xconsoledescriptorstatuscheck_close(xconsoledescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_rem | xdescriptorstatus_close | xdescriptorstatus_exception))
    {
        return xtrue;
    }
    return xfalse;
}
static xint32 xconsoledescriptorstatuscheck_exception(xconsoledescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_exception;
}
static xint32 xconsoledescriptorstatuscheck_rem(xconsoledescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_rem;
}

static xint32 xconsoledescriptorstatuscheck_register(xconsoledescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_register;
}

static xint32 xconsoledescriptorstatuscheck_flush(xconsoledescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_flush;
}

static xint32 xconsoledescriptorstatuscheck_readoff(xconsoledescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_readoff;
}
static xint32 xconsoledescriptorstatuscheck_writeoff(xconsoledescriptor * descriptor)
{
    return descriptor->status & xdescriptorstatus_writeoff;
}

static xint32 xconsoledescriptorstatuscheck_opening(xconsoledescriptor * descriptor)
{
    if(xconsoledescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_opening;
}

static xint32 xconsoledescriptorstatuscheck_create(xconsoledescriptor * descriptor)
{
    if(xconsoledescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_create;
}

static xint32 xconsoledescriptorstatuscheck_bind(xconsoledescriptor * descriptor)
{
    if(xconsoledescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_bind;
}

static xint32 xconsoledescriptorstatuscheck_alloff(xconsoledescriptor * descriptor)
{
    if(xconsoledescriptorstatuscheck_close(descriptor))
    {
        return xfalse;
    }
    return descriptor->status & xdescriptorstatus_alloff;
}
