#include <stdio.h>
#include <stdlib.h>

#include "../../../../thread.h"
#include "../../../../console.h"

#include "in.h"

#include "../subscription.h"
#include "../../../../descriptor/event/generator.h"
#include "../../../../event/engine.h"

typedef xint64 (*xconsoledescriptorprocess)(xconsoledescriptor *);

static const xuint64 streambuffersize = 8192;

static xint64 xconsoledescriptoreventprocessorin_void(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_open(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_in(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_out(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_close(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_exception(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_rem(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_register(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_flush(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_readoff(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_writeoff(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_opening(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_create(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_bind(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_clear(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_alloff(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_connect(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_listen(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_connecting(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorin_unregister(xconsoledescriptor * o);

static xconsoledescriptorprocess processes[xdescriptoreventtype_max] = {
    xconsoledescriptoreventprocessorin_void,        // xdescriptoreventtype_void            0
    xconsoledescriptoreventprocessorin_open,        // xdescriptoreventtype_open            1
    xconsoledescriptoreventprocessorin_in,          // xdescriptoreventtype_in              2
    xconsoledescriptoreventprocessorin_out,         // xdescriptoreventtype_out             3
    xconsoledescriptoreventprocessorin_close,       // xdescriptoreventtype_close           4
    xconsoledescriptoreventprocessorin_exception,   // xdescriptoreventtype_exception       5
    xconsoledescriptoreventprocessorin_rem,         // xdescriptoreventtype_rem             6
    xconsoledescriptoreventprocessorin_register,    // xdescriptoreventtype_register        7
    xconsoledescriptoreventprocessorin_flush,       // xdescriptoreventtype_flush           8
    xconsoledescriptoreventprocessorin_readoff,     // xdescriptoreventtype_readoff         9
    xconsoledescriptoreventprocessorin_writeoff,    // xdescriptoreventtype_writeoff       10
    xconsoledescriptoreventprocessorin_opening,     // xdescriptoreventtype_opening        11
    xconsoledescriptoreventprocessorin_create,      // xdescriptoreventtype_create         12
    xconsoledescriptoreventprocessorin_bind,        // xdescriptoreventtype_bind           13
    xconsoledescriptoreventprocessorin_clear,       // xdescriptoreventtype_clear          14
    xconsoledescriptoreventprocessorin_alloff,      // xdescriptoreventtype_alloff         15
    xconsoledescriptoreventprocessorin_connect,     // xdescriptoreventtype_connect        16
    xconsoledescriptoreventprocessorin_listen,      // xdescriptoreventtype_listen         17
    xconsoledescriptoreventprocessorin_connecting,  // xdescriptoreventtype_connecting     18
    xconsoledescriptoreventprocessorin_unregister   // xdescriptoreventtype_unregister     19
};

extern xint64 xconsoledescriptoreventprocessorin(xconsoledescriptor * o, xuint32 event)
{
    xint64 ret = xfail;

    if(event < xdescriptoreventtype_max)
    {
        return processes[event](o);
    }

    return ret;
}

static xint64 xconsoledescriptoreventprocessorin_void(xconsoledescriptor * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xconsoledescriptoreventprocessorin_register(o);
        return xsuccess;
    }

    xconsole * console = o->console;

    xassertion(console == xnil, "");

    xconsoledescriptor * out = xconsoledescriptorin_get(console);

    if((out->status & xdescriptorstatus_flush) == xdescriptorstatus_void)
    {
        xconsoledescriptoreventprocessorin_in(o);
    }

    if((o->status & xdescriptorstatus_in) == xdescriptorstatus_void)
    {
        xconsoledescriptoreventprocessorin_register(o);
    }
    else
    {
        if(o->event.queue == xnil)
        {
            xconsoledescriptoreventsubscription * subscription = o->subscription;
            xeventengine * engine = subscription ? subscription->enginenode.engine : xnil;
            if(engine)
            {
                if(o->event.queue == xnil)
                {
                    xeventengine_queue_push(engine, (xevent *) xaddressof(o->event));
                }
            }
        }
    }

    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_open(xconsoledescriptor * o)
{
    xconsoledescriptoreventprocessorin_register(o);

    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_in(xconsoledescriptor * o)
{
    xstreamadjust(o->stream, xfalse);
    if(xstreamremain(o->stream) < streambuffersize)
    {
        xstreamcapacity_set(o->stream, streambuffersize - xstreamremain(o->stream));
    }

    return xdescriptorread((xdescriptor *) o, xstreamback(o->stream), xstreamremain(o->stream));
}

static xint64 xconsoledescriptoreventprocessorin_out(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xconsoledescriptoreventprocessorin_close(xconsoledescriptor * o)
{
    xconsoledescriptoreventprocessorin_unregister(o);

    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_exception(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_rem(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_register(xconsoledescriptor * o)
{
    xconsoledescriptoreventsubscription * subscription = o->subscription;
    xdescriptoreventgenerator * generator = subscription ? subscription->generatornode.generator : xnil;

    if(generator)
    {
        if(subscription->generatornode.list == xnil)
        {
            xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, (xdescriptoreventsubscription *) subscription);
        }

        if((o->status & xdescriptorstatus_register) == xdescriptorstatus_void)
        {
            xdescriptoreventgenerator_descriptor_register(generator, (xdescriptor *) o);
        }
        return xsuccess;
    }

    return xfail;
}

static xint64 xconsoledescriptoreventprocessorin_flush(xconsoledescriptor * o)
{
    if(xstreamlen(o->stream) > 0)
    {
        xstreamclear(o->stream);
    }
    o->status &= (~xdescriptorstatus_flush);

    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_readoff(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_writeoff(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_opening(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_create(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_bind(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_clear(xconsoledescriptor * o)
{
    if(xstreamlen(o->stream) > 0)
    {
        xstreamclear(o->stream);
    }
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_alloff(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_connect(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_listen(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_connecting(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorin_unregister(xconsoledescriptor * o)
{
    xconsoledescriptoreventsubscription * subscription = o->subscription;
    xdescriptoreventgenerator * generator = subscription ? subscription->generatornode.generator : xnil;

    if(generator)
    {
        if(o->status & xdescriptorstatus_register)
        {
            xdescriptoreventgenerator_descriptor_unregister(generator, (xdescriptor *) o);
        }

        if(subscription->generatornode.list == generator->alive)
        {
            xdescriptoreventgeneratorsubscriptionlist_del((xdescriptoreventsubscription *) subscription);
        }
    }

    return xsuccess;
}