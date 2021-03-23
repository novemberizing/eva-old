#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "handle.h"

#include "../log.h"

extern xint32 xsockethandle_shutdown(xint32 f)
{
    if(shutdown(f, SHUT_RDWR) != xsuccess)
    {
        xlogcaution("shutdown(...) => %d", errno);
    }

    if(close(f) != xsuccess)
    {
        xlogcaution("close(...) => %d", errno);
    }

    return xinvalid;
}