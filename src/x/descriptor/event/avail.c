#include "avail.h"

extern xint32 xdescriptoreventavail_open(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_rem | xdescriptorstatus_exception))
    {
        return xfalse;
    }

    return descriptor->handle.f >= 0 && (descriptor->status & xdescriptorstatus_open);
}

extern xint32 xdescriptoreventavail_rem(xdescriptor * descriptor)
{
    return descriptor->status == xdescriptorstatus_rem;
}

extern xint32 xdescriptoreventavail_in(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_rem | xdescriptorstatus_exception))
    {
        return xfalse;
    }

    return (descriptor->handle.f >= 0 && (descriptor->status & xdescriptorstatus_readoff) == xdescriptorstatus_void);
}

extern xint32 xdescriptoreventavail_out(xdescriptor * descriptor)
{
    if(descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_rem | xdescriptorstatus_exception))
    {
        return xfalse;
    }

    return (descriptor->handle.f >= 0 && (descriptor->status & xdescriptorstatus_writeoff) == xdescriptorstatus_void);
}
