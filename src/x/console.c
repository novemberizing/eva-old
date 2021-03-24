#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "console.h"
#include "console/descriptor.h"
#include "event/engine.h"

static xconsoledescriptor * xconsoledescriptor_rem(xconsoledescriptor * o);

struct xconsole
{
    xconsoledescriptor in;
    xconsoledescriptor out;
    xconsoleobserver   on;
};

static xconsole singleton = {
    {
        xconsoledescriptor_rem,             // rem
        xnil,                               // subscription
        xnil,                               // sync
        xdescriptormask_void,               // mask
        xdescriptorstatus_void,             // status
        xdescriptorhandle_invalid,          // handle
        xnil,                               // process: todo
        xnil,                               // check: deprecated
        xnil,                               // observer: todo
        { xnil, xnil, xnil, xnil, xnil },   // event: todo
        xexception_void,                    // exception
        xnil,                               // console
        xnil                                // stream
    },
    {
        xconsoledescriptor_rem,             // rem
        xnil,                               // subscription
        xnil,                               // sync
        xdescriptormask_void,               // mask
        xdescriptorstatus_void,             // status
        xdescriptorhandle_invalid,          // handle
        xnil,                               // process: todo
        xnil,                               // check: deprecated
        xnil,                               // observer: todo
        { xnil, xnil, xnil, xnil, xnil },   // event: todo
        xexception_void,                    // exception
        xnil,                               // console
        xnil                                // stream
    },
    xnil
};

extern void xconsoleobserver_set(xconsoleobserver on)
{
    singleton.on = on;
}

// /**
//  * 로직을 합번 정리할 필요가 있다.
//  */

// static xconsoledescriptor * xconsoledescriptor_rem(xconsoledescriptor * descriptor);
// static void xconsoledescriptoreventhandler_all(xconsoledescriptorevent * event);

// static xint64 xconsoledescriptorprocessor_input(xconsoledescriptor * descriptor, xuint32 event, void * parameter);
// static xint64 xconsoledescriptorsubscriber_input(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val);
// static xint32 xconsoledescriptorcheck_input(xconsoledescriptor * descriptor, xuint32 event);

// static void xconsoledescriptoreventhandler_input(xconsoledescriptorevent * event);


// static xconsoledescriptor consoledescriptor_in = {
//     /** INHERITED EVENT TARGET */
//     xconsoledescriptor_rem,
//     xnil,
//     xnil,
//     xdescriptormask_void,
//     xdescriptorstatus_void,
//     /** INHERITED DESCRIPTOR */
//     xdescriptorhandle_invalid,
//     xconsoledescriptorprocessor_input,
//     xconsoledescriptorcheck_input,
//     xconsoledescriptorsubscriber_input,
//     xconsoledescriptorevent_void,
//     xexception_void,
//     /** CONSOLE DESCRIPTOR MEMBER */
//     xnil,
//     xnil
// };

// static xint64 xconsoledescriptorprocessor_output(xconsoledescriptor * descriptor, xuint32 event, void * parameter);
// static xint64 xconsoledescriptorsubscriber_output(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val);
// static xint32 xconsoledescriptorcheck_output(xconsoledescriptor * descriptor, xuint32 event);

// static void xconsoledescriptoreventhandler_output(xconsoledescriptorevent * event);

// static xconsoledescriptor consoledescriptor_out = {
//     /** INHERITED EVENT TARGET */
//     xconsoledescriptor_rem,
//     xnil,
//     xnil,
//     xdescriptormask_void,
//     xdescriptorstatus_void,
//     /** INHERITED DESCRIPTOR */
//     xdescriptorhandle_invalid,
//     xconsoledescriptorprocessor_output,
//     xconsoledescriptorcheck_output,
//     xconsoledescriptorsubscriber_output,
//     xconsoledescriptorevent_void,
//     xexception_void,
//     /** CONSOLE DESCRIPTOR MEMBER */
//     xnil,
//     xnil
// };

// static xconsole console = { xnil, xnil, xnil };

// extern xconsole * xconsoleinit(xconsolesubscriber on)
// {
//     xconsolesubscriber_set(on);
// }

// extern xconsole * xconsoleget(void)
// {
//     return xaddressof(console);
// }

// extern void xconsoleterm(void)
// {
//     xlogfunction_start("%s()", __func__);

//     if(console.in)
//     {
//         if(console.in->subscription)
//         {
//             if(console.in->subscription->enginenode.engine)
//             {
//                 xeventengine_descriptor_unregister(console.in->subscription->enginenode.engine, (xdescriptor *) console.in);
//             }
//             xeventsubscription * subscription = (xeventsubscription *) console.in->subscription;
//             console.in->subscription = xnil;
//             xeventsubscription_rem(subscription);
//         }
//         console.in = xconsoledescriptor_rem(console.in);
//     }
//     if(console.out)
//     {
//         if(console.out->subscription)
//         {
//             if(console.out->subscription->enginenode.engine)
//             {
//                 xeventengine_descriptor_unregister(console.out->subscription->enginenode.engine, (xdescriptor *) console.out);
//             }
//             xeventsubscription * subscription = (xeventsubscription *) console.out->subscription;
//             console.out->subscription = xnil;
//             xeventsubscription_rem(subscription);
            
//         }
//         console.out = xconsoledescriptor_rem(console.out);
//     }

//     xlogfunction_end("%s()", __func__);
// }

// extern void xconsolesubscriber_set(xconsolesubscriber subscriber)
// {
//     xlogfunction_start("%s(%p)", __func__, subscriber);

//     if(console.in == xnil)
//     {
//         console.in = (xconsoledescriptor *) xconsoledescriptorin_get();
//     }
//     if(console.out == xnil)
//     {
//         console.out = (xconsoledescriptor *) xconsoledescriptorout_get();
//     }
//     console.on = (subscriber ? subscriber : xconsolesubscriber_default);

//     xlogfunction_end("%s(...)", __func__);
// }

// extern xint64 xconsolesubscriber_default(xconsole * console, xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 value)
// {
//     xlogfunction_start("%s(%p, %p, %d, %p, %ld)", __func__, console, descriptor, event, parameter, value);

//     xassertion(xtrue, "implement this");

//     xlogfunction_end("%s(...) => %ld", __func__, value);
//     return value;
// }

// extern xdescriptor * xconsoledescriptorin_get(void)
// {
//     xlogfunction_start("%s()", __func__);

//     if(console.in == xnil)
//     {
//         console.in = xaddressof(consoledescriptor_in);
//         console.in->handle.f = STDIN_FILENO;
//         console.in->event.descriptor = xaddressof(consoledescriptor_in);
//         console.in->event.on = xconsoledescriptoreventhandler_input;
//         console.in->status = (xdescriptorstatus_open | xdescriptorstatus_out);
//         console.in->console = xaddressof(console);
//         // TODO: 사용자가 버퍼를 생성할 수 있도록 하자.
//         console.in->stream = xstreamnew(xstreamtype_default);
//     }
    
//     xlogfunction_end("%s(...) => %p", __func__, console.in);
//     return (xdescriptor *) console.in;
// }

// extern xdescriptor * xconsoledescriptorout_get(void)
// {
//     xlogfunction_start("%s()", __func__);

//     if(console.out == xnil)
//     {
//         console.out = xaddressof(consoledescriptor_out);
//         console.out->handle.f = STDOUT_FILENO;
//         console.out->event.descriptor = xaddressof(consoledescriptor_out);
//         console.out->event.on = xconsoledescriptoreventhandler_output;
//         console.out->status = (xdescriptorstatus_open | xdescriptorstatus_out | xdescriptorstatus_in);
//         console.out->console = xaddressof(console);
//         // TODO: 사용자가 버퍼를 생성할 수 있도록 하자.
//         console.out->stream = xstreamnew(xstreamtype_default);
//     }

//     xlogfunction_end("%s(...) => %p", __func__, console.out);
//     return (xdescriptor *) console.out;
// }


// static xconsoledescriptor * xconsoledescriptor_rem(xconsoledescriptor * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);
//     xassertion(descriptor == xnil, "");
//     xassertion(descriptor->event.queue || descriptor->event.next || descriptor->event.prev, "");
//     xassertion(descriptor->subscription != xnil, "");

//     descriptor->console   = xnil;
//     descriptor->exception = xexception_void;
//     descriptor->status    = xdescriptorstatus_open;
//     descriptor->stream    = xstreamrem(descriptor->stream);
//     descriptor->sync      = xsyncrem(descriptor->sync);

//     xlogfunction_end("%s(...) => %p", __func__, descriptor);
//     return descriptor;
// }

// static inline xint64 xconsoledescriptorprocessor_input_open(xconsoledescriptor * descriptor, void * parameter)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, parameter);

//     if(xdescriptorcheck_close((xdescriptor *) descriptor) == xfalse)
//     {
//         if(descriptor->stream == xnil)
//         {
//             descriptor->stream = xstreamnew(xstreamtype_default);
//         }
//         if(descriptor->handle.f == xinvalid)
//         {
//             descriptor->handle.f = STDIN_FILENO;
//         }

//         if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
//         {
//             descriptor->status = (xdescriptorstatus_open | xdescriptorstatus_out);
//         }

//         xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
//         return xsuccess;
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//     return xfail;
// }


// static inline xint64 xconsoledescriptorprocessor_output_open(xconsoledescriptor * descriptor, void * parameter)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, parameter);

//     if(xdescriptorcheck_open((xdescriptor *) descriptor))
//     {
//         if(descriptor->stream == xnil)
//         {
//             descriptor->stream = xstreamnew(xstreamtype_default);
//         }
//         if(descriptor->handle.f == xinvalid)
//         {
//             descriptor->handle.f = STDOUT_FILENO;
//         }

//         if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
//         {
//             descriptor->status = (xdescriptorstatus_open | xdescriptorstatus_in | xdescriptorstatus_out);
//         }

//         xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
//         return xsuccess;
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//     return xfail;
// }

// static inline xint64 xconsoledescriptorprocessor_out(xconsoledescriptor * descriptor, void * parameter)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, parameter);

//     if(xdescriptorcheck_open((xdescriptor *) descriptor))
//     {
//         if(xstreamlen(descriptor->stream) > 0)
//         {
//             xint64 n = xdescriptorwrite((xdescriptor *) descriptor, xstreamfront(descriptor->stream), xstreamlen(descriptor->stream));
//             if(n > 0)
//             {
//                 xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + n);
//             }

//             xlogfunction_end("%s(...) => %ld", __func__, n);
//             return n;
//         }

//         xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
//         return xsuccess;
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//     return xfail;
// }

// static inline xint64 xconsoledescriptorprocessor_in(xconsoledescriptor * descriptor, void * parameter)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, parameter);

//     if(xdescriptorcheck_open((xdescriptor *) descriptor))
//     {
//         xstreamadjust(descriptor->stream, xfalse);
//         xstreamcapacity_set(descriptor->stream, xstreamcapacity_get(descriptor->stream) + 8192);

//         xint64 n = xdescriptorread((xdescriptor *) descriptor, xstreamback(descriptor->stream), xstreamremain(descriptor->stream));
//         if(n > 0)
//         {
//             xstreamsize_set(descriptor->stream, n + xstreamsize_get(descriptor->stream));

//             xlogfunction_end("%s(...) => %ld", __func__, n);
//             return n;
//         }

//         xlogfunction_end("%s(...) => %ld", __func__, n);
//         return n;
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//     return xfail;
// }

// static inline xint64 xconsoledescriptorprocessor_close(xconsoledescriptor * descriptor, void * parameter)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, parameter);

//     if((descriptor->status & xdescriptorstatus_close) == xdescriptorstatus_void)
//     {
//         descriptor->status |= xdescriptorstatus_close;
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
//     return xsuccess;
// }

// static inline xint64 xconsoledescriptorprocessor_exception(xconsoledescriptor * descriptor, void * parameter)
// {
//     xlogfunction_start("%s(%p, %p)", __func__, descriptor, parameter);

//     if((descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
//     {
//         descriptor->status |= xdescriptorstatus_exception;
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
//     return xsuccess;
// }

// static xint64 xconsoledescriptorprocessor_input(xconsoledescriptor * descriptor, xuint32 event, void * parameter)
// {
//     xlogfunction_start("%s(%p, %u, %p)", __func__, descriptor, event, parameter);

//     xint64 ret = xsuccess;
//     switch(event)
//     {
//         case xdescriptoreventtype_open:      ret = xconsoledescriptorprocessor_input_open(descriptor, parameter);   break;
//         case xdescriptoreventtype_in:        ret = xconsoledescriptorprocessor_in(descriptor, parameter);           break;
//         case xdescriptoreventtype_close:     ret = xconsoledescriptorprocessor_close(descriptor, parameter);        break;
//         case xdescriptoreventtype_exception: ret = xconsoledescriptorprocessor_exception(descriptor, parameter);    break;
//         default:                             xassertion(xtrue, "");                                                 break;
//     }
    
//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }


// static xint64 xconsoledescriptorsubscriber_input(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val)
// {
//     xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, descriptor, event, parameter, val);

//     xassertion(descriptor == xnil, "");
//     xassertion(descriptor->console == xnil, "");
//     xassertion(descriptor->console->on == xnil, "");

//     // 콘솔 입출력은 ????? 이벤트 핸들링을 어떻게 해야할까?

//     xint64 ret = descriptor->console->on(descriptor->console, descriptor, event, parameter, val);

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// static xint64 xconsoledescriptorsubscriber_on(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val)
// {
//     xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, descriptor, event, parameter, val);
//     xassertion(descriptor == xnil, "");
//     xassertion(descriptor->console == xnil, "");
//     xassertion(descriptor->console->on == xnil, "");

//     xint64 ret = descriptor->console->on(descriptor->console, descriptor, event, parameter, val);

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// static xint32 xconsoledescriptorcheck_input(xconsoledescriptor * descriptor, xuint32 event)
// {
//     xlogfunction_start("%s(%p, %u)", __func__, descriptor, event);

//     if(event == xdescriptoreventtype_out)
//     {
//         xlogfunction_end("%s(...) => %d", __func__, xfalse);
//         return xfalse;
//     }

//     xassertion(xtrue, "");

//     xlogfunction_end("%s(...) => %d", __func__, xtrue);
//     return xtrue;
// }

// static xint64 xconsoledescriptorprocessor_output(xconsoledescriptor * descriptor, xuint32 event, void * parameter)
// {
//     xlogfunction_start("%s(%p, %u, %p)", __func__, descriptor, event, parameter);

//     xint64 ret = xsuccess;
//     switch(event)
//     {
//         case xdescriptoreventtype_open:         ret = xconsoledescriptorprocessor_output_open(descriptor, parameter);   break;
//         case xdescriptoreventtype_out:          ret = xconsoledescriptorprocessor_out(descriptor, parameter);           break;
//         case xdescriptoreventtype_close:        ret = xconsoledescriptorprocessor_close(descriptor, parameter);         break;
//         case xdescriptoreventtype_exception:    ret = xconsoledescriptorprocessor_exception(descriptor, parameter);     break;
//         default:                                xassertion(xtrue, "");                                                  break;
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// static xint64 xconsoledescriptorsubscriber_output(xconsoledescriptor * descriptor, xuint32 event, void * parameter, xint64 val)
// {
//     xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, descriptor, event, parameter, val);

//     xassertion(descriptor == xnil, "");
//     xassertion(descriptor->console == xnil, "");
//     xassertion(descriptor->console->on == xnil, "");

//     xint64 ret = descriptor->console->on(descriptor->console, descriptor, event, parameter, val);

//     xlogfunction_end("%s(...) => %ld", __func__, ret);
//     return ret;
// }

// static xint32 xconsoledescriptorcheck_output(xconsoledescriptor * descriptor, xuint32 event)
// {
//     xlogfunction_start("%s(%p, %u)", __func__, descriptor, event);
//     if(event == xdescriptoreventtype_out)
//     {
//         xint32 ret = (xstreamlen(descriptor->stream) > 0);

//         xlogfunction_end("%s(...) => %d", __func__, ret);
//         return ret;
//     }

//     xassertion(xtrue, "");

//     xlogfunction_end("%s(...) => %ld", __func__, xtrue);
//     return xtrue;
    
// }

// extern xint64 xconsoleout_string(const char * s)
// {
//     xlogfunction_start("%s(%s)", __func__, s);

//     xconsoledescriptor * descriptor = (xconsoledescriptor *) xconsoledescriptorout_get();

//     xint64 len = strlen(s);

//     xstreampush(descriptor->stream, s, len);

//     if(descriptor->subscription == xnil)
//     {
//         xint64 n = xdescriptorwrite((xdescriptor *) descriptor, xstreamfront(descriptor->stream), xstreamlen(descriptor->stream));

//         if(n > 0)
//         {
//             xassertion(n + len < xstreamlen(descriptor->stream), "");

//             xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + n);
//             xstreamadjust(descriptor->stream, xfalse);
//         }
//         else
//         {
//             xassertion(len > 0, "");
//             xassertion(n < 0, "");
//         }

//         xlogfunction_end("%s(...) => %ld", __func__, n);
//         return n;
//     }
//     else
//     {
//         return xstreamlen(descriptor->stream);
//     }
// }

// /**
//  * 현재까지 받을 수 있는 총량만을 출력한다.
//  * 즉, SIZE 는 힌트일 뿐이다.
//  */
// extern xint64 xconsolein_string(char * buffer, xuint64 size)
// {
//     xlogfunction_start("%s(%p, %lu)", __func__, buffer, size);

//     xassertion(buffer == xnil || size == 0, "");

//     xint64 n = 0;

//     xconsoledescriptor * descriptor = (xconsoledescriptor *) xconsoledescriptorin_get();

//     if(size <= xstreamlen(descriptor->stream))
//     {
//         memcpy(buffer, xstreamfront(descriptor->stream), size);
//         xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + size);
//         xstreamadjust(descriptor->stream, xfalse);

//         xlogfunction_end("%s(...) => %lu", __func__, size);
//         return size;
//     }
//     else if(xstreamlen(descriptor->stream) > 0)
//     {
//         xint64 n = xdescriptorread((xdescriptor *) descriptor, xstreamback(descriptor->stream), size - xstreamlen(descriptor->stream));
//         if(n > 0)
//         {
//             xstreamsize_set(descriptor->stream, xstreamsize_get(descriptor->stream) + n);
//         }
//         xassertion(n < 0, "");

//         xassertion(xtrue, "implement this");

//         // xint64 len = xstreamlen(descriptor->str

//         memcpy(buffer, xstreamfront(descriptor->stream), size);
//         xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + size);
//         xstreamadjust(descriptor->stream, xfalse);

//         xlogfunction_end("%s(...) => %lu", __func__, size);
//         return size;
//     }
//     else
//     {
//         xint64 n = xdescriptorread((xdescriptor *) descriptor, buffer, size);
//         // TODO: CHECK THIS LOGIC
//         if(n > 0)
//         {
//             xlogfunction_end("%s(...) => %lu", __func__, n);
//             return n;
//         }
//         else if(n == 0)
//         {
//             xassertion(n < 0, "");

//             xlogfunction_end("%s(...) => %lu", __func__, n);
//             return n;
//         }
//         else
//         {
//             xassertion(n < 0, "");
//             xlogfunction_end("%s(...) => %lu", __func__, xfail);
//             return xfail;
//         }

//         xlogfunction_end("%s(...) => %lu", __func__, n);
//         return n;
//     }

//     xlogfunction_end("%s(...) => %lu", __func__, xfail);
//     return xfail;
// }

// extern void xconsoleout_flush(void)
// {
//     xlogfunction_start("%s()", __func__);
//     xconsoledescriptor * descriptor = (xconsoledescriptor *) xconsoledescriptorout_get();
    
//     if(xdescriptorcheck_open((xdescriptor *) descriptor))
//     {
//         descriptor->status |= xdescriptorstatus_flush;
//         if(descriptor->status & xdescriptorstatus_out)
//         {
//             xint64 n = xdescriptorwrite((xdescriptor *) descriptor, xstreamfront(descriptor->stream), xstreamlen(descriptor->stream));
//             if(n >= 0)
//             {
//                 if(n > 0)
//                 {
//                     xstreampos_set(descriptor->stream, xstreampos_get(descriptor->stream) + n);
//                     xstreamadjust(descriptor->stream, xfalse);
//                     if(xstreamlen(descriptor->stream) == 0)
//                     {
//                         descriptor->status &= (~xdescriptorstatus_flush);
//                     }
//                 }
//             }
//             else
//             {
//                 xassertion(xtrue, "");
//             }
//         }
//     }

//     xlogfunction_end("%s(...)", __func__);
// }

// extern void xconsolein_flush(void)
// {
//     xlogfunction_start("%s()", __func__);

//     xconsoledescriptor * descriptor = (xconsoledescriptor *) xconsoledescriptorin_get();
//     xstreamclear(descriptor->stream);

//     xlogfunction_end("%s(...)", __func__);
// }

// static void xconsoledescriptoreventhandler_all(xconsoledescriptorevent * event)
// {
//     xlogfunction_start("%s(%p)", __func__, event);
    
//     xdescriptor * descriptor = (xdescriptor *) event->descriptor;

//     xassertion(descriptor == xnil, "");

//     if(xdescriptorcheck_close(descriptor))
//     {
//         xdescriptorevent_processor_unregister(descriptor);
//         xdescriptorevent_processor_close(descriptor);
//         xlogfunction_end("%s(...)", __func__);
//         return;
//     }
//     else if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
//     {
//         xassertion(xtrue, "not support open");
//         // xdescriptorevent_processor_open(descriptor);
//     }

//     xdescriptor * out = xconsoledescriptorout_get();

//     if(out->status & xdescriptorstatus_flush)
//     {
//         xdescriptorevent_processor_out(descriptor);
//     }
//     else
//     {
//         xdescriptorevent_processor_in(descriptor);
//     }

//     if((descriptor->status & (xdescriptorstatus_in | xdescriptorstatus_out)) != (xdescriptorstatus_in | xdescriptorstatus_out))
//     {
//         xdescriptorevent_processor_register(descriptor);
//     }

//     if(xdescriptorcheck_close(descriptor))
//     {
//         xdescriptorevent_processor_unregister(descriptor);
//         xdescriptorevent_processor_close(descriptor);

//         xlogfunction_end("%s(...) => %d", __func__);
//         return;
//     }

//     xlogfunction_end("%s(...)", __func__);
// }

// static void xconsoledescriptoreventhandler_input(xconsoledescriptorevent * event)
// {
//     xlogfunction_start("%s(%p)", __func__, event);

//     xconsoledescriptoreventhandler_all(event);

//     xlogfunction_end("%s(...)", __func__);
// }

// static void xconsoledescriptoreventhandler_output(xconsoledescriptorevent * event)
// {
//     xlogfunction_start("%s(%p)", __func__, event);

//     xconsoledescriptoreventhandler_all(event);

//     xlogfunction_end("%s(...)", __func__);
// }

// extern xstream * xconsoledescriptorstream_get(xconsoledescriptor * descriptor)
// {
//     return descriptor->stream;
// }