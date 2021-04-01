#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include <x/time.h>
#include <x/client/pool.h>
#include <x/event/engine.h>
#include <x/eva/cli.h>
#include <x/console.h>
#include <x/socket.h>

xtime start = { 0, 0 };
xtime end = { 0, 0 };

xuint64 n = 0;
xuint64 total = 0;

char packet[2048];

static void benchmark_packet_init()
{
    xrandominit();

    for(xuint64 i = 0; i < 1024; i++)
    {
        packet[i] = (char) (xrandomget() % 26) + 97;
    }
    packet[1024] = 0;
}

static xint64 on(xclientpool * pool, xclient * client, xuint64 event, xdescriptorparam param, xint64 result)
{
    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            end = xtimeget();
            xtime diff = xtimediff(xaddressof(end), xaddressof(start));

            total = total + result / 1024;
            n = n + result % 1024;

            if(n >= 1024)
            {
                total = total + n / 1024;
                n = n % 1024;
            }
            

            if(total % 100000 == 0)
            {
                xconsoleout("event on => %s / [ %ld.%09ld , %ld ]\n", xdescriptoreventtype_str(event), diff.second, diff.nanosecond, total);
                xconsoleout("event on => %s / | %ld.%09ld | %ld |\n", xdescriptoreventtype_str(event), diff.second, diff.nanosecond, total);
            }

            xclientsend(client, packet, 1024);
        }
    }
    else if(event == xdescriptoreventtype_open)
    {
        start = xtimeget();
        xclientsend(client, packet, 1024);

        // xclientsendf(client, xstringformatserialize ,"PING\r\n");
    }

    return result;
}

int main(int argc, char ** argv)
{
    xlogconsole_set(xtrue);
    xlogmask_set(xlogtype_assertion);
    benchmark_packet_init();

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(3371);
    
    xeventengine * engine = xeventengine_new();

    xclientpool * pool = xclientpoolnew(on, sizeof(xclientpool));

    for(xint32 i = 0; i < 25; i++)
    {
        xclientpooladd(pool, xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), xnil, sizeof(xclientpool)));
    }

    xeventengine_cli(engine, xevacli);

    xeventengine_clientpool_add(engine, pool);

    xeventengine_run(engine);

    xclientpoolrem(pool, xclientrem);

    xconsoleterm();
    xlogterm();

    return 0;
}