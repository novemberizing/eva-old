#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/client.h>

static xint64 on(xclient * client, xuint32 event, xdescriptorparam param, xint64 result)
{
    if(event == xdescriptoreventtype_in)
    {
        printf("event on => %s / %s", xdescriptoreventtype_str(event), (char *) param.p);
    }
    else if(event == xdescriptoreventtype_out)
    {
        printf("event on => %s / %s", xdescriptoreventtype_str(event), (const char *) param.c);
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

    char buffer[16] = { 0, };

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(6379);

    xclient * client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), on, sizeof(xclient));

    xclientconnect(client);

    xclientsend(client, "PING\r\n", 6);
    xclientrecv(client, buffer, 7);

    xclientclose(client);
    xclientrem(client);

    return 0;
}
