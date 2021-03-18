#include <x/eva.h>
#include <x/eva/extension/echo.h>

int main(int argc, char ** argv)
{
    xlogconsole_set(xtrue);
    xevaconfigloginit("/novemberizing", xlogtype_assertion);

    xevaserveradd(xtransmissioncontrolprotocol, 7, xevaechoserver_get(xtransmissioncontrolprotocol));

    xevaclientadd(xevaechoclient_gen(xtransmissioncontrolprotocol, "127.0.0.1", xstreamgen_str("hello world")));

    return xevarun(argc, argv);
}
