#include <stdio.h>

#include <x/thread.h>
#include <x/console.h>
#include <x/event/engine.h>

static xint64 xconsolesubscriber_example(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 value);

int main(int argc, char ** argv)
{
    xconsolesubscriber_set(xconsolesubscriber_example);

    xeventengine * engine = xeventengine_new();

    xeventengine_descriptor_register(engine, xconsoledescriptorout_get());
    xeventengine_descriptor_register(engine, xconsoledescriptorin_get());
    
    return xeventengine_run(engine);
}

static xint64 xconsolesubscriber_example(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 value)
{
    return value;
}
