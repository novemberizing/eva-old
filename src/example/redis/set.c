#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>

#include <x/time.h>
#include <x/client/pool.h>
#include <x/event/engine.h>
#include <x/eva/cli.h>
#include <x/console.h>
#include <x/socket.h>
#include <x/extension/redis/client.h>

xtime start = { 0, 0 };
xtime end = { 0, 0 };

xuint64 n = 0;
xuint64 total = 0;
xuint64 count = 0;

char packet[2048];

static void redisbenchmark_packet_init(void)
{
    xrandominit();

    for(xuint64 i = 0; i < 1024; i++)
    {
        packet[i] = (char) (xrandomget() % 26) + 97;
    }
    packet[1024] = 0;
}

static void redisbenchmark_packet_send(xclient * client, xuint64 i)
{
    char key[256];
    snprintf(key, 256, "key-%lu", i);
    xredisclientsenddata_set(client, key, packet, 1024);
}

static xint64 on(xclientpool * pool, xclient * client, xuint64 event, xdescriptorparam param, xint64 result)
{

    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            xstream * in = xclientstreamin_get(client);
            xuint64 index = 0;
            xredisstring * o = (xredisstring *) xredisobject_deserialize(xstreamfront(in), xaddressof(index), xstreamlen(in));

            if(o != xnil)
            {
                total = total + 1;
                xredisstring_rem(o);

                if(total % 200000 == 0)
                {
                    end = xtimeget();
                    xtime diff = xtimediff(xaddressof(end), xaddressof(start));
                    // printf("event on => %s / [%ld.%09ld / %ld]\n", xdescriptoreventtype_str(event), diff.second, diff.nanosecond, total);
                    xconsoleout("event on => %s / [%ld.%09ld , %ld]\n", xdescriptoreventtype_str(event), diff.second, diff.nanosecond, total);
                    xconsoleout("event on => %s / | %ld.%09ld | %ld |\n", xdescriptoreventtype_str(event), diff.second, diff.nanosecond, total);
                }

                redisbenchmark_packet_send(client, count++);
                return result;
            }
        }
    }
    else if(event == xdescriptoreventtype_open)
    {
        start = xtimeget();

        redisbenchmark_packet_send(client, count++);

        // xredisclientsenddata_set(client, "foo", packet, 1024);
    }

    return result;
}

int main(int argc, char ** argv)
{
    redisbenchmark_packet_init();

    xlogconsole_set(xtrue);
    xlogmask_set(xlogtype_assertion);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // addr.sin_addr.s_addr = inet_addr("192.168.0.128");
    addr.sin_port = htons(6379);
    
    xeventengine * engine = xeventengine_new();

    xclientpool * pool = xclientpoolnew(on, sizeof(xclientpool));

    for(xint32 i = 0; i < 50; i++)
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