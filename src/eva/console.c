#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>
#include <x/stream.h>

#include "console.h"

#include <x/socket.h>

static xint32 __ready = xfalse;

extern xint64 evacli(xconsole * console, xconsoledescriptor * descriptor, xuint64 event, void * parameter, xint64 value)
{
    xlogfunction_start("%s(%p, %p, %lu, %p, %ld)", __func__, console, descriptor, event, parameter, value);

    if(event == xdescriptorstatus_register)
    {
        if(__ready == xfalse)
        {
            if(xdescriptoreventsubscription_get((xdescriptor *) console->in) && xdescriptoreventsubscription_get((xdescriptor *) console->out))
            {
                __ready = xtrue;

                xconsoleout_string("greeting\n");
                xconsoleout_string("eva> ");
                xconsoleout_flush();
            }
        }
    }
    else if(event == xdescriptorstatus_in)
    {
        if(value > 0)
        {
            xstream * stream = xconsoledescriptorstream_get(descriptor);

            

            // byte stream to command

            // stream parse
            // if(xstreamlne(stream) > 0)

            
            printf("event in => %s(%p, %p, %lu, %p, %ld)\n", __func__, console, descriptor, event, parameter, value);
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, value);
    return value;
}
