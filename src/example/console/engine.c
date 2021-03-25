#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include <x/time.h>
#include <x/client/pool.h>
#include <x/event/engine.h>
#include <x/eva/cli.h>

xtime start = { 0, 0 };
xtime end = { 0, 0 };

xuint64 n = 0;
xuint64 total = 0;

static xint64 on(xclientpool * pool, xclient * client, xuint64 event, xdescriptorparam param, xint64 result)
{
    printf("event on => %s\n", xdescriptoreventtype_str(event));
    return result;
}

int main(int argc, char ** argv)
{
    xlogconsole_set(xtrue);
    xlogmask_set(xlogtype_assertion);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // addr.sin_addr.s_addr = inet_addr("192.168.0.128");
    addr.sin_port = htons(6379);
    
    xeventengine * engine = xeventengine_new();

    xclientpool * pool = xclientpoolnew(on, sizeof(xclientpool));

    for(xint32 i = 0; i < 32; i++)
    {
        xclientpooladd(pool, xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), xnil, sizeof(xclientpool)));
    }

    xeventengine_clientpool_add(engine, pool);

    xeventengine_cli(engine, xevacli);

    // xeventengine_cli_set(evacli);
    
    xeventengine_run(engine);

    xclientpoolrem(pool);

    return 0;
}