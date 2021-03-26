#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "thread.h"

#include "socket.h"

#include "descriptor/event/avail.h"

#include "client.h"
#include "client/pool.h"
#include "client/socket.h"
#include "client/socket/status.h"

static const xuint64 streambuffersize = 8192;

extern xclient * xclientnew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xclientobserver on, xuint64 size)
{
    xassertion(size < sizeof(xclient), "");

    xclient * client = (xclient *) calloc(size, 1);

    client->descriptor = xclientsocket_new(client, domain, type, protocol, addr, addrlen);
    client->on         = on;

    client->pool       = xnil;
    client->prev       = xnil;
    client->next       = xnil;
    
    return client;
}

extern xclient * xclientrem(xclient * client)
{
    if(client)
    {
        client->descriptor = client->descriptor->rem(client->descriptor);

        xclientpooldel(client);

        free(client);
    }

    return xnil;
}

extern xint64 xclientconnect(xclient * client)
{
    xclientsocket * o = client->descriptor;

    if(o->subscription == xnil)
    {
        xsocketcreate((xsocket *) o);
        xclientsocketconnect(o, o->addr, o->addrlen);

        return xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse && (o->status & (xsocketstatus_connect | xsocketstatus_connecting));
    }
    else
    {
        xassertion(xtrue, "");
        return xsuccess;
    }
}

extern xint64 xclientread(xclient * client)
{
    return xdescriptorstreamread((xdescriptor *) client->descriptor, client->descriptor->stream.in, streambuffersize);
}

extern xint64 xclientwrite(xclient * client)
{
    return xdescriptorstreamwrite((xdescriptor *) client->descriptor, client->descriptor->stream.out);
}

extern xint64 xclientclose(xclient * client)
{
    return xdescriptorclose((xdescriptor *) client->descriptor);
}

extern xint64 xclientsend(xclient * client, const char * data, xuint64 len)
{
    if(xdescriptorstatuscheck_open((xdescriptor *) client->descriptor))
    {
        xstreampush(client->descriptor->stream.out, data, len);
        return xdescriptorstreamwrite((xdescriptor *) client->descriptor, client->descriptor->stream.out);
    }

    return xfail;
}

extern xint64 xclientrecv(xclient * client, char * buffer, xuint64 size)
{
    if(xdescriptorstatuscheck_open((xdescriptor *) client->descriptor))
    {
        return xdescriptorstreamread((xdescriptor *) client->descriptor, client->descriptor->stream.in, streambuffersize);
    }

    return xfail;
}

extern xint64 xclientsendf(xclient * client, xstringserializer serialize, const char * format, ...)
{
//    xassertion(xtrue, "implement this");

    xclientsocket * o = client->descriptor;
    if(xdescriptoreventavail_in((xdescriptor *) o))
    {
        va_list ap;
        va_start(ap, format);
        xstreamformatv(o->stream.out, serialize, format, ap);
        va_end(ap);

        return xdescriptorstreamwrite((xdescriptor *) o, o->stream.out);
        
    }
    
    return xdescriptorstatuscheck_close((xdescriptor *) o) ? xfail : xsuccess;
    
}
