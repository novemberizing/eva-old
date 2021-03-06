#include <x/event/engine.h>

int main(int argc, char ** argv)
{
    xeventengine * engine = xeventengine_new();
    return xeventengine_run(engine);
}
