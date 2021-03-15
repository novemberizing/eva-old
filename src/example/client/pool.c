#include <x/event/engine.h>
#include <x/client/pool.h>

xeventengine * engine = xnil;

int main(int argc, char ** argv)
{
    xlogpath_set("/novemberizing/");
    xlogmask_set(xlogtype_all);

    engine = xeventengine_new();

    xint32 ret = xeventengine_run(engine);


    xconsoledescriptor_term();
    xlogterm();

    return ret;
}
