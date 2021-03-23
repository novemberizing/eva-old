#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/client/pool.h>
#include <x/event/engine.h>

int main(int argc, char ** argv)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(6379);
    
    xeventengine * engine = xeventengine_new();

    xclientpool * pool = xclientpoolnew(xnil, sizeof(xclientpool));

    xclientpooladd(pool, xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), xnil, sizeof(xclientpool)));

    xeventengine_clientpool_register(engine, pool);

    xclientpoolrem(pool);

    return 0;
}