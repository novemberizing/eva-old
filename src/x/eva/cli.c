#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"
#include "cli.h"

extern xint64 xevacli(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
{
    printf("console event => %s\n", xdescriptoreventtype_str(event));

    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            char * s = param.p;
            s[result] = 0;
            printf("%s\n", (char *) param.p);
        }
    }
    else if(event == xdescriptoreventtype_out)
    {

    }
    else if(event == xdescriptoreventtype_register)
    {

    }
    else if(event == xdescriptoreventtype_open)
    {
        if(descriptor == xconsoledescriptorout_get())
        {
            // TODO: IMPLEMENT THIS `eva> ....`
            xassertion(xtrue, "implement this");
        }
    }
    else
    {

    }

    return result;
}
