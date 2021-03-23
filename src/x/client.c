#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "thread.h"

#include "socket.h"
#include "client.h"
#include "client/socket.h"
#include "client/socket/status.h"

extern xclient * xclientnew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xclientobserver on, xuint64 size)
{
    xassertion(size < sizeof(xclient), "");

    xclient * client = (xclient *) calloc(size, 1);

    client->descriptor = xclientsocket_new(client, domain, type, protocol, addr, addrlen);
    client->on = on;
    
    return client;
}

extern xclient * xclientrem(xclient * client)
{
    if(client)
    {
        client->descriptor = client->descriptor->rem(client->descriptor);

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
    if(client->descriptor->stream.in == xnil)
    {
        client->descriptor->stream.in = xstreamnew(xstreamtype_buffer);
    }

    return xdescriptorread((xdescriptor *) client->descriptor, xstreamback(client->descriptor->stream.in), xstreamremain(client->descriptor->stream.in));
}

extern xint64 xclientwrite(xclient * client)
{
    if(client->descriptor->stream.out == xnil)
    {
        client->descriptor->stream.out = xstreamnew(xstreamtype_buffer);
    }

    return xdescriptorwrite((xdescriptor *) client->descriptor, xstreamfront(client->descriptor->stream.out), xstreamlen(client->descriptor->stream.out));
}

extern xint64 xclientclose(xclient * client)
{
    return xdescriptorclose((xdescriptor *) client->descriptor);
}

extern xint64 xclientsend(xclient * client, const char * data, xuint64 len)
{
    if(client->descriptor->stream.out)
    {
        if(xdescriptorstatuscheck_open((xdescriptor *) client->descriptor))
        {
            xstreampush(client->descriptor->stream.out, data, len);

            return xdescriptorwrite((xdescriptor *) client->descriptor, xstreamfront(client->descriptor->stream.out), xstreamlen(client->descriptor->stream.out));
        }
    }
    else
    {
        return xdescriptorwrite((xdescriptor *) client->descriptor, data, len);
    }

    return xfail;
}

extern xint64 xclientrecv(xclient * client, char * buffer, xuint64 size)
{
    xint64 ret = xfail;

    xclientsocket * o = client->descriptor;

    if(o->stream.in)
    {
        if(size <= xstreamlen(o->stream.in))
        {
            memcpy(buffer, xstreamfront(o->stream.in), size);
            xstreampos_set(o->stream.in, xstreampos_get(o->stream.in) + size);
            return size;
        }
        else
        {
            xint64 ret = xdescriptorread((xdescriptor *) o, xstreamback(o->stream.in), size - xstreamlen(o->stream.in));
            if(ret > 0)
            {
                xstreamsize_set(o->stream.in, xstreamsize_get(o->stream.in) + ret);

                if(size <= xstreamlen(o->stream.in))
                {
                    memcpy(buffer, xstreamfront(o->stream.in), size);
                    xstreampos_set(o->stream.in, xstreampos_get(o->stream.in) + size);
                    return size;
                }
                return xsuccess;
            }
            return ret;
        }
    }
    else
    {
        return xdescriptorread((xdescriptor *) o, buffer, size);
    }

    return ret;
}
