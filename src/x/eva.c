#include "eva.h"

static xeva * __singleton = xnil;

extern xint32 xevarun(void)
{
    if(__singleton == xnil)
    {
        __singleton = xevanew();
    }
    return 0;
}
