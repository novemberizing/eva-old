#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/client.h>
#include <x/extension/redis/req.h>
#include <x/extension/redis/res.h>
// #include <x/extension/echo/req.h>
// #include <x/extension/echo/res.h>

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

    const xint32 total = 65536;
    xtime diff[total];

    for(xint32 i = 0; i < total; i++)
    {
        xredisres * res = (xredisres *) xclientwaitres(client, xclientreq(client, (xreq *) xredisreqgen_set("foo", "bar")), -1);
        // xechores * res = (xechores *) xclientwaitres(client, xclientreq(client, (xreq *) xechoreqnew("PING\r\n")), -1);
        if(xrescheck_complete(res))
        {
            diff[i] = xtimediff(xaddressof(res->end), xaddressof(res->req->start));
            // xtime diff = xtimediff(xaddressof(res->end), xaddressof(res->req->start));
            // printf("%ld.%09ld\n", res->req->start.second, res->req->start.nanosecond);
            // printf("%ld.%09ld\n", diff.second, diff.nanosecond);

            // printf("%s\n", res->)
            // printf("%.*s\n", (int) res->size, res->value);
        }
        res = xredisresrem(res);
    }

    for(xint32 i = 0; i < total; i++)
    {
        printf("%ld.%09ld\n", diff[i].second, diff[i].nanosecond);
    }

    xclientrem(client);
    return 0;
}