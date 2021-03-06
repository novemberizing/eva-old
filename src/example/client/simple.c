#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/client.h>

int main(int argc, char ** argv)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(3372);

    xclient * client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, &addr, sizeof(addr), xnil, sizeof(xclient));

    if(xclientconnect(client) == xsuccess)
    {
        if(xclientsend(client, "hello world\n", 12) == 12)
        {
            char buffer[64];
            buffer[0] = 0;
            if(xclientread(client, buffer, 12) == 12)
            {
                buffer[12] = 0;
                printf("%s\n", buffer);
                xclientclose(client);
                xclientrem(client);
                return 0;
            }
        }
    }
    
    return -1;
}
