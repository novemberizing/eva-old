#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>

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

    // xcheck(xtrue, "event => %s", xsocketeventtype_str(event));
    // if(event == xdescriptoreventtype_register)
    // {
    //     printf("= 1 =\n");
    //     // CONSOLE IN REGISTER & CONSOLE OUT REGISTER
    //     if(__ready == xfalse)
    //     {
    //         printf("= 2 = 0x%08x\n", xdescriptorstatus_get((xdescriptor *) console->in));
    //         if(xdescriptorcheck_register((xdescriptor *) console->in) && xdescriptorcheck_register((xdescriptor *) console->out))
    //         {
    //             printf("= 3 =\n");
    //             __ready = xtrue;
    //             xconsoleout_string("hello world\n");
    //         }
    //     }

    //     printf("register => parameter => %p, value => %ld\n", parameter, value);
    // }
    if(__ready == xfalse)
    {
        if(xdescriptorstatus_get((xdescriptor *) console->in) == xdescriptorstatus_in)
        {
            if(xdescriptorstatus_get((xdescriptor *) console->in) == xdescriptorstatus_out)
            {
                __ready = xtrue;
                printf("= 3 =\n");
            }
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, value);
    return value;
}
