#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../../thread.h"

#include "in.h"
#include "../descriptor.h"

static xint64 xconsoledescriptoreventprocess_void(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_open(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_in(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_out(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_close(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_exception(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_rem(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_register(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_flush(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_readoff(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_writeoff(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_opening(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_create(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_bind(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_alloff(xconsoledescriptor * descriptor, xdescriptorparam param);

static xint64 xconsoledescriptorin_process(xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param);
static xint64 xconsoledescriptorin_observe(xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result);
static void xconsoledescriptorin_eventon(xconsoledescriptorevent * event);

static xconsoledescriptor singleton = {
    xconsoledescriptordestruct,
    xnil,
    xnil,
    xdescriptormask_void,
    xdescriptorstatus_void,
    xdescriptorhandle_invalid,
    xconsoledescriptorin_process,
    xconsoledescriptorstatuscheck,
    xconsoledescriptorin_observe,
    xconsoledescriptorevent_void,
    xexception_void,
    xnil,
    xnil
};

extern xconsoledescriptor * xconsoledescriptorin_init(xconsole * console)
{
    if(singleton.console == xnil)
    {
        console->in = xaddressof(singleton);

        singleton.status   = (xdescriptorstatus_open | xdescriptorstatus_out);
        singleton.handle.f = STDIN_FILENO;
        singleton.event.descriptor = xaddressof(singleton);
        singleton.event.on         = xconsoledescriptorin_eventon;
        singleton.console  = console;

        xconsoledescriptorin_observe(xaddressof(singleton), xdescriptorstatus_open, xdescriptorparamgen(xnil), xsuccess);
        if(singleton.stream == xnil)
        {
            singleton.stream = xstreamnew(xstreamtype_buffer);
        }
    }
    return xaddressof(singleton);
}

static xint64 xconsoledescriptorin_process(xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param)
{
    switch(event)
    {
        case xdescriptorstatus_void:        xconsoledescriptoreventprocess_void(descriptor, param);         break;
        case xdescriptorstatus_open:        xconsoledescriptoreventprocess_open(descriptor, param);         break;
        case xdescriptorstatus_in:          xconsoledescriptoreventprocess_in(descriptor, param);           break;
        case xdescriptorstatus_out:         xconsoledescriptoreventprocess_out(descriptor, param);          break;
        case xdescriptorstatus_close:       xconsoledescriptoreventprocess_close(descriptor, param);        break;
        case xdescriptorstatus_exception:   xconsoledescriptoreventprocess_exception(descriptor, param);    break;
        case xdescriptorstatus_rem:         xconsoledescriptoreventprocess_rem(descriptor, param);          break;
        case xdescriptorstatus_register:    xconsoledescriptoreventprocess_register(descriptor, param);     break;
        case xdescriptorstatus_flush:       xconsoledescriptoreventprocess_flush(descriptor, param);        break;
        case xdescriptorstatus_readoff:     xconsoledescriptoreventprocess_readoff(descriptor, param);      break;
        case xdescriptorstatus_writeoff:    xconsoledescriptoreventprocess_writeoff(descriptor, param);     break;
        case xdescriptorstatus_opening:     xconsoledescriptoreventprocess_opening(descriptor, param);      break;
        case xdescriptorstatus_create:      xconsoledescriptoreventprocess_create(descriptor, param);       break;
        case xdescriptorstatus_bind:        xconsoledescriptoreventprocess_bind(descriptor, param);         break;
        case xdescriptorstatus_alloff:      xconsoledescriptoreventprocess_alloff(descriptor, param);       break;
        default: xassertion(xtrue, "");                                                                     break;
    }
}

static xint64 xconsoledescriptorin_observe(xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
{
    xconsole * console = descriptor->console;

    return console->on(console, descriptor, event, param, result);
}

static void xconsoledescriptorin_eventon(xconsoledescriptorevent * event)
{
    xconsoledescriptoreventprocess_void(event->descriptor, xdescriptorparamgen(xnil));
}

static xint64 xconsoledescriptoreventprocess_void(xconsoledescriptor * descriptor, xdescriptorparam param)
{
    xlogfunction_start("%s(%p, %p)", __func__, descriptor, param.p);

    xassertion(descriptor == xnil, "");

    if(xdescriptorstatuscheck_close(descriptor))
    {
        xdescriptoreventprocess_unregister((xdescriptor *) descriptor);
        xint64 ret = xdescriptoreventprocess_close((xdescriptor *) descriptor, xdescriptorparamgen(xnil));

        xlogfunction_end("%s(...) => %d", __func__, ret);
        return ret;
    }

    xdescriptoreventprocess_in(descriptor);

    if(xconsoledescriptorstatuscheck(descriptor, xdescriptorstatus_close) == xfalse)
    {
        if((descriptor->status & (xdescriptorstatus_in | xdescriptorstatus_out)) != (xdescriptorstatus_in | xdescriptorstatus_out))
        {
            xdescriptoreventprocess_register((xdescriptor *) descriptor);
        }
    }

    if(xdescriptorstatuscheck_close(descriptor))
    {
        xdescriptoreventprocess_unregister(descriptor);
        xdescriptoreventprocess_close(descriptor);
        xlogfunction_end("%s(...) => %d", __func__, xfail);
        return xfail;
    }

    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;    
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocess_open(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_in(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_out(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_close(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_exception(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_rem(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_register(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_flush(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_readoff(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_writeoff(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_opening(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_create(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_bind(xconsoledescriptor * descriptor, xdescriptorparam param);
static xint64 xconsoledescriptoreventprocess_alloff(xconsoledescriptor * descriptor, xdescriptorparam param);