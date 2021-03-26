#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <netinet/in.h>

#include "../thread.h"
#include "../socket/handle.h"

#include "socket.h"
#include "socket/status.h"
#include "socket/event.h"
#include "socket/event/type.h"
#include "socket/event/avail.h"
#include "socket/event/process/tcp.h"

static xclientsocketprocessor xclientsocketprocessor_get(xint32 domain, xint32 type, xint32 protocol);
static xint64 xclientsocketon(xclientsocket * o, xuint32 event, xdescriptorparam param, xint64 result);
static void xclientsocketeventon(xclientsocketevent * event);

extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xclientsocket * o = (xclientsocket *) calloc(sizeof(xclientsocket), 1);

    o->rem = xclientsocket_rem;
    // o->subscription = xnil;
    // o->sync = xnil;
    // o->mask = xdescriptormask_void;
    // o->status = xsocketstatus_void;
    o->handle.f = xinvalid;
    o->process = xclientsocketprocessor_get(domain, type, protocol);
    // o->check = xnil;
    o->on = xclientsocketon;
    o->event.descriptor = o;
    o->event.on = xclientsocketeventon;
    o->domain = domain;
    o->type = type;
    o->protocol = protocol;
    o->addr = xobjectdup(addr, addrlen);
    o->addrlen = addrlen;
    // o->stream.in = xnil;
    // o->stream.out = xnil;
    o->client = client;

    return o;
}

extern xclientsocket * xclientsocket_rem(xclientsocket * o)
{
    if(o)
    {
        if(o->subscription && o->subscription->generatornode.generator)
        {
            xeventengine_descriptor_unregister(o->subscription->enginenode.engine, (xdescriptor *) o->subscription->descriptor);
        }
        
        o->subscription = xobjectrem(o->subscription);
        o->handle.f = xsockethandle_shutdown(o->handle.f);
        o->stream.in = xstreamrem(o->stream.in);
        o->stream.out = xstreamrem(o->stream.out);
        o->sync = xsyncrem(o->sync);
        o->addr = xobjectrem(o->addr);

        free(o);
    }
    return xnil;
}

extern xint64 xclientsocketclear(xclientsocket * o)
{
    xassertion(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse, "");

    o->stream.in = xstreamrem(o->stream.in);
    o->stream.out = xstreamrem(o->stream.out);

    return xsuccess;
}

extern xint64 xclientsocketconnect(xclientsocket * o, void * addr, xuint32 addrlen)
{
    xint64 ret = xfail;
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f >= 0 && (o->status & xsocketstatus_create))
        {
            if(o->stream.in == xnil)
            {
                o->stream.in = xstreamnew(xstreamtype_buffer);
            }

            if(o->stream.out == xnil)
            {
                o->stream.out = xstreamnew(xstreamtype_buffer);
            }

            if((o->status & xdescriptorstatus_connect) == xdescriptorstatus_void)
            {
                xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) o->subscription;
                xdescriptoreventgenerator * generator = subscription ? subscription->generatornode.generator : xnil;

                if(o->status & xdescriptorstatus_connecting)
                {
                    int code = xsocketerror((xsocket *) o);
                    if(code == xsuccess)
                    {
                        o->status &= (~xdescriptorstatus_connecting);
                        o->status |= (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_out);
                        if((ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess)) == xsuccess)
                        {
                            if(o->stream.in == xnil)
                            {
                                o->stream.in = xstreamnew(xstreamtype_buffer);
                            }
                            if(o->stream.out == xnil)
                            {
                                o->stream.out = xstreamnew(xstreamtype_buffer);
                            }
                        }
                    }
                    else
                    {
                        if((o->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
                        {
                            if(code != EAGAIN && errno != EINPROGRESS)
                            {
                                xdescriptorexception((xdescriptor *) o, connect, code, xexceptiontype_sys, "");
                            }
                            else
                            {
                                ret = xsuccess;
                            }
                        }
                    }
                }
                else
                {

                    if(generator || (o->mask & xdescriptormask_nonblock))
                    {
                        xdescriptornonblock((xdescriptor *) o, xtrue);
                    }

                    if((ret = connect(o->handle.f, addr, addrlen)) == xsuccess)
                    {
                        o->status |= (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_out);

                        if((ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess)) == xsuccess)
                        {
                            if(o->stream.in == xnil)
                            {
                                o->stream.in = xstreamnew(xstreamtype_buffer);
                            }
                            if(o->stream.out == xnil)
                            {
                                o->stream.out = xstreamnew(xstreamtype_buffer);
                            }
                        }
                    }
                    else
                    {
                        if(errno == EAGAIN || errno == EINPROGRESS)
                        {
                            o->status |= xdescriptorstatus_connecting;
                            ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_opening, xdescriptorparamgen(xnil), xsuccess);
                        }
                        else
                        {
                            xdescriptorexception((xdescriptor *) o, connect, errno, xexceptiontype_sys, "");
                        }
                    }
                }

                /**
                 * 기본 이벤트 등록은 VOID 에서 이루어지면 어떻게 해야할까? 
                 * TODO: 리팩터링 대상이다. 이벤트 엔진에 등록은 I/O 가 끝난 후에 이루어져야 한다.
                 * 그렇기 때문에, 오픈과 등록은 별개로 나뉘어야 한다.
                 */
                if(o->status & (xdescriptorstatus_connecting | xdescriptorstatus_connect))
                {
                    if(generator)
                    {
                        if(subscription->generatornode.list == xnil)
                        {
                            xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
                        }

                        if((o->status & xdescriptorstatus_register) == xdescriptorstatus_void)
                        {
                            xdescriptoreventgenerator_descriptor_register(generator, (xdescriptor *) o);
                        }
                        else
                        {
                            // xassertion(o->status & xdescriptorstatus_register, "");
                        }
                    }
                }
            }
            else
            {
                ret = xsuccess;
            }
        }
    }
    return ret;
}

static xclientsocketprocessor xclientsocketprocessor_get(xint32 domain, xint32 type, xint32 protocol)
{
    if(domain == AF_INET)
    {
        if(type == SOCK_STREAM)
        {
            if(protocol == IPPROTO_TCP)
            {
                return xclientsocketprocess_tcp;
            }
        }
    }
    xassertion(xtrue, "");
    return xnil;
}

static xint64 xclientsocketon(xclientsocket * o, xuint32 event, xdescriptorparam param, xint64 result)
{
    xclient * client = o->client;

    return client->on(client, event, param, result);
}

static void xclientsocketeventon(xclientsocketevent * event)
{
    xclientsocket * o = event->descriptor;

    o->process(o, xsocketeventtype_void);
}

static xint64 xserversocketon(xserversocket * o, xuint32 event, xdescriptorparam param, xint64 result)
{
    return result;
}
