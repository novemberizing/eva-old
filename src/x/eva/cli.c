#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"
#include "cli.h"

#include "../console/descriptor.h"

#define xevaclicommandtype_ping         "ping"
#define xevaclicommandtype_quit         "quit"

extern xint64 xevacli(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
{
    printf("console event => %s => %ld\n", xdescriptoreventtype_str(event), result);

    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            if(xconsolestatus_get() & xconsolestatus_wait)
            {
                printf("command parse\n");
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
