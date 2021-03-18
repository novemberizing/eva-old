#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "echo.h"
#include "../extension.h"
#include "../../client/socket.h"

struct service
{
    xserver * tcp;
    xserver * udp;
};

struct xevaechoclient
{
    xclientsocket * descriptor;
    xclientsubscriber on;           // 사용자에게 오픈되지만, 

    xclient * prev;
    xclient * next;
    xclientpool * cntr;

    xuint64 completed;
};

typedef struct xevaechoclient xevaechoclient;

static struct service service = { xnil, xnil };

static xint64 xevaechoserver_handler(xsession * session, xuint32 event, void * data, xint64 result);
static xint64 xevaechoclient_handler(xclient * o, xuint32 event, void * parameter, xint64 result);

extern xserver * xevaechoserver_get(xuint32 protocol)
{
    if(protocol == xtransmissioncontrolprotocol)
    {
        if(service.tcp == xnil)
        {
            struct sockaddr_in addr;
            addr.sin_family = PF_INET;
            addr.sin_addr.s_addr = 0;
            addr.sin_port = htons(xevaextensionport_echo);

            service.tcp = xservernew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), xevaechoserver_handler, sizeof(xserver));
        }

        return service.tcp;
    }
    else if(protocol == xuserdatagramprotocol)
    {

    }
    xassertion(xtrue, "not support protocol");
    return xnil;
}

extern xserver * xevaechoserver_del(xserver * server)
{
    if(service.tcp == server)
    {
        service.tcp = xserverrem(service.tcp);

        return service.tcp;
    }
    else if(service.tcp == server)
    {
        service.udp = xserverrem(service.udp);

        return service.udp;
    }

    return server;
}

extern void xevaechoserver_term(void)
{
    if(service.tcp != xnil)
    {
        service.tcp = xserverrem(service.tcp);
    }
    if(service.udp != xnil)
    {
        service.udp = xserverrem(service.udp);
    }
}

static xint64 xevaechoserver_handler(xsession * session, xuint32 event, void * data, xint64 result)
{
    if(event == xsessioneventtype_open)
    {
        xassertion(xsessionstreamin_get(session), "");
        xstream * stream = xstreamnew(xstreamtype_buffer);

        xsessionstreamin_set(session, stream);
        xsessionstreamout_set(session, stream);
    }
    else if(event == xsessioneventtype_close)
    {
        xstream * stream = xsessionstreamin_get(session);

        xsessionstreamin_set(session, xnil);
        xsessionstreamout_set(session, xnil);

        xstreamrem(stream);
    }
    return result;
}

extern xclient * xevaechoclient_gen(xuint32 protocol, const char * ip, xstream * stream)
{
    if(protocol == xtransmissioncontrolprotocol)
    {
        struct sockaddr_in addr;
        addr.sin_family = PF_INET;
        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htons(7);

        xevaechoclient * client = (xevaechoclient *) xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), xevaechoclient_handler, sizeof(xevaechoclient));
        client->descriptor->stream.out = stream;

        return (xclient *) client;

    }
    xassertion(xtrue, "implement this");
    return xnil;
}

static xint64 xevaechoclient_handler(xclient * o, xuint32 event, void * parameter, xint64 result)
{
    xevaechoclient * client = (xevaechoclient *) o;

    if(event == xsocketeventtype_close || event == xsocketeventtype_exception)
    {

        xstream * stream = xclientstreamout_get(o);
        if(xstreamsize_get(stream) == client->completed)
        {
            o->descriptor->status |= xsocketeventtype_rem;
        }
    }
    else if(event == xsocketeventtype_in)
    {
        if(result > 0)
        {
            printf("%s\n", "hello world");
            client->completed = client->completed + result;
        }
    }
    printf("client event => %u\n", event);

    return result;
}