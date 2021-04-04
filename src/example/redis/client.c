#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/client.h>
#include <x/extension/redis.h>

static xint64 on(xclient * client, xuint32 event, xdescriptorparam param, xint64 result)
{
    return result;
}

#define xredisreq_append    0

#define xredisreq_max       1

xtime diff[xredisreq_max] = { 0, };

static xredisres * xredisrescheck(int i, xredisres * o)
{
    if(xrescheck_complete(o))
    {
        diff[i] = xtimediff(xaddressof(o->end), xaddressof(o->req->start));
        printf("reply[%d] => ", i);
        xredisobject_print(o->object);
    }

    return xredisresrem(o);
}

static const char * xredisreqstr(xint32 i)
{
    switch(i)
    {
        case xredisreq_append:  return "append";
        default:                return "unknown";
    }
}

static char key[256] = { 0, };

static char randomdatabuf[512];

static const char * randomkey(void)
{
    int n = snprintf(key, 256, "%lu", xrandomget());
    key[n] = 0;

    return key;
}

static void randomdatagen(char * data, xuint64 n)
{
    for(xuint64 i = 0; i < n; i++)
    {
        data[i] = 97 + xrandominteger64(26);
    }
    data[n] = 0;
}

int main(int argc, char ** argv)
{
    xloginit(xnil, xlogtype_assertion, xtrue);
    xrandominit();
    randomdatagen(randomdatabuf, 256);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(6379);

    xclient * client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), on, sizeof(xclient));
    xclientmask_add(client, xdescriptormask_nonblock);
    xclientconnect(client);
    xclientwait(client, xdescriptorstatus_open, -1);

    xclientrem(client);
    return 0;
}