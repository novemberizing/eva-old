#include <x/eva.h>
#include <x/eva/server/echo.h>

int main(int argc, char ** argv)
{
    xlogconsole_set(xtrue);
    xevaconfigloginit("/novemberizing", xlogtype_all);

    xevaserveradd(xtransmissioncontrolprotocol, 7, xevaechoserver_get(xtransmissioncontrolprotocol));

    return xevarun(argc, argv);
}
