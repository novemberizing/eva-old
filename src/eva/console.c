#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>

#include "console.h"

#include <x/socket.h>

extern xint64 evacli(xconsole * console, xuint64 event, void * parameter, xint64 value)
{
    xcheck(xtrue, "event => %s", xsocketeventtype_str(event));
    return value;
}