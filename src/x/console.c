#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "console.h"
#include "console/descriptor.h"

static xconsoledescriptor * xconsoledescriptor_rem(xconsoledescriptor * descriptor);

static xint64 xconsoledescriptorprocessor_input(xconsoledescriptor * descriptor, xuint32 event, void * parameter);
static xint64 xconsoledescriptorsubscriber_input(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val);
static xint32 xconsoledescriptorcheck_input(xconsoledescriptor * descriptor, xuint32 event);

static xconsoledescriptor consoledescriptor_in = {
    /** INHERITED EVENT TARGET */
    xconsoledescriptor_rem,
    xnil,
    xnil,
    xdescriptormask_void,
    xdescriptorstatus_void,
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle_invalid,
    xconsoledescriptorprocessor_input,
    xconsoledescriptorcheck_input,
    xconsoledescriptorsubscriber_input,
    xconsoledescriptorevent_void,
    xexception_void,
    /** CONSOLE DESCRIPTOR MEMBER */
    xnil,
    xnil
};

static xint64 xconsoledescriptorprocessor_output(xconsoledescriptor * descriptor, xuint32 event, void * parameter);
static xint64 xconsoledescriptorsubscriber_output(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val);
static xint32 xconsoledescriptorcheck_output(xconsoledescriptor * descriptor, xuint32 event);

static xconsoledescriptor consoledescriptor_out = {
    /** INHERITED EVENT TARGET */
    xconsoledescriptor_rem,
    xnil,
    xnil,
    xdescriptormask_void,
    xdescriptorstatus_void,
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle_invalid,
    xconsoledescriptorprocessor_output,
    xconsoledescriptorcheck_output,
    xconsoledescriptorsubscriber_output,
    xconsoledescriptorevent_void,
    xexception_void,
    /** CONSOLE DESCRIPTOR MEMBER */
    xnil,
    xnil
};

static xconsole console = { xnil, xnil, xnil };

static xconsoledescriptor * consoledescriptorsingleton_in = xnil;
static xconsoledescriptor * consoledescriptorsingleton_out = xnil;

extern void xconsoledescriptor_term(void)
{
    if(console.in)
    {
        console.in = xconsoledescriptor_rem(console.in);
    }
    if(console.out)
    {
        console.out = xconsoledescriptor_rem(console.out);
    }
}

extern void xconsolesubscriber_set(xconsolesubscriber subscriber)
{
    if(console.in == xnil)
    {
        console.in = (xconsoledescriptor *) xconsoledescriptorin_get();
    }
    if(console.out == xnil)
    {
        console.out = (xconsoledescriptor *) xconsoledescriptorout_get();
    }
    console.on = (subscriber ? subscriber : xconsolesubscriber_default);
}

extern xint64 xconsolesubscriber_default(xconsole * console, xuint64 event, void * parameter, xint64 value)
{
    xassertion(xtrue, "implement this");
    return value;
}

extern xdescriptor * xconsoledescriptorin_get(void)
{
    if(consoledescriptorsingleton_in == xnil)
    {
        consoledescriptorsingleton_in = xaddressof(consoledescriptor_in);
        consoledescriptorsingleton_in->handle.f = STDIN_FILENO;
        consoledescriptorsingleton_in->event.descriptor = xaddressof(consoledescriptor_in);
        consoledescriptorsingleton_in->status = (xdescriptorstatus_open | xdescriptorstatus_out);
        consoledescriptorsingleton_in->console = xaddressof(console);
        // TODO: 사용자가 버퍼를 생성할 수 있도록 하자.
        consoledescriptorsingleton_in->stream = xstreamnew(xstreamtype_default);
        console.in = consoledescriptorsingleton_in;
    }
    
    return (xdescriptor *) consoledescriptorsingleton_in;
}

extern xdescriptor * xconsoledescriptorout_get(void)
{
    if(consoledescriptorsingleton_out == xnil)
    {
        consoledescriptorsingleton_out = xaddressof(consoledescriptor_out);
        consoledescriptorsingleton_out->handle.f = STDOUT_FILENO;
        consoledescriptorsingleton_out->event.descriptor = xaddressof(consoledescriptor_out);
        consoledescriptorsingleton_out->status = (xdescriptorstatus_open | xdescriptorstatus_out | xdescriptorstatus_in);
        consoledescriptorsingleton_out->console = xaddressof(console);
        // TODO: 사용자가 버퍼를 생성할 수 있도록 하자.
        consoledescriptorsingleton_out->stream = xstreamnew(xstreamtype_default);
        console.out = consoledescriptorsingleton_out;
    }

    return (xdescriptor *) consoledescriptorsingleton_out;
}


static xconsoledescriptor * xconsoledescriptor_rem(xconsoledescriptor * descriptor)
{
    xassertion(descriptor == xnil, "");
    xassertion(descriptor->event.queue || descriptor->event.next || descriptor->event.prev, "");
    xassertion(descriptor->subscription == xnil, "");

    descriptor->console   = xnil;
    descriptor->exception = xexception_void;
    descriptor->status    = xdescriptorstatus_open;
    descriptor->stream    = xstreamrem(descriptor->stream);
    descriptor->sync      = xsyncrem(descriptor->sync);

    return descriptor;
}

static inline xint64 xconsoledescriptorprocessor_input_open(xconsoledescriptor * descriptor, void * parameter)
{
    if(xdescriptorcheck_close((xdescriptor *) descriptor) == xfalse)
    {
        if(descriptor->stream == xnil)
        {
            descriptor->stream = xstreamnew(xstreamtype_default);
        }
        if(descriptor->handle.f == xinvalid)
        {
            descriptor->handle.f = STDIN_FILENO;
        }

        if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
        {
            descriptor->status = (xdescriptorstatus_open | xdescriptorstatus_out);
        }

        return xsuccess;
    }

    return xfail;
}


static inline xint64 xconsoledescriptorprocessor_output_open(xconsoledescriptor * descriptor, void * parameter)
{
    if(xdescriptorcheck_open((xdescriptor *) descriptor))
    {
        if(descriptor->stream == xnil)
        {
            descriptor->stream = xstreamnew(xstreamtype_default);
        }
        if(descriptor->handle.f == xinvalid)
        {
            descriptor->handle.f = STDOUT_FILENO;
        }

        if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
        {
            descriptor->status = (xdescriptorstatus_open | xdescriptorstatus_in | xdescriptorstatus_out);
        }

        return xsuccess;
    }

    return xfail;
}

static inline xint64 xconsoledescriptorprocessor_out(xconsoledescriptor * descriptor, void * parameter)
{
    if(xdescriptorcheck_open((xdescriptor *) descriptor))
    {
        if(xstreamlen(descriptor->stream) > 0)
        {
            xint64 n = xdescriptorwrite((xdescriptor *) descriptor, xstreamfront(descriptor->stream), xstreamlen(descriptor->stream));
            if(n > 0)
            {
                xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + n);
            }

            return n;
        }
        return xsuccess;
    }
    return xfail;
}

static inline xint64 xconsoledescriptorprocessor_in(xconsoledescriptor * descriptor, void * parameter)
{
    if(xdescriptorcheck_open((xdescriptor *) descriptor))
    {
        xstreamadjust(descriptor->stream, xfalse);
        xstreamcapacity_set(descriptor->stream, xstreamcapacity_get(descriptor->stream) + 8192);

        xint64 n = xdescriptorread((xdescriptor *) descriptor, xstreamback(descriptor->stream), xstreamremain(descriptor->stream));
        if(n > 0)
        {
            xstreamsize_set(descriptor->stream, n + xstreamsize_get(descriptor->stream));
            return n;
        }
        return n;
    }
    return xfail;
}

static inline xint64 xconsoledescriptorprocessor_close(xconsoledescriptor * descriptor, void * parameter)
{
    if((descriptor->status & xdescriptorstatus_close) == xdescriptorstatus_void)
    {
        descriptor->status |= xdescriptorstatus_close;
    }
    return xsuccess;
}

static inline xint64 xconsoledescriptorprocessor_exception(xconsoledescriptor * descriptor, void * parameter)
{
    if((descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
    {
        descriptor->status |= xdescriptorstatus_exception;
    }

    return xsuccess;
}

static xint64 xconsoledescriptorprocessor_input(xconsoledescriptor * descriptor, xuint32 event, void * parameter)
{
    switch(event)
    {
        case xdescriptoreventtype_open:         return xconsoledescriptorprocessor_input_open(descriptor, parameter);
        case xdescriptoreventtype_in:           return xconsoledescriptorprocessor_in(descriptor, parameter);
        case xdescriptoreventtype_close:        return xconsoledescriptorprocessor_close(descriptor, parameter);
        case xdescriptoreventtype_exception:    return xconsoledescriptorprocessor_exception(descriptor, parameter);
    }
    xassertion(xtrue, "");

    return xsuccess;
}


static xint64 xconsoledescriptorsubscriber_input(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val)
{
    xassertion(descriptor == xnil, "");
    xassertion(descriptor->console == xnil, "");
    xassertion(descriptor->console->on == xnil, "");

    return descriptor->console->on(descriptor->console, event, parameter, val);
}

static xint64 xconsoledescriptorsubscriber_on(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val)
{
    xassertion(descriptor == xnil, "");
    xassertion(descriptor->console == xnil, "");
    xassertion(descriptor->console->on == xnil, "");

    return descriptor->console->on(descriptor->console, event, parameter, val);
}

static xint32 xconsoledescriptorcheck_input(xconsoledescriptor * descriptor, xuint32 event)
{
    if(event == xdescriptoreventtype_out)
    {
        return xfalse;
    }

    xassertion(xtrue, "");
}

static xint64 xconsoledescriptorprocessor_output(xconsoledescriptor * descriptor, xuint32 event, void * parameter)
{
    switch(event)
    {
        case xdescriptoreventtype_open:         return xconsoledescriptorprocessor_output_open(descriptor, parameter);
        case xdescriptoreventtype_out:          return xconsoledescriptorprocessor_out(descriptor, parameter);
        case xdescriptoreventtype_close:        return xconsoledescriptorprocessor_close(descriptor, parameter);
        case xdescriptoreventtype_exception:    return xconsoledescriptorprocessor_exception(descriptor, parameter);
    }
    xassertion(xtrue, "");

    return xsuccess;
}

static xint64 xconsoledescriptorsubscriber_output(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val)
{
    
    xassertion(descriptor == xnil, "");
    xassertion(descriptor->console == xnil, "");
    xassertion(descriptor->console->on == xnil, "");

    return descriptor->console->on(descriptor->console, event, parameter, val);
}

static xint32 xconsoledescriptorcheck_output(xconsoledescriptor * descriptor, xuint32 event)
{
    if(event == xdescriptoreventtype_out)
    {
        return xstreamlen(descriptor->stream) > 0;
    }

    xassertion(xtrue, "");
}

extern xint64 xconsoleout_string(const char * s)
{
    xconsoledescriptor * descriptor = (xconsoledescriptor *) xconsoledescriptorout_get();

    xint64 len = strlen(s);

    xstreampush(descriptor->stream, s, len);

    xint64 n = xdescriptorwrite((xdescriptor *) descriptor, xstreamfront(descriptor->stream), xstreamlen(descriptor->stream));

    if(n > 0)
    {
        xassertion(n + len < xstreamlen(descriptor->stream), "");

        xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + n);
        xstreamadjust(descriptor->stream, xfalse);
    }
    else
    {
        xassertion(len > 0, "");
        xassertion(n < 0, "");
    }

    return n;
    
}

/**
 * 현재까지 받을 수 있는 총량만을 출력한다.
 * 즉, SIZE 는 힌트일 뿐이다.
 */
extern xint64 xconsolein_string(char * buffer, xuint64 size)
{
    xassertion(buffer == xnil || size == 0, "");

    xint64 n = 0;

    xconsoledescriptor * descriptor = (xconsoledescriptor *) xconsoledescriptorin_get();

    if(size <= xstreamlen(descriptor->stream))
    {
        memcpy(buffer, xstreamfront(descriptor->stream), size);
        xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + size);
        xstreamadjust(descriptor->stream, xfalse);
        return size;
    }
    else if(xstreamlen(descriptor->stream) > 0)
    {
        xint64 n = xdescriptorread((xdescriptor *) descriptor, xstreamback(descriptor->stream), size - xstreamlen(descriptor->stream));
        if(n > 0)
        {
            xstreamsize_set(descriptor->stream, xstreamsize_get(descriptor->stream) + n);
        }
        xassertion(n < 0, "");

        xassertion(xtrue, "implement this");

        // xint64 len = xstreamlen(descriptor->str

        memcpy(buffer, xstreamfront(descriptor->stream), size);
        xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + size);
        xstreamadjust(descriptor->stream, xfalse);

        return size;
    }
    else
    {
        xint64 n = xdescriptorread((xdescriptor *) descriptor, buffer, size);

        if(n > 0)
        {
            return n;
        }
        else if(n == 0)
        {
            xassertion(n < 0, "");
            return n;
        }
        else
        {
            xassertion(n < 0, "");
            return xfail;
        }

        return n;
    }

    return xfail;
}