#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../thread.h"
#include "cli.h"

#include "../event/engine.h"
#include "../console/descriptor.h"

#define xevacommandtype_ping    0x676e6970u
#define xevacommandtype_quit    0x74697571u

static xeventengine * __engine = xnil;    // 임시적으로 QUIT 을 위한 이벤트 엔진을 변수로 할당하자.

extern void xevacli_init(xeventengine * engine)
{
    __engine = engine;
}

static xint32 xevacommand_ping(void)
{
    xconsoleout("pong\n\n");
    return xsuccess;
}

static void xeventenginecancelcb(xeventengine * engine)
{

}

static xint32 xevacommand_quit(void)
{
    xconsoleout("bye\n\n");
    xeventengine_cancel(__engine, xeventenginecancelcb);
    return xsuccess;
}

static xint32 xevacommand_fail(const char * format, ...)
{
    va_list ap;
    va_start(ap, format);
    xconsoleoutv(format, ap);
    va_end(ap);
}

static xint32 xevacommand_exec(char * strings, xuint64 count)
{
    if(count > 0)
    {
        if(strlen(strings) == 4)
        {
            xuint32 type = *((xuint32 *) strings);
            switch(type)
            {
                case xevacommandtype_ping:  return xevacommand_ping();
                case xevacommandtype_quit:  return xevacommand_quit();
                default:                    return xevacommand_fail("not supported command (%s)\n\n", strings);
            }
            return xsuccess;
        }
        else
        {
            xconsoleout("command type is always length 4\n\n");
        }
    }

    return xfail;
}

extern xint64 xevacli(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
{
    // printf("console event => %s => %ld\n", xdescriptoreventtype_str(event), result);

    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            if(xconsolestatus_get() & xconsolestatus_wait)
            {
                char * buffer = (char *) xstreamfront(descriptor->stream);
                xuint64 total = xstreamlen(descriptor->stream);
                char *   next = xnil;
                xuint64 index = 0;

                do {
                    total = xstreamlen(descriptor->stream);
                    next  = xstringline_next((char *) xstreamfront(descriptor->stream), xaddressof(index), total);
                    if(index < total)
                    {
                        
                        // xcommandstring command = xcommandstring_init(xnil, )
                        char * strings = xnil;
                        xuint64 count = xstringwhitespace_split(xaddressof(strings), buffer, index + 1);
                        if(strings)
                        {
                            xevacommand_exec(strings, count);
                            free(strings);
                        }

                        xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + index + 1);
                    }
                } while(next && index < total);

                result = xsuccess;

                xconsolestatus_set(xconsolestatus_void);

                xconsoleout("eva> ");
                // TODO: COMMAND PARSING
            }
            else
            {
                result = 0;
            }
        }
    }
    else if(event == xdescriptoreventtype_out)
    {
        if(result > 0)
        {
            if(xstreamlen(descriptor->stream) == 0)
            {
                xconsolestatus_set(xconsolestatus_wait);
            }
        }
    }
    else if(event == xdescriptoreventtype_register)
    {

    }
    else if(event == xdescriptoreventtype_open)
    {
        if(descriptor == xconsoledescriptorout_get())
        {
            xconsoleout("eva> ");
            // TODO: IMPLEMENT THIS `eva> ....`
            // xassertion(xtrue, "implement this");
        }
    }
    else
    {

    }

    return result;
}
