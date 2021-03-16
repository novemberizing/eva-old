#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>
#include <x/stream.h>
#include <x/string.h>
#include <x/socket.h>
#include <x/command/string.h>

#include "../console.h"
#include "../eva.h"

static xint32 __ready = xfalse;

#define xconsolecommandtype_quit        (0x74697571u)            // "quit"

static void xconsolecommandfunc(xcommandstring * command)
{
    if(command && command->strings.size > 0)
    {
        switch(xinteger32from_str(xstringto_lower(xnil, command->strings.cntr[0])))
        {
        case xconsolecommandtype_quit: xevaquit();  break;
        }
    }
}

extern xint64 xevacli(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 value)
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
            // 아래의 로직은 수행하지 않을 수 있는 방법을 찾아야 한다.
            if(xstreamremain(stream) == 0)
            {
                xstreamcapacity_set(stream, xstreamcapacity_get(stream) + 1);
            }

            char * s = xstreamfront(stream);
            s[xstreamlen(stream)] = 0;

            char * line = xnil;

            const char * start = s;
            const char * end = xnil;

            while((end = xstringline_get(start, xnil)), start != xnil)
            {
                char * line = xstringline_dup(xnil, start, end);
                xcommandstring * command = xcommandstringfrom_line(line, xconsolecommandfunc);
                xcommandexec(command);
                xcommandstring_rem(command);
                free(line);
                start = end;
            }
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, value);
    return value;
}
