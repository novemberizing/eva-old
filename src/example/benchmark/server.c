#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include <x/log.h>
#include <x/server.h>
#include <x/event/engine.h>
#include <x/eva/cli.h>
#include <x/time.h>

xtime start = { 0, 0 };
xtime end = { 0, 0 };

xuint64 count = 0;

static xint64 on(xsession * session, xuint32 event, xdescriptorparam param, xint64 result)
{
    // printf("event => %s\n", xdescriptoreventtype_str(event));

    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            if(count == 0)
            {
                start = xtimeget();
            }
            count++;
            if(count % 10000 == 0)
            {
                end = xtimeget();
                xtime diff = xtimediff(xaddressof(end), xaddressof(start));
                xconsoleout("event on => %s / [%ld.%09ld / %ld]\n", xdescriptoreventtype_str(event), diff.second, diff.nanosecond, count);
            }
            
            xstream * in = xsessionstreamin_get(session);
            xstream * out = xsessionstreamout_get(session);

            xstreampush(out, xstreamfront(in), xstreamlen(in));
        }
    }
    
    return result;
}

int main(int argc, char ** argv)
{
    xloginit(xnil, xlogtype_assertion, xtrue);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(3371);

    xeventengine * engine = xeventengine_new();

    xserver * server = xservernew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), on, sizeof(xserver));

    xeventengine_cli(engine, xevacli);
    xeventengine_server_register(engine, server);

    xint32 ret = xeventengine_run(engine);

    server = xserverrem(server);

    xconsoleterm();
    xlogterm();

    return 0;
}
