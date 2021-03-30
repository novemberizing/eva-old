#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include "echo.h"
#include "port.h"

static xserver * server = xnil;

static xint64 on(xsession * session, xuint32 event, xdescriptorparam param, xint64 result)
{

    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            xstream * in = xsessionstreamin_get(session);
            xstream * out = xsessionstreamout_get(session);

            xstreampush(out, xstreamfront(in), xstreamlen(in));
        }
    }
    
    return result;
}

extern xserver * xserverextensionecho_get(void)
{
    if(server == xnil)
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = 0;
        addr.sin_port = htons(xserverextensionport_echo);

        server = xservernew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), on, sizeof(xserver));
    }

    return server;
}

extern void xserverextensionecho_term(void)
{
    if(server == xnil)
    {
        server = xserverrem(server);
    }
}

