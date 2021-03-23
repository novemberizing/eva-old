#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <netinet/in.h>

#include "../thread.h"

#include "socket.h"
#include "socket/status.h"
#include "socket/event/type.h"

extern xint64 xclientsocketconnect(xclientsocket * o, void * addr, xuint32 addrlen)
{
    xint64 ret = xfail;
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->handle.f >= 0 && (o->status & xsocketstatus_create))
        {
            if((o->status & (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_connecting)) == xdescriptorstatus_void)
            {
                if((o->subscription && o->subscription->enginenode.engine) || (o->mask & xdescriptormask_nonblock))
                {
                    xdescriptornonblock((xdescriptor *) o, xtrue);
                }

                if((o->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
                {
                    if((ret = connect(o->handle.f, addr, addrlen)) == xsuccess)
                    {
                        o->status |= (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_out);
                        ret = xdescriptoron((xdescriptor *) o, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess);
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
            }
            else
            {
                ret = xsuccess;
            }
        }
    }
    return ret;
}

// static xint64 xclientsocketobserve(xclientsocket * o, xuint32 event, void * param, xint64 result);
// static void xclientsocketeventhandler_tcp(xclientsocketevent * event);

// static xclientsocketprocessor xclientsocketprocessor_get(xint32 domain, xint32 type, xint32 protocol);
// static xclientsocketeventhandler xclientsocketeventhandler_get(xint32 domain, xint32 type, xint32 protocol);

// static xint64 xclientsocketprocessor_tcp(xclientsocket * o, xuint32 event, void * param);

// extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
// {
//     xlogfunction_start("%s(%p, %d, %d, %d, %p, %u)", client, domain, type, protocol, addr, addrlen);
//     xclientsocket * o = (xclientsocket *) calloc(sizeof(xclientsocket), 1);

//     o->rem              = xclientsocket_rem;
//     o->handle.f         = xinvalid;
//     o->process          = xclientsocketprocessor_get(domain, type, protocol);
//     o->check            = xclientsocketcheck;
//     o->on               = xclientsocketobserve;
//     o->event.descriptor = o;
//     o->event.on         = xclientsocketeventhandler_get(domain, type, protocol);
//     o->domain           = domain;
//     o->type             = type;
//     o->protocol         = protocol;
//     o->addr             = xobjectdup(addr, addrlen);
//     o->addrlen          = addrlen;
//     o->client           = client;

//     xlogfunction_end("%s(...) => %p", __func__, o);
//     return o;
// }

// static xclientsocketprocessor xclientsocketprocessor_get(xint32 domain, xint32 type, xint32 protocol)
// {
//     if(domain == AF_INET)
//     {
//         if(type == SOCK_STREAM)
//         {
//             if(protocol == IPPROTO_TCP)
//             {
//                 return xclientsocketprocessor_tcp;
//             }
//         }
//     }
    
//     xassertion(xtrue, "");  // 아직 미구현된

//     return xnil;
// }

// static xclientsocketeventhandler xclientsocketeventhandler_get(xint32 domain, xint32 type, xint32 protocol)
// {
//     if(domain == AF_INET)
//     {
//         if(type == SOCK_STREAM)
//         {
//             if(protocol == IPPROTO_TCP)
//             {
//                 return xclientsocketeventhandler_tcp;
//             }
//         }
//     }
    
//     xassertion(xtrue, "");  // 아직 미구현된

//     return xnil;
// }

// static xint64 xclientsocketprocessor_tcp(xclientsocket * o, xuint32 event, void * param)
// {
//     xint64 ret = xfail;
//     switch(event)
//     {
//         case xsocketeventtype_connect:      ret = xsocketprocessortcp_connect(o, param);    break;
//         case xsocketeventtype_in:           ret = xsocketprocessortcp_in(o, param);         break;
//         case xsocketeventtype_out:          ret = xsocketprocessortcp_out(o, param);        break;
//         case xsocketeventtype_close:        ret = xsocketprocessortcp_close(o, param);      break;
//         case xsocketeventtype_exception:    ret = xsocketprocessortcp_exception(o, param);  break;
//         case xsocketeventtype_rem:          ret = xsocketprocessortcp_rem(o, param);        break;
//         case xsocketeventtype_register:     ret = xsocketprocessortcp_register(o, param);   break;
//         case xsocketeventtype_flush:        ret = xsocketprocessortcp_flush(o, param);      break;
//         case xsocketeventtype_readoff:      ret = xsocketprocessortcp_readoff(o, param);    break;
//         case xsocketeventtype_writeoff:     ret = xsocketprocessortcp_writeoff(o, param);   break;
//         case xsocketeventtype_connecting:   ret = xsocketprocessortcp_connecting(o, param); break;
//         case xsocketeventtype_create:       ret = xsocketprocessortcp_create(o, param);     break;
//         case xsocketeventtype_bind:         ret = xsocketprocessortcp_bind(o, param);       break;
//         case xsocketeventtype_alloff:       ret = xsocketprocessortcp_alloff(o, param);     break;
//         case xsocketeventtype_void:         ret = xsocketprocessortcp_void(o, param);       break;
//         default:                            xassertion(xtrue, "");                          break;
//     }
//     return ret;
// }

// static void xclientsocketeventhandler_tcp(xclientsocketevent * event)
// {
//     xlogfunction_start("%s(%p)", __func__, event);

//     xdescriptorevent_process((xdescriptor *) event->descriptor);

//     xlogfunction_end("%s(...)", __func__);
// }

// static xint64 xclientsocketobserve(xclientsocket * o, xuint32 event, void * param, xint64 result)
// {
//     xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, o, event, param, result);

//     xclient * client = o->client;

//     xint64 ret = client->on(client, event, param, result);

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// // static xint64 xclientsocketprocessor_tcp(xclientsocket * o, xuint32 event, void * parameter);
// // static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * parameter, xint64 result);
// // static xint32 xclientsocketcheck_tcp(xclientsocket * o, xuint32 event);
// // static void xclientsocketeventhandler_tcp(xclientsocketevent * event);

// // extern xint32 xclientsocketcheck(xclientsocket * o, xuint32 status)
// // {
// //     xlogfunction_start("%s(%p, %u)", __func__, o, status);
// //     xint32 ret = xfalse;
    
// //     xassertion(xtrue, "implement this");

// //     xlogfunction_end("%s(...) => %d", __func__, ret);
// //     return ret;
// // }

// // extern xint32 xclientsocketcheck_close(xclientsocket * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);
// //     xint32 ret = (descriptor->status & (xclientsocketstatus_exception | xclientsocketstatus_close | xclientsocketstatus_rem));

// //     xlogfunction_end("%s(...) => %d", __func__, ret);
// //     return ret;
// // }

// // extern xint32 xclientsocketcheck_rem(xclientsocket * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor == xnil, "");

// //     if(descriptor->subscription)
// //     {
// //         xlogfunction_end("%s(...) => %d", __func__, xfalse);
// //         return xfalse;
// //     }
// //     if(descriptor->handle.f >= 0)
// //     {
// //         xlogfunction_end("%s(...) => %d", __func__, xfalse);
// //         return xfalse;
// //     }
// //     if(descriptor->event.queue || descriptor->event.next || descriptor->event.prev)
// //     {
// //         xlogfunction_end("%s(...) => %d", __func__, xfalse);
// //         return xfalse;
// //     }
// //     xlogfunction_end("%s(...) => %d", __func__, xtrue);
// //     return xtrue;
// // }



// // extern xclientsocket * xclientsocket_rem(xclientsocket * o)
// // {
// //     xlogfunction_start("%s(%p)", __func__, o);
// //     xassertion(o == xnil, "");
// //     xassertion(o->subscription == xnil, "");
// //     if(o->handle.f >= 0)
// //     {
// //         // TODO: STDIN, OUT, ERR 를 종료시키지 않는다.
// //         close(o->handle.f);
// //         o->handle.f = xinvalid;
// //     }
// //     o->sync = xsyncrem(o->sync);
// //     o->addr = xobjectrem(o->addr);
// //     o->stream.in = xstreamrem(o->stream.in);
// //     o->stream.out = xstreamrem(o->stream.out);

// //     xlogfunction_end("%s(...) => %p", __func__, xnil);
// //     return xnil;
// // }

// // static xint64 xclientsocketprocessor_tcp_open(xclientsocket * descriptor, void * data)
// // {
// //     xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

// //     if(xclientsocketcheck(descriptor, xclientsocketstatus_close) == xfalse)
// //     {
// //         if(xclientsocketcheck(descriptor, xclientsocketstatus_open) == xfalse)
// //         {
// //             if((descriptor->status & xsocketstatus_create) == xsocketstatus_void)
// //             {
// //                 if(xsocketcreate((xsocket *) descriptor) != xsuccess)
// //                 {
// //                     xlogfunction_end("%s(...) => %ld", __func__, xfail);
// //                     return xfail;
// //                 }
// //             }
// //             xdescriptornonblock_set((xdescriptor *) descriptor, xtrue);

// //             if((descriptor->status & (xsocketstatus_connect | xsocketstatus_connecting)) == xsocketstatus_void)
// //             {
// //                 if(xsocketconnect((xsocket *) descriptor, descriptor->addr, descriptor->addrlen) != xsuccess)
// //                 {
// //                     xlogfunction_end("%s(...) => %ld", __func__, xfail);
// //                     return xfail;
// //                 }
// //             }
// //         }
// //         xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
// //         return xsuccess;
// //     }
// //     xlogfunction_end("%s(...) => %ld", __func__, xfail);
// //     return xfail;
// // }

// // static xint64 xclientsocketprocessor_tcp_in(xclientsocket * descriptor, void * data)
// // {
// //     xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

// //     if(xclientsocketcheck(descriptor, xclientsocketstatus_open))
// //     {
// //         xstreamadjust(descriptor->stream.in, xfalse);
// //         // TODO: 8192 CHANGE OPTIMIZED VALUE
// //         xstreamcapacity_set(descriptor->stream.in, xstreamcapacity_get(descriptor->stream.in) + 8192);

// //         xint64 n = xdescriptorread((xdescriptor *) descriptor, xstreamback(descriptor->stream.in), xstreamremain(descriptor->stream.in));
// //         if(n > 0)
// //         {
// //             xstreamsize_set(descriptor->stream.in, n + xstreamsize_get(descriptor->stream.in));

// //             xlogfunction_end("%s(...) => %ld", __func__,  n);
// //             return n;
// //         }

// //         xlogfunction_end("%s(...) => %ld", __func__,  n);
// //         return n;
// //     }

// //     xlogfunction_end("%s(...) => %ld", xfail);
// //     return xfail;
// // }

// // static xint64 xclientsocketprocessor_tcp_out(xclientsocket * descriptor, void * data)
// // {
// //     xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

// //     if(xdescriptorcheck_open((xdescriptor *) descriptor))
// //     {
// //         if(xstreamlen(descriptor->stream.out) > 0)
// //         {
// //             xint64 n = xdescriptorwrite((xdescriptor *) descriptor, xstreamfront(descriptor->stream.out), xstreamlen(descriptor->stream.out));
// //             if(n > 0)
// //             {
// //                 xstreampos_set(descriptor->stream.out, xstreampos_get(descriptor->stream.out) + n);
// //             }
// //             xlogfunction_end("%s(...) => %ld", __func__, n);
// //             return n;
// //         }

// //         xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
// //         return xsuccess;
// //     }

// //     xlogfunction_end("%s(...) => %ld", __func__, xfail);
// //     return xfail;
// // }

// // static xint64 xclientsocketprocessor_tcp_close(xclientsocket * descriptor, void * data)
// // {
// //     xlogfunction_start("%s(%p, %p)", __func__, descriptor, data);

// //     xsocketshutdown((xsocket *) descriptor, xsocketeventtype_offall);
// //     xint64 ret = xdescriptorclose((xdescriptor *) descriptor);

// //     xlogfunction_end("%s(...) => %ld", __func__, ret);
// //     return ret;
// // }

// // static xint64 xclientsocketprocessor_tcp(xclientsocket * descriptor, xuint32 event, void * parameter)
// // {
// //     xlogfunction_start("%s(%p, %u, $p)", __func__, descriptor, event, parameter);
// //     xint64 ret = xsuccess;
// //     switch(event)
// //     {
// //         case xclientsocketeventtype_open:   ret = xclientsocketprocessor_tcp_open(descriptor, parameter);   break;
// //         case xclientsocketeventtype_in:     ret = xclientsocketprocessor_tcp_in(descriptor, parameter);     break;
// //         case xclientsocketeventtype_out:    ret = xclientsocketprocessor_tcp_out(descriptor, parameter);    break;
// //         case xclientsocketeventtype_close:  ret = xclientsocketprocessor_tcp_close(descriptor, parameter);  break;
// //     }

// //     xlogfunction_end("%s(...) => %d", __func__, xfail);
// //     return ret;
// // }

// // static xint64 xclientsocketsubscriber_tcp(xclientsocket * descriptor, xuint32 event, void * parameter, xint64 result)
// // {
// //     xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, descriptor, event, parameter, result);
// //     xclient * client = descriptor->client;

// //     if(descriptor->exception.number)
// //     {
// //         xcheck(xtrue, "exception errno => %d", descriptor->exception.number);
// //     }

// //     xcheck(xtrue, "event: %s, result: %ld", xclientsocketeventtype_str(event), result);

// //     xint64 ret = client->on(client, event, parameter, result);

// //     xlogfunction_end("%s(...) => %ld", __func__, ret);
// //     return ret;
// // }

// // static xint32 xclientsocketcheck_tcp(xclientsocket * o, xuint32 event)
// // {
// //     xlogfunction_start("%s(%p, %u)", __func__, o, event);
// //     xassertion(xtrue, "implement this");

// //     xlogfunction_end("%s(...) => %d", __func__, xfail);
// //     return xfail;
// // }

// // static void xclientsocketeventhandler_tcp(xclientsocketevent * event)
// // {
// //     xlogfunction_start("%s(%p)", __func__, event);
// //     xassertion(xtrue, "implement this");
// //     xlogfunction_end("%s(...)", __func__);
// // }

// // extern xint32 xclientsocketcheck_open(xclientsocket * o)
// // {
// //     xlogfunction_start("%s(%p)", __func__, o);
// //     xassertion(o == xnil, "");

// //     if(o->handle.f < 0)
// //     {
// //         xlogfunction_end("%s(...) => %d", __func__, xfalse);
// //         return xfalse;
// //     }

// //     if(o->status & (xsocketstatus_exception | xsocketstatus_rem | xsocketstatus_close))
// //     {
// //         xlogfunction_end("%s(...) => %d", __func__, xfalse);
// //         return xfalse;
// //     }

// //     if((o->status & (xsocketstatus_open | xsocketstatus_connecting | xsocketstatus_connect)) == xsocketstatus_void)
// //     {
// //         xlogfunction_end("%s(...) => %d", __func__, xfalse);
// //         return xfalse;
// //     }

// //     xlogfunction_end("%s(...) => %d", __func__, xtrue);
// //     return xtrue;
// // }

// // extern xint32 xclientsocketcheck_connecting(xclientsocket * o)
// // {
// //     xlogfunction_start("%s(%p)", __func__, o);
// //     xint32 ret = (o->status & xsocketstatus_connecting);
// //     xlogfunction_end("%s(...) => %d", __func__, ret);
// //     return ret;
// // }

// // extern const char * xclientsocketeventtype_str(xuint32 event)
// // {
// //     switch(event)
// //     {
// //         case xsocketeventtype_open:         return "open";
// //         case xsocketeventtype_in:           return "in";
// //         case xsocketeventtype_out:          return "out";
// //         case xsocketeventtype_close:        return "close";
// //         case xsocketeventtype_exception:    return "exception";
// //         case xsocketeventtype_rem:          return "rem";
// //         case xsocketeventtype_register:     return "register";
// //         case xsocketeventtype_create:       return "create";
// //         case xsocketeventtype_bind:         return "bind";
// //         case xsocketeventtype_connect:      return "connect";
// //         case xsocketeventtype_connecting:   return "connecting";
// //         case xsocketeventtype_listen:       return "listen";
// //         case xsocketeventtype_offin:        return "off in";
// //         case xsocketeventtype_offout:       return "off out";
// //         case xsocketeventtype_offall:       return "off all";
// //         default:                            return "unknown";
// //     }
// // }