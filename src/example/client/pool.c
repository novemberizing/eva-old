#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include <x/client/pool.h>
#include <x/event/engine.h>

static xint64 on(xclientpool * pool, xclient * client, xuint64 event, xdescriptorparam param, xint64 result)
{
    if(event == xdescriptoreventtype_in)
    {
        printf("event on => %s / %s", xdescriptoreventtype_str(event), (char *) param.p);
    }
    else if(event == xdescriptoreventtype_out)
    {
        printf("event on => %s / %s", xdescriptoreventtype_str(event), (const char *) param.c);
    }
    else if(event == xdescriptoreventtype_exception)
    {
        xexception * exception = (xexception *) param.p;
        printf("exception no => %d\n", exception->number);
        printf("exception type => %d\n", exception->type);
        printf("event on => %s\n", xdescriptoreventtype_str(event));
    }
    else if(event == xdescriptoreventtype_open)
    {
        xclientsendf(client, xstringformatserialize ,"PING\r\n");
    }
    else
    {
        printf("event on => %s\n", xdescriptoreventtype_str(event));
    }
    return result;
}

int main(int argc, char ** argv)
{
    xlogconsole_set(xtrue);
    xlogmask_set(xlogtype_assertion);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(6379);
    
    xeventengine * engine = xeventengine_new();

    xclientpool * pool = xclientpoolnew(on, sizeof(xclientpool));

    xclientpooladd(pool, xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), xnil, sizeof(xclientpool)));

    xeventengine_clientpool_add(engine, pool);

    // xeventengine_cli_set(evacli);
    
    xeventengine_run(engine);

    xclientpoolrem(pool);

    return 0;
}