#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "thread.h"

#include "socket.h"
#include "client.h"
#include "client/socket.h"

extern xclient * xclientnew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xclientsubscriber on, xuint64 size)
{
    xassertion(size < sizeof(xclient), "");
    xclient * client = (xclient *) calloc(size, 1);

    client->descriptor = xclientsocket_new(client, domain, type, protocol, addr, addrlen);
    client->on         = on;

    return client;
}

extern xint64 xclientconnect(xclient * client)
{
    xassertion(client == xnil || client->descriptor == xnil, "");
    
    xclientsocket * descriptor = client->descriptor;

    xassertion(descriptor->subscription, "");

    if(descriptor->handle.f < 0)
    {
        if(xsocketcreate((xsocket *) descriptor) != xsuccess)
        {
            return xfail;
        }
    }

    xassertion((descriptor->status & xsocketstatus_create) == xsocketstatus_void, "");

    if((descriptor->status & xsocketstatus_open) == xsocketstatus_void)
    {
        xassertion(descriptor->handle.f < 0, "");
        xassertion(descriptor->status & xsocketstatus_connect, "");

        if((descriptor->status & xsocketstatus_connecting) == xsocketstatus_void)
        {
            return xsuccess;
        }

        int ret = connect(descriptor->handle.f, descriptor->addr, descriptor->addrlen);

        if(ret != xsuccess)
        {
            if(errno == EINPROGRESS || errno == EAGAIN)
            {
                descriptor->status |= xsocketstatus_connecting;
                return xsuccess;
            }
            descriptor->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(descriptor->exception), connect, errno, xexceptiontype_system, "");
            return xfail;
        }
    }
    
    return xsuccess;
}