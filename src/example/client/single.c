#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/client.h>

static xint64 on(xclient * client, xuint32 event, xdescriptorparam param, xint64 result)
{
    if(event == xsocketeventtype_in)
    {
        printf("in\n");
    }
    else if(event == xsocketeventtype_out)
    {
        printf("out\n");
    }
    else
    {
        printf("event => %s\n", xdescriptoreventtype_str(event));
    }
    return result;
}

int main(int argc, char ** argv)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(6379);

    xclient * client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), on, sizeof(xclient));

    xclientconnect(client);
    xclientsendf(client, xstringformatserialize, "PING\r\n");

    // xclientreq(client, xstringformatserialize, "PING\r\n");

    xclientrem(client);
    return 0;
}