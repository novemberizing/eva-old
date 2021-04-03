#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/client.h>
#include <x/extension/echo/req.h>
#include <x/extension/echo/res.h>

static xint64 on(xclient * client, xuint32 event, xdescriptorparam param, xint64 result)
{
    // printf("event => %s\n", xdescriptoreventtype_str(event));
    return result;
}

int main(int argc, char ** argv)
{
    xloginit(xnil, xlogtype_assertion, xtrue);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(6379);

    xclient * client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), on, sizeof(xclient));
    xclientmask_add(client, xdescriptormask_nonblock);
    xclientconnect(client);
    xclientwait(client, xdescriptorstatus_open, -1);

    for(xint32 i = 0; i < 32; i++)
    {
        xechores * res = (xechores *) xclientwaitres(client, xclientreq(client, (xreq *) xechoreqnew("PING\r\n")), -1);
        if(xrescheck_complete(res))
        {
            xtime diff = xtimediff(xaddressof(res->end), xaddressof(res->req->start));
            printf("%ld.%09ld\n", diff.second, diff.nanosecond);
            printf("%.*s\n", (int) res->size, res->value);
        }
        res = xechoresrem(res);
    }

    xclientrem(client);
    return 0;
}