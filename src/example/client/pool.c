#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include <x/time.h>
#include <x/client/pool.h>
#include <x/event/engine.h>

xtime start = { 0, 0 };
xtime end = { 0, 0 };

xuint64 n = 0;
xuint64 total = 0;

static xint64 on(xclientpool * pool, xclient * client, xuint64 event, xdescriptorparam param, xint64 result)
{
    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            end = xtimeget();
            xtime diff = xtimediff(xaddressof(end), xaddressof(start));

            total = total + result / 7;
            n = n + result % 7;

            if(n >= 7)
            {
                total = total + n / 7;
                n = n % 7;
            }

            xclientsendf(client, xstringformatserialize ,"PING\r\n");
            if(total % 10000 == 0)
            {
                printf("event on => %s / [%ld.%09ld / %ld]\n", xdescriptoreventtype_str(event), diff.second, diff.nanosecond, total);
            }
            

            // for(xuint64 i = 0; i < 64; i++)
            // {
            //     xclientsendf(client, xstringformatserialize ,"PING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\n");
            // }
        }
    }
    else if(event == xdescriptoreventtype_out)
    {
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
        printf("event on => %s\n", xdescriptoreventtype_str(event));
        start = xtimeget();

        xclientsendf(client, xstringformatserialize ,"PING\r\n");

        // for(xuint64 i = 0; i < 64; i++)
        // {
        //     xclientsendf(client, xstringformatserialize ,"PING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\nPING\r\n");
        // }
    }
    else if(event == xdescriptoreventtype_register)
    {
        // printf("%s:%d event on => %s\n", __FILE__, __LINE__, xdescriptoreventtype_str(event));
    }
    else
    {
        // printf("event on => %s\n", xdescriptoreventtype_str(event));
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
    // addr.sin_addr.s_addr = inet_addr("192.168.0.128");
    addr.sin_port = htons(6379);
    
    xeventengine * engine = xeventengine_new();

    xclientpool * pool = xclientpoolnew(on, sizeof(xclientpool));

    for(xint32 i = 0; i < 64; i++)
    {
        xclientpooladd(pool, xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), xnil, sizeof(xclientpool)));
    }

    xeventengine_clientpool_add(engine, pool);

    // xeventengine_cli_set(evacli);
    
    xeventengine_run(engine);

    xclientpoolrem(pool, xclientrem);

    return 0;
}