#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include "thread.h"
#include "eva.h"

#include <x/map.h>
#include <x/server.h>
#include <x/server/socket.h>
#include <x/console.h>
#include <x/event/engine.h>
#include <x/eva/config.h>

struct xeva
{
    xeventengine * engine;
    xevaconfig config;
    xmap * servers;
};

static void xevaeventengine_cancel(xeventengine * engine)
{
    printf("engine cancel\n");
}

static void xevaserverrem(xval * key, xval * value)
{
    xserver * server = (xserver *) value->p;

    if (server->descriptor->subscription)
    {
        xassertion(server->descriptor->subscription->enginenode.engine, "");
        free(server->descriptor->subscription);
        server->descriptor->subscription = xnil;
    }
    if(server->descriptor->handle.f >= 0)
    {
        shutdown(server->descriptor->handle.f, SHUT_RDWR);
        close(server->descriptor->handle.f);
        server->descriptor->handle.f = xinvalid;
    }
    server->descriptor->status = xdescriptorstatus_void;
    
    xserverrem(server);
}

static struct xeva __singleton = {
    xnil,
    { 0, },
    xnil
};

static void xevaconfigterm(void)
{
    __singleton.config.log.path = xobjectrem(__singleton.config.log.path);
}

extern void xevaserveradd(xint32 protocol, xint32 port, xserver * server)
{
    xuint64 key = xunsigned64from_integer32(protocol, port);
    if(__singleton.servers == xnil)
    {
        __singleton.servers = xmapnew(xnil);
    }
    xmapnode * prev = xmapadd(__singleton.servers, xvalunsigned64(key), xvalobject(server), xnil);
    if(prev)
    {
        xval value = xmapnodevalue(prev);
        if(value.p != server)
        {
            xserverrem((xserver *) value.p);
        }
    }
}

extern xint32 xevarun(int argc, char ** argv)
{
    // xassertion(__singleton.engine, "");

    if(__singleton.engine == xnil)
    {
        // 두개의 함수는 모두 설정이 되어 있지 않으면 설정을 하자.
        // INITIALIZE 함수는 함수가 초기화되어 있지 않으면 초기화 하도록 하자.
        xconsoleinit(xevacli);

        xevaconfigloginit("/novemberizing", xlogtype_all);
        

        xlogfunction_start("%s()", __func__);

        // 0. CREATE EVENT ENGINE
        __singleton.engine = xeventengine_new();
        if(__singleton.servers == xnil)
        {
            __singleton.servers = xmapnew(xnil);
        }
        
        // 1. REGISTER CONSOLE IN/OUT, SERVERS, CLIENT, CLIENT POOL
        xeventengine_descriptor_register(__singleton.engine, xconsoledescriptorin_get());
        xeventengine_descriptor_register(__singleton.engine, xconsoledescriptorout_get());

        for(xmapnode * node = xmapbegin(__singleton.servers); node != xnil; node = xmapnode_next(node))
        {
            xeventengine_server_register(__singleton.engine, (xserver *) xvalobjectget(xmapnodevalue(node)));
            // printf("node => \n", node)
        }

        // 2. EVENT ENGINE RUN
        xint32 ret = xeventengine_run(__singleton.engine);
        __singleton.engine = xnil;
        if(__singleton.servers)
        {
            __singleton.servers = xmaprem(__singleton.servers, xevaserverrem);
        }

        xlogfunction_end("%s()", __func__, ret);

        // Z. TERMINAITION
        xconsoleterm();
        xevaconfigterm();

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

        xlogpath_set(__singleton.config.log.path);
        xlogmask_set(__singleton.config.log.types);
    }
}

extern void xevaquit(void)
{
    xeventengine_cancel(__singleton.engine, xevaeventengine_cancel);
}
