#include <stdio.h>
#include <stdlib.h>

#include "../../../../thread.h"

#include "out.h"

#include "../subscription.h"
#include "../../../../descriptor/event/generator.h"
#include "../../../../event/engine.h"

typedef xint64 (*xconsoledescriptorprocess)(xconsoledescriptor *);

static const xuint64 streambuffersize = 8192;
static const xint32 maxretrycount = 32;

static xint64 xconsoledescriptoreventprocessorout_void(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_open(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_in(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_out(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_close(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_exception(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_rem(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_register(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_flush(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_readoff(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_writeoff(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_opening(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_create(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_bind(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_clear(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_alloff(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_connect(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_listen(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_connecting(xconsoledescriptor * o);
static xint64 xconsoledescriptoreventprocessorout_unregister(xconsoledescriptor * o);

static xconsoledescriptorprocess processes[xdescriptoreventtype_max] = {
    xconsoledescriptoreventprocessorout_void,       // xdescriptoreventtype_void            0
    xconsoledescriptoreventprocessorout_open,       // xdescriptoreventtype_open            1
    xconsoledescriptoreventprocessorout_in,         // xdescriptoreventtype_in              2
    xconsoledescriptoreventprocessorout_out,        // xdescriptoreventtype_out             3
    xconsoledescriptoreventprocessorout_close,      // xdescriptoreventtype_close           4
    xconsoledescriptoreventprocessorout_exception,  // xdescriptoreventtype_exception       5
    xconsoledescriptoreventprocessorout_rem,        // xdescriptoreventtype_rem             6
    xconsoledescriptoreventprocessorout_register,   // xdescriptoreventtype_register        7
    xconsoledescriptoreventprocessorout_flush,      // xdescriptoreventtype_flush           8
    xconsoledescriptoreventprocessorout_readoff,    // xdescriptoreventtype_readoff         9
    xconsoledescriptoreventprocessorout_writeoff,   // xdescriptoreventtype_writeoff       10
    xconsoledescriptoreventprocessorout_opening,    // xdescriptoreventtype_opening        11
    xconsoledescriptoreventprocessorout_create,     // xdescriptoreventtype_create         12
    xconsoledescriptoreventprocessorout_bind,       // xdescriptoreventtype_bind           13
    xconsoledescriptoreventprocessorout_clear,      // xdescriptoreventtype_clear          14
    xconsoledescriptoreventprocessorout_alloff,     // xdescriptoreventtype_alloff         15
    xconsoledescriptoreventprocessorout_connect,    // xdescriptoreventtype_connect        16
    xconsoledescriptoreventprocessorout_listen,     // xdescriptoreventtype_listen         17
    xconsoledescriptoreventprocessorout_connecting, // xdescriptoreventtype_connecting     18
    xconsoledescriptoreventprocessorout_unregister  // xdescriptoreventtype_unregister     19
};

extern xint64 xconsoledescriptoreventprocessorout(xconsoledescriptor * o, xuint32 event)
{
    xint64 ret = xfail;

    if(event < xdescriptoreventtype_max)
    {
        return processes[event](o);
    }

    return ret;
}

static xint64 xconsoledescriptoreventprocessorout_void(xconsoledescriptor * o)
{
    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xconsoledescriptoreventprocessorout_unregister(o);
        return xsuccess;
    }

    xconsole * console = o->console;

    xassertion(console == xnil, "");

    xconsoledescriptoreventprocessorout_flush(o);

    if((o->status & xdescriptorstatus_out) == xdescriptorstatus_void)
    {
        xconsoledescriptoreventprocessorout_register(o);
    }
    else
    {
        if(o->event.queue == xnil && xstreamlen(o->stream) > 0)
        {
            xconsoledescriptoreventsubscription * subscription = o->subscription;
            xeventengine * engine = subscription ? subscription->enginenode.engine : xnil;
            if(engine)
            {
                xeventengine_queue_push(engine, (xevent *) xaddressof(o->event));
            }
        }
    }

    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_open(xconsoledescriptor * o)
{
    xconsoledescriptoreventprocessorout_register(o);

    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_in(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xfail;
}

static xint64 xconsoledescriptoreventprocessorout_out(xconsoledescriptor * o)
{
    xint64 ret = xdescriptorwrite((xdescriptor *) o, xstreamfront(o->stream), xstreamlen(o->stream));

    if(ret > 0)
    {
        xstreampos_set(o->stream, xstreampos_get(o->stream) + ret);
        xstreamadjust(o->stream, xfalse);
    }

    return ret;
    // xstreamadjust(o->stream, xfalse);
    // if(xstreamremain(o->stream) < streambuffersize)
    // {
    //     xstreamcapacity_set(o->stream, streambuffersize - xstreamremain(o->stream));
    // }

    // return xdescriptorread((xdescriptor *) o, xstreamback(o->stream), xstreamremain(o->stream));
}

static xint64 xconsoledescriptoreventprocessorout_close(xconsoledescriptor * o)
{
    xconsoledescriptoreventprocessorout_unregister(o);

    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_exception(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_rem(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_register(xconsoledescriptor * o)
{
    xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) o->subscription;
    xdescriptoreventgenerator * generator = subscription ? subscription->generatornode.generator : xnil;

    if(generator)
    {
        if(subscription->generatornode.list == xnil)
        {
            xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
        }

        if((o->status & xdescriptorstatus_register) == xdescriptorstatus_void)
        {
            xdescriptoreventgenerator_descriptor_register(generator, (xdescriptor *) o);
        }
        return xsuccess;
    }

    return xfail;
}

static xint64 xconsoledescriptoreventprocessorout_flush(xconsoledescriptor * o)
{
    for(xint32 i = 0; i < maxretrycount && xstreamlen(o->stream) > 0; i++)
    {
        xdescriptorwrite((xdescriptor *) o, xstreamfront(o->stream), xstreamlen(o->stream));
    }

    if(xstreamlen(o->stream) == 0)
    {
        o->status &= (~xdescriptorstatus_flush);
        xstreamcapacity_set(o->stream, streambuffersize);
    }

    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_readoff(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_writeoff(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_opening(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_create(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_bind(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_clear(xconsoledescriptor * o)
{
    if(xstreamlen(o->stream) > 0)
    {
        xstreamclear(o->stream);
    }
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_alloff(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_connect(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_listen(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_connecting(xconsoledescriptor * o)
{
    xassertion(xtrue, "");
    return xsuccess;
}

static xint64 xconsoledescriptoreventprocessorout_unregister(xconsoledescriptor * o)
{
    xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) o->subscription;
    xdescriptoreventgenerator * generator = subscription ? subscription->generatornode.generator : xnil;

    if(generator)
    {
        if(o->status & xdescriptorstatus_register)
        {
            xdescriptoreventgenerator_descriptor_unregister(generator, (xdescriptor *) o);
        }

        if(subscription->generatornode.list == generator->alive)
        {
            xdescriptoreventgeneratorsubscriptionlist_del(subscription);
        }
    }

    return xsuccess;
}