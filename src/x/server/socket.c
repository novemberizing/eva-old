#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../thread.h"

#include "../socket.h"
#include "../socket/processor/tcp.h"
#include "../socket/event/handler/tcp.h"

#include "../session/socket.h"
#include "socket.h"

static xint64 xserversocketobserve(xserversocket * o, xuint32 event, xdescriptorparam param, xint64 result);
static xserversocketobserver xserversocketprocessor_get(xint32 domain, xint32 type, xint32 protocol);
static xserversocketeventhandler xserversocketeventhandler_get(xint32 domain, xint32 type, xint32 protocol);

extern xserversocket * xserversocket_new(xserver * server, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xlogfunction_start("%s(%p, %d, %d, %d, %p, %u)", __func__, server, domain, type, protocol, addr, addrlen);
    xserversocket * descriptor = calloc(sizeof(xserversocket), 1);

    descriptor->rem              = xserversocket_rem;
    descriptor->handle.f         = xinvalid;
    descriptor->process          = xserversocketprocessor_get(domain, type, protocol);
    descriptor->check            = xnil;
    descriptor->on               = xserversocketobserve;
    descriptor->event.on         = xserversocketeventhandler_get(domain, type, protocol);
    descriptor->event.descriptor = descriptor;
    descriptor->domain           = domain;
    descriptor->type             = type;
    descriptor->protocol         = protocol;
    descriptor->addr             = xobjectdup(addr, addrlen);
    descriptor->addrlen          = addrlen;
    descriptor->server           = server;
    descriptor->backlog          = SOMAXCONN;

     xlogfunction_end("%s(...) => %p", __func__, descriptor);
    return descriptor;
}

extern xserversocket * xserversocket_rem(xserversocket * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);
    if(descriptor)
    {
        if(descriptor->event.queue)
        {
            xassertion(descriptor->event.queue, "");
            xeventqueue_del(xaddressof(descriptor->event));
        }
        if(descriptor->subscription)
        {
            if(descriptor->subscription->enginenode.engine)
            {
                xassertion(descriptor->subscription->enginenode.engine, "");
                xeventengine_descriptor_unregister(descriptor->subscription->enginenode.engine, (xdescriptor *) descriptor);
            }
            descriptor->subscription = xobjectrem(descriptor->subscription);
        }
        if(descriptor->handle.f > xdescriptorsystemno_max)
        {
            xassertion(descriptor->handle.f > xdescriptorsystemno_max, "");
            shutdown(descriptor->handle.f, SHUT_RDWR);
            close(descriptor->handle.f);
            descriptor->handle.f = xinvalid;
        }
        descriptor->addr = xobjectrem(descriptor->addr);
        if(descriptor->server)
        {
            descriptor->server->descriptor = xnil;
        }
        free(descriptor);
    }
    xlogfunction_end("%s(...) => %p", __func__, xnil);
    return xnil;
}

static xint64 xserversocketobserve(xserversocket * o, xuint32 event, xdescriptorparam param, xint64 result)
{
    xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, o, event, param.p, result);

    xserver * server = o->server;

    result = server->on(server, event, param, result);

    xlogfunction_end("%s(...) => %ld", __func__, result);
    return result;
}

static xserversocketobserver xserversocketprocessor_get(xint32 domain, xint32 type, xint32 protocol)
{
    if(domain == AF_INET)
    {
        if(type == SOCK_STREAM)
        {
            if(protocol == IPPROTO_TCP)
            {
                return xsocketprocessortcp_server;
            }
        }
    }
    xassertion(xtrue, "");
    return xnil;
}

static xserversocketeventhandler xserversocketeventhandler_get(xint32 domain, xint32 type, xint32 protocol)
{
    if(domain == AF_INET)
    {
        if(type == SOCK_STREAM)
        {
            if(protocol == IPPROTO_TCP)
            {
                return xserversocketeventhandler_tcp;
            }
        }
    }
    xassertion(xtrue, "");
    return xnil;
}

// static void xserversocketeventhandler_tcp(xserversocketevent * server);
// static xint64 xserversocketprocessor_tcp(xserversocket *, xuint32, void *);
// static xint64 xserversocketsubscriber_tcp(xserversocket *, xuint32, void *, xint64);
// static xint32 xserversocketcheck_tcp(xserversocket *, xuint32);

// static xint64 xserversocketprocessor_tcp_open(xserversocket * descriptor, void * data);
// static xint64 xserversocketprocessor_tcp_in(xserversocket * descriptor, void * data);
// static xint64 xserversocketprocessor_tcp_close(xserversocket * descriptor, void * data);

// extern xserversocket * xserversocket_new(xserver * server, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
// {
//     xlogfunction_start("%s(%p, %d, %d, %d, %p, %u)", __func__, server, domain, type, protocol, addr, addrlen);
//     xserversocket * descriptor = calloc(sizeof(xserversocket), 1);

//     descriptor->rem              = xserversocket_rem;
//     descriptor->handle.f         = xinvalid;
//     descriptor->process          = xserversocketprocessor_tcp;
//     descriptor->check            = xserversocketcheck_tcp;
//     descriptor->on               = xserversocketsubscriber_tcp;
//     descriptor->event.on         = xserversocketeventhandler_tcp;
//     descriptor->event.descriptor = descriptor;
//     descriptor->domain           = domain;
//     descriptor->type             = type;
//     descriptor->protocol         = protocol;
//     descriptor->addr             = xobjectdup(addr, addrlen);
//     descriptor->addrlen          = addrlen;
//     descriptor->server           = server;
//     descriptor->backlog          = SOMAXCONN;

//     xlogfunction_end("%s(...) => %p", __func__, descriptor);
//     return descriptor;
// }

// extern xint32 xserversocketcheck_open(xserversocket * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);

//     xassertion(descriptor == xnil, "");
//     if(descriptor->handle.f < 0)
//     {
//         xlogfunction_end("%s(...) => %d", __func__, xfalse);
//         return xfalse;
//     }
//     if((descriptor->status & xserversocketstatus_open) == xserversocketstatus_void)
//     {
//         xlogfunction_end("%s(...) => %d", __func__, xfalse);
//         return xfalse;
//     }

//     xlogfunction_end("%s(...) => %d", __func__, xtrue);
//     return xtrue;
// }

// extern xint32 xserversocketcheck_close(xserversocket * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);
//     xint32 ret = (descriptor->status & (xserversocketstatus_exception | xserversocketstatus_close | xserversocketstatus_rem));

//     xlogfunction_end("%s(...) => %d", __func__, ret);
//     return ret;
// }

// extern xint32 xserversocketcheck_rem(xserversocket * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);

//     xassertion(descriptor == xnil, "");

//     if(descriptor->subscription)
//     {
//         xlogfunction_end("%s(...) => %d", __func__, xfalse);
//         return xfalse;
//     }
//     if(descriptor->handle.f >= 0)
//     {
//         xlogfunction_end("%s(...) => %d", __func__, xfalse);
//         return xfalse;
//     }
//     if(descriptor->event.queue || descriptor->event.next || descriptor->event.prev)
//     {
//         xlogfunction_end("%s(...) => %d", __func__, xfalse);
//         return xfalse;
//     }
//     xlogfunction_end("%s(...) => %d", __func__, xtrue);
//     return xtrue;
// }


// extern xserversocket * xserversocket_rem(xserversocket * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);

//     xassertion(xserversocketcheck_rem(descriptor) == xfalse, "");

//     descriptor->sync = xsyncrem(descriptor->sync);
//     descriptor->addr = xobjectrem(descriptor->addr);

//     free(descriptor);
    
//     xlogfunction_end("%s(...) => %p", __func__, xnil);
//     return xnil;
// }

// extern void xserversocketbacklog_set(xserversocket * descriptor, xint32 backlog)
// {
//     xlogfunction_start("%s(%p, %d)", __func__, descriptor, backlog);
//     xassertion(descriptor == xnil, "");

//     descriptor->backlog = backlog;

//     xlogfunction_end("%s(...)", __func__);
// }

// static void xserversocketeventhandler_tcp(xserversocketevent * event)
// {
//     xlogfunction_start("%s(%p)", __func__, event);

//     xdescriptorevent_processor_on((xdescriptor *) event->descriptor);

//     xlogfunction_end("%s(...)");
// }

// static xint64 xserversocketprocessor_tcp(xserversocket * descriptor, xuint32 event, void * data)
// {
//     xlogfunction_start("%s(%p, %u, %p)", __func__, descriptor, event, data);
//     xint64 ret = xsuccess;
//     switch(event)
//     {
//         case xserversocketeventtype_open:   ret = xserversocketprocessor_tcp_open(descriptor, data);            break;
//         case xserversocketeventtype_in:     ret = xserversocketprocessor_tcp_in(descriptor, data);              break;
//         case xserversocketeventtype_out:    ret = xsuccess;                                                     break;
//         case xserversocketeventtype_close:  ret = xserversocketprocessor_tcp_close(descriptor, data);           break;
//         default:                            xassertion(xtrue, "implement this - check event 0x%08x", event);    break;
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// static xint64 xserversocketprocessor_tcp_open(xserversocket * descriptor, void * data)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

//     if(xserversocketcheck_close(descriptor) == xfalse)
//     {
//         if(xserversocketcheck_open(descriptor) == xfalse)
//         {
//             if((descriptor->status & xsocketstatus_create) == xsocketstatus_void)
//             {
//                 if(xsocketcreate((xsocket *) descriptor) != xsuccess)
//                 {
//                     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//                     return xfail;
//                 }
//             }
//             xdescriptornonblock_set((xdescriptor *) descriptor, xtrue);
//             xsocketresuseaddr_set((xsocket *) descriptor, xtrue);

//             if((descriptor->status & xsocketstatus_bind) == xsocketstatus_void)
//             {
//                 if(xsocketbind((xsocket *) descriptor, descriptor->addr, descriptor->addrlen) != xsuccess)
//                 {
//                     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//                     return xfail;
//                 }
//             }
//             if((descriptor->status & xsocketstatus_listen) == xsocketstatus_void)
//             {
//                 if(xsocketlisten((xsocket *) descriptor, descriptor->backlog) != xsuccess)
//                 {
//                     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//                     return xfail;
//                 }
//             }
//             descriptor->status |= (xsocketstatus_open | xsocketstatus_out);
//         }
//         descriptor->status |= (xsocketstatus_out | xsocketstatus_out);
//         xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
//         return xsuccess;
//     }
//     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//     return xfail;
// }

// static xint64 xserversocketprocessor_tcp_in(xserversocket * descriptor, void * data)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);
    
//     xassertion(descriptor == xnil, "");
//     xassertion(descriptor->subscription == xnil, "");
//     xassertion(descriptor->server == xnil, "");

//     xserver * server = descriptor->server;
//     xserversocketeventsubscription * subscription = descriptor->subscription;
//     xeventengine * engine = subscription->enginenode.engine;

//     xassertion(engine == xnil, "");
    
//     int f = accept(descriptor->handle.f, xnil, 0);

//     if(f >= 0)
//     {
//         xsession * session = server->session.create(descriptor->domain, descriptor->type, descriptor->protocol);
//         if(session)
//         {
//             session->server = server;

//             xsessionsocket * sessionsocket = session->descriptor;

//             sessionsocket->session = session;
//             sessionsocket->handle.f = f;
//             sessionsocket->status = (xsessionsocketstatus_open | xsessionsocketstatus_bind | xsessionsocketstatus_out);
//             if(xeventengine_session_register(engine, session) == xnil)
//             {
//                 xassertion(xtrue, "");
//                 xlogfunction_end("%s(...) => %ld", __func__, xfail);
//                 return xfail;
//             }
//             xassertion((sessionsocket->status & xsessionsocketstatus_register) == xsessionsocketstatus_void, "");
//             sessionsocket->on(sessionsocket, xsessionsocketstatus_open, xnil, xsuccess);
//         }
//         else
//         {
//             xcheck(xtrue, "shutdown apply");
//             if(close(f) != xsuccess)
//             {
//                 xassertion(xtrue, "");
//             }
//             // xassertion(session == xnil, "");
//         }
//         xlogfunction_end("%s(...) => %ld", __func__, 1);
//         // 1 is or not 1 check this
//         // 1 이란 의미는 의미 있는 데이터가 처리되었다는 의미이다.
//         // 하지만, 성공(0) 을 리턴하더라도 소켓 생성기에 상태 업데이터가 일어나지 않는다면
//         // 이곳의 좋은 리턴 값은 SUCCESS 일 것이다.
//         return 1;
//     }
//     else
//     {
//         if(errno != EAGAIN)
//         {
//             xcheck(xtrue, "accept fail %d", errno);
//             xassertion(xtrue, "implement this");
//         }
//         // 같은 원리로 0 혹은 1을 리턴하는 것이 올바른지 확인하자.
//         xlogfunction_end("%s(...) => %ld", __func__, 0);
//         return 0;
//         // 서버를 체크하도록 하자.
        
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//     return xfail;
// }

// static xint64 xserversocketprocessor_tcp_close(xserversocket * descriptor, void * data)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

//     xint64 ret = xdescriptorclose((xdescriptor *) descriptor);

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// static xint64 xserversocketsubscriber_tcp(xserversocket * descriptor, xuint32 event, void * data, xint64 result)
// {
//     xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, descriptor, event, data, result);
//     xserver * server = descriptor->server;
//     if(descriptor->exception.number)
//     {
//         xcheck(xtrue, "exception errno => %d", descriptor->exception.number);
//     }

//     xcheck(xtrue, "event: %s, result: %ld", xserversocketeventtype_str(event), result);

//     xint64 ret = server->on(server, event, data, result);

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// static xint32 xserversocketcheck_tcp(xserversocket * descriptor, xuint32 event)
// {
//     xlogfunction_start("%s(%p, %u)", __func__, descriptor, event);
//     xassertion(xtrue, "implement this");

//     xlogfunction_end("%s(...)", __func__);
// }

// extern const char * xserversocketeventtype_str(xuint32 event)
// {
//     switch(event)
//     {
//         case xsocketeventtype_open:         return "open";
//         case xsocketeventtype_in:           return "in";
//         case xsocketeventtype_out:          return "out";
//         case xsocketeventtype_close:        return "close";
//         case xsocketeventtype_exception:    return "exception";
//         case xsocketeventtype_rem:          return "rem";
//         case xsocketeventtype_register:     return "register";
//         case xsocketeventtype_create:       return "create";
//         case xsocketeventtype_bind:         return "bind";
//         case xsocketeventtype_connect:      return "connect";
//         case xsocketeventtype_connecting:   return "connecting";
//         case xsocketeventtype_listen:       return "listen";
//         case xsocketeventtype_offin:        return "off in";
//         case xsocketeventtype_offout:       return "off out";
//         case xsocketeventtype_offall:       return "off all";
//         default:                            return "unknown";
//     }
// }
