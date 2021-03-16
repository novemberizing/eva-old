#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "eva.h"

#include <x/console.h>
#include <x/event/engine.h>
#include <x/eva/config.h>

struct xeva
{
    xeventengine * engine;
    xevaconfig config;

    // tree ???????????????????????????????
};

static void xevaeventengine_cancel(xeventengine * engine)
{
    printf("engine cancel\n");
}

static struct xeva __singleton = {
    xnil,
};

extern xint32 xevarun(int argc, char ** argv)
{
    xassertion(__singleton.engine, "");

    if(__singleton.engine == xnil)
    {
        // 두개의 함수는 모두 설정이 되어 있지 않으면 설정을 하자.
        // INITIALIZE 함수는 함수가 초기화되어 있지 않으면 초기화 하도록 하자.
        xconsoleinit(xevacli);
        xevaconfigloginit("/novemberizing", xlogtype_all);

        xlogfunction_start("%s()", __func__);

        // 0. CREATE EVENT ENGINE
        __singleton.engine = xeventengine_new();
        
        // 1. REGISTER CONSOLE IN/OUT, SERVERS, CLIENT, CLIENT POOL
        xeventengine_descriptor_register(__singleton.engine, xconsoledescriptorin_get());
        xeventengine_descriptor_register(__singleton.engine, xconsoledescriptorout_get());

        // 2. EVENT ENGINE RUN
        xint32 ret = xeventengine_run(__singleton.engine);

        xlogfunction_end("%s()", __func__, ret);

        // Z. TERMINAITION
        xconsoleterm();
        xlogterm();

        return ret;
    }

    return xfail;
}

extern void xevaconfiglogpath_set(const char * path)
{
    if(__singleton.config.log.path)
    {
        free(__singleton.config.log.path);
    }
    __singleton.config.log.path = xobjectdup(path, strlen(path));   // check security
}

extern void xevaconfiglogtypes_set(xuint32 types)
{
    __singleton.config.log.types = types;
}

extern void xevaconfiglogtypes_add(xuint32 type)
{
    __singleton.config.log.types |= type;
}

extern void xevaconfiglogtypes_del(xuint32 type)
{
    __singleton.config.log.types &= (~type);
}

extern void xevaconfigloginit(char * path, xuint32 types)
{
    if(__singleton.config.log.path == xnil)
    {
        __singleton.config.log.path  = xobjectdup(path, strlen(path));   // check strnlen
        __singleton.config.log.types = types;
    }
}

extern void xevaquit(void)
{
    xeventengine_cancel(__singleton.engine, xevaeventengine_cancel);
}
