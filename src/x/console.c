#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "console.h"
#include "console/descriptor.h"
#include "console/descriptor/event/processor/in.h"
#include "console/descriptor/event/processor/out.h"
#include "event/engine.h"

struct xconsole
{
    xconsoledescriptor in;
    xconsoledescriptor out;
    xconsoleobserver   on;
    xuint32            status;
};

static xconsoledescriptor * xconsoledescriptor_rem(xconsoledescriptor * o);

static xint64 xconsoledescriptoron(xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result);

static void xconsoledescriptoreventon_in(xconsoledescriptorevent * event);
static void xconsoledescriptoreventon_out(xconsoledescriptorevent * event);

static xconsole singleton = {
    {
        xconsoledescriptor_rem,                 // singleton.in.rem
        xnil,                                   // singleton.in.subscription
        xnil,                                   // singleton.in.sync
        xdescriptormask_void,                   // singleton.in.mask
        xdescriptorstatus_void,                 // singleton.in.status
        xdescriptorhandle_invalid,              // singleton.in.handle
        xconsoledescriptoreventprocessorin,     // singleton.in.process
        xnil,                                   // singleton.in.check: deprecated
        xconsoledescriptoron,                   // singleton.in.observer
        {
            xnil,                                   // singleton.in.event.prev
            xnil,                                   // singleton.in.event.next
            xnil,                                   // singleton.in.event.queue
            xconsoledescriptoreventon_in,           // singleton.in.event.on
            xnil                                    // singleton.in.event.descriptor
        },
        xexception_void,                        // singleton.in.exception
        xnil,                                   // singleton.in.console
        xnil                                    // singleton.in.stream
    },
    {
        xconsoledescriptor_rem,                 // singleton.out.rem
        xnil,                                   // singleton.out.subscription
        xnil,                                   // singleton.out.sync
        xdescriptormask_void,                   // singleton.out.mask
        xdescriptorstatus_void,                 // singleton.out.status
        xdescriptorhandle_invalid,              // singleton.out.handle
        xconsoledescriptoreventprocessorout,    // singleton.out.process
        xnil,                                   // singleton.out.check: deprecated
        xconsoledescriptoron,                   // singleton.out.observer
        {
            xnil,                                   // singleton.out.event.prev
            xnil,                                   // singleton.out.event.next
            xnil,                                   // singleton.out.event.queue
            xconsoledescriptoreventon_out,          // singleton.out.event.on
            xnil                                    // singleton.out.event.descriptor
        },
        xexception_void,                        // singleton.out.exception
        xnil,                                   // singleton.out.console
        xnil                                    // singleton.out.stream
    },
    xnil                                    // singleton.on
};

extern void xconsoleobserver_set(xconsoleobserver on)
{
    singleton.on = on;
}

extern void xconsoleinit(xconsoleobserver on)
{
    xassertion(singleton.on || on == xnil, "");

    if(singleton.on == xnil)
    {
        singleton.in.handle.f          = STDIN_FILENO;
        singleton.in.status            = (xdescriptorstatus_open | xdescriptorstatus_out);
        singleton.in.event.descriptor  = xaddressof(singleton.in);
        singleton.in.console           = xaddressof(singleton);

        singleton.out.handle.f         = STDOUT_FILENO;
        singleton.out.status           = (xdescriptorstatus_open | xdescriptorstatus_out);
        singleton.out.event.descriptor = xaddressof(singleton.out);
        singleton.out.console          = xaddressof(singleton);

        singleton.on                   = on;

        singleton.in.on(xaddressof(singleton.in), xdescriptoreventtype_create, xdescriptorparamgen(xnil), xsuccess);
        singleton.out.on(xaddressof(singleton.out), xdescriptoreventtype_create, xdescriptorparamgen(xnil), xsuccess);

        if(singleton.in.stream == xnil)
        {
            singleton.in.stream = xstreamnew(xstreamtype_buffer);
        }

        if(singleton.out.stream == xnil)
        {
            singleton.out.stream = xstreamnew(xstreamtype_buffer);
        }

        singleton.in.on(xaddressof(singleton.in), xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess);
        singleton.out.on(xaddressof(singleton.out), xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess);
    }
}

extern xconsoledescriptor * xconsoledescriptorin_get(void)
{
    return xaddressof(singleton.in);
}

extern xconsoledescriptor * xconsoledescriptorout_get(void)
{
    return xaddressof(singleton.out);
}

static xconsoledescriptor * xconsoledescriptor_rem(xconsoledescriptor * o)
{
    if(o)
    {
        xassertion(o->event.queue, "");
        xassertion(o->subscription->enginenode.engine || o->subscription->generatornode.generator || o->subscription->generatornode.list, "");

        o->mask         = xdescriptormask_void;
        o->status       = xdescriptorstatus_void;
        o->subscription = xobjectrem(o->subscription);
        o->sync         = xsyncrem(o->sync);
        o->handle.f     = xinvalid;
        o->stream       = xstreamrem(o->stream);
        o->exception    = xexception_void;
    }

    return o;
}

static xint64 xconsoledescriptoron(xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
{
    xconsole * console = descriptor->console;
    return console->on(console, descriptor, event, param, result);
}

static void xconsoledescriptoreventon_in(xconsoledescriptorevent * event)
{
    xconsoledescriptoreventprocessorin(event->descriptor, xdescriptoreventtype_void);
}

static void xconsoledescriptoreventon_out(xconsoledescriptorevent * event)
{
    xconsoledescriptoreventprocessorout(event->descriptor, xdescriptoreventtype_void);
}

extern void xconsoleout(const char * format, ...)
{
    va_list ap;
    va_start(ap, format);
    xstreamformatv(singleton.out.stream, xstringformatserialize, format, ap);
    va_end(ap);

    singleton.out.process(xaddressof(singleton.out), xdescriptoreventtype_void);
}

extern void xconsolestatus_set(xuint32 value)
{
    singleton.status = value;
}

extern void xconsolestatus_add(xuint32 status)
{
    singleton.status |= status;
}

extern void xconsolestatus_del(xuint32 status)
{
    singleton.status &= (~status);
}

extern xuint32 xconsolestatus_get(void)
{
    return singleton.status;
}
