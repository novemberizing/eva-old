#include <x/event/engine.h>

xeventengine * engine = xnil;

int main(int argc, char ** argv)
{
    engine = xeventengine_new();

    xclientpool * clients = xnil;

    xeventengine_clientpool_register(engine, clients);

    xint32 ret = xeventengine_run(engine);

    return ret;
}