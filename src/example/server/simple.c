#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include <x/log.h>
#include <x/server.h>
#include <x/event/engine.h>

static xint64 on(xsession * session, xuint32 event, xdescriptorparam param, xint64 result)
{
    printf("event => %s\n", xdescriptoreventtype_str(event));

    if(event == xdescriptoreventtype_in)
    {
        if(result > 0)
        {
            xstream * in = xsessionstreamin_get(session);
            xstream * out = xsessionstreamout_get(session);

            printf("len => %ld\n", xstreamlen(in));
            xstreampush(out, xstreamfront(in), xstreamlen(in));
            // printf("%s\n", xstreamfront(session->descriptor->))
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

    xeventengine_server_register(engine, server);

    xint32 ret = xeventengine_run(engine);

    return 0;
}