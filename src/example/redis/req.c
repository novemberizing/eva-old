#include <x/extension/redis.h>

int main(int argc, char ** argv)
{
    xloginit(xnil, xlogtype_assertion, xtrue);

    xredisreq * req = xnil;
    
    req = xredisreqrem(xredisreqfrom_format("set hello world"));
    req = xredisreqrem(xredisreqfrom_format("   set hello world"));
    req = xredisreqrem(xredisreqfrom_format("set %s %s", "hello", "world"));
    req = xredisreqrem(xredisreqfrom_format("set keylen_%d %s", 1024, "world"));
    req = xredisreqrem(xredisreqfrom_format("set \"keylen %d\" %s", 1024, "world"));
    req = xredisreqrem(xredisreqfrom_format("set 'keylen %d' %s", 1024, "world"));

    req = xredisreqrem(xredisreqfrom_format("set \"key\\\"len %d\" %s", 1024, "world"));
    req = xredisreqrem(xredisreqfrom_format("set 'key\\'len %d' %s", 1024, "world"));
    return 0;
}
