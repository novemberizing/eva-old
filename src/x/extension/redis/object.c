#include "object.h"

extern xredisobject * xredisobjectrem(xredisobject * o)
{
    return o ? o->rem(o) : xnil;
}