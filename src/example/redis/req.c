#include <x/extension/redis.h>

int main(int argc, char ** argv)
{
    xredisreq * req = xredisreqfrom_format("set hello world");
    return 0;
}
