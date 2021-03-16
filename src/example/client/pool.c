#include <x/event/engine.h>
#include <x/client/pool.h>

int main(int argc, char ** argv)
{
    xeventengine * engine = xeventengine_new();

    xint32 ret = xeventengine_run(engine);

    return ret;
}


