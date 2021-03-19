#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "descriptor.h"
#include "thread.h"

#include "event/engine.h"

extern xint64 xdescriptoron(xdescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
{
    if(event == xdescriptoreventtype_exception)
    {
        result = descriptor->on(descriptor, event, param, result);
    }
    else
    {
        xint64 n = descriptor->on(descriptor, event, param, result);
        if(result >=0 && n < 0)
        {
            descriptor->status |= xdescriptorstatus_exception;
            xexceptionset(xaddressof(descriptor->exception), descriptor->on, 0, xexceptiontype_user, "");
            result = descriptor->on(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), n);
        }
        else
        {
            result = n;
        }
    }
    return result;
}

extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, descriptor, buffer, size);
    xint64 n = xfail;

    if(xdescriptorstatuscheck_in(descriptor))
    {
        if(descriptor->status & xdescriptorstatus_opening)
        {
            if(descriptor->process(descriptor, xdescriptoreventtype_opening) != xsuccess)
            {
                xlogfunction_end("%s(...) => %ld", __func__, xfail);
                return xfail;
            }
            if(descriptor->status & xdescriptorstatus_opening)
            {
                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
            xassertion((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void, "");
        }
        if(buffer && size)
        {
            n = read(descriptor->handle.f, buffer, size);

            if(n > 0)
            {
                descriptor->status &= (~xdescriptorstatus_end);
                descriptor->status |= xdescriptorstatus_in;
                n = xdescriptoron(descriptor, xdescriptorstatus_in, xdescriptorparamgen(buffer), n);
            }
            else if(n == 0)
            {
                descriptor->status |= xdescriptorstatus_end;
                n = xdescriptoron(descriptor, xdescriptorstatus_in, xdescriptorparamgen(buffer), n);
            }
            else
            {
                if(errno == EAGAIN)
                {
                    descriptor->status &= (~(xdescriptorstatus_end | xdescriptorstatus_in));
                    n = xsuccess;
                }
                else
                {
                    descriptor->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(descriptor->exception), read, errno, xexceptiontype_system, "");
                    n = descriptor->on(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), n);
                }
            }
        }
        else
        {
            xlognotice("");
            n = xsuccess;
        }
    }
    
    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, descriptor, data, len);
    xint64 n = xfail;

    if(xdescriptorstatuscheck_out(descriptor))
    {
        if(descriptor->status & xdescriptorstatus_opening)
        {
            if(descriptor->process(descriptor, xdescriptoreventtype_opening) != xsuccess)
            {
                xlogfunction_end("%s(...) => %ld", __func__, xfail);
                return xfail;
            }
            if(descriptor->status & xdescriptorstatus_opening)
            {
                xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
                return xsuccess;
            }
            xassertion((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void, "");
        }
        if(data && len)
        {
            n = write(descriptor->handle.f, data, len);

            if(n > 0)
            {
                descriptor->status |= xdescriptorstatus_out;
                n = xdescriptoron(descriptor, xdescriptorstatus_out, xdescriptorparamgen_const(data), n);
            }
            else if(n == 0)
            {
                n = xdescriptoron(descriptor, xdescriptorstatus_out, xdescriptorparamgen_const(data), n);
            }
            else
            {
                if(errno == EAGAIN)
                {
                    descriptor->status &= (~xdescriptorstatus_out);
                    n = xsuccess;
                }
                else
                {
                    descriptor->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(descriptor->exception), write, errno, xexceptiontype_system, "");
                    n = descriptor->on(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), n);
                }
            }
        }
        else
        {
            xlognotice("");
            n = xsuccess;
        }
    }
    
    xlogfunction_end("%s(...) => %ld", __func__, n);
    return n;
}

extern xint64 xdescriptorclose(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    if(descriptor->handle.f >= 0)
    {
        xdescriptoreventsubscription * subscription = descriptor->subscription;
        if(subscription)
        {
            xdescriptoreventgenerator * generator = subscription->generatornode.generator;
            if(generator)
            {
                xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
            }
        }

        if(descriptor->handle.f > xdescriptorsystemno_max)
        {
            if(close(descriptor->handle.f) < 0)
            {
                descriptor->status |= xdescriptorstatus_exception;
                xexceptionset(xaddressof(descriptor->exception), close, errno, xexceptiontype_system, "");
                descriptor->on(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), xfail);
            }
            descriptor->status |= xdescriptorstatus_close;
            descriptor->on(descriptor, xdescriptoreventtype_close, xdescriptorparamgen(xnil), xsuccess);
            descriptor->handle.f = xinvalid;
            descriptor->process(descriptor, xdescriptoreventtype_clear);
        }
        descriptor->status = (descriptor->status & xdescriptorstatus_rem);
    }

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

extern xint64 xdescriptorexception(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xdescriptorclose(descriptor);

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

extern xint64 xdescriptorrem(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    descriptor->rem(descriptor);

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

extern xint64 xdescriptorregister(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xdescriptoreventsubscription * subscription = descriptor->subscription;
    if(subscription)
    {
        xdescriptoreventgenerator * generator = subscription->generatornode.generator;

        if(generator)
        {
            xint64 ret = xdescriptoreventgenerator_descriptor_register(generator, descriptor);
            if(ret < 0)
            {
                descriptor->status |= xdescriptorstatus_exception;
                xexceptionset(xaddressof(descriptor->exception), xdescriptoreventgenerator_descriptor_register, 0, xexceptiontype_lib, "");
                descriptor->on(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), xfail);
            }
            xlogfunction_end("%s(...) => %ld", __func__, ret);
            return ret;
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

extern xint64 xdescriptorclear(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xassertion(descriptor->handle.f >= 0, "");

    if(descriptor->handle.f < 0)
    {
        if(descriptor->subscription)
        {
            xassertion(descriptor->subscription->generatornode.list || descriptor->subscription->generatornode.prev || descriptor->subscription->generatornode.next, "");
        }
        
        descriptor->status = (descriptor->status & xdescriptorstatus_rem);
        descriptor->exception = xexception_void;
    }
    else
    {
        xassertion(descriptor->handle.f >= 0, "");
    }

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

extern xint64 xdescriptorunregister(xdescriptor * descriptor)
{
    xlogfunction_start("%s(%p)", __func__, descriptor);

    xdescriptoreventsubscription * subscription = descriptor->subscription;
    if(subscription)
    {
        xdescriptoreventgenerator * generator = subscription->generatornode.generator;
        if(generator)
        {
            xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
        }
    }

    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

extern xint64 xdescriptoreventdispatch(xdescriptor * descriptor, xuint32 event)
{
    xint64 ret = xsuccess;

    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(subscription)
    {
        if(xeventengine_descriptor_dispatch(descriptor, event) != xsuccess)
        {
            ret = descriptor->process(descriptor, xdescriptoreventtype_void);
        }
    }
    else
    {
        ret = descriptor->process(descriptor, event);
    }

    return ret;
}

extern xint32 xdescriptornonblock(xdescriptor * descriptor, xint32 on)
{
    xlogfunction_start("%s(%p, %d)", __func__, descriptor, on);

    xassertion(descriptor == xnil || descriptor->handle.f < 0, "");

    int mask = fcntl(descriptor->handle.f, F_GETFL, 0);
    if(mask < 0)
    {
        descriptor->status |= xdescriptorstatus_exception;
        xexceptionset(xaddressof(descriptor->exception), fcntl, errno, xexceptiontype_system, "");
        xdescriptoron(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), xfail);

        xlogfunction_end("%s(...) => %d", __func__, xfail);
        return xfail;
    }
    if(on)
    {
        mask |= O_NONBLOCK;
    }
    else
    {
        mask &= (~O_NONBLOCK);
    }
    if(fcntl(descriptor->handle.f, F_SETFL, mask) != xsuccess)
    {
        descriptor->status |= xdescriptorstatus_exception;
        xexceptionset(xaddressof(descriptor->exception), fcntl, errno, xexceptiontype_system, "");
        xdescriptoron(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), xfail);

        xlogfunction_end("%s(...) => %d", __func__, xfail);
        return xfail;
    }

    xlogfunction_end("%s(...) => %d", __func__, xsuccess);
    return xsuccess;
}



// #define xdescriptoreventtype_exception       5



// #define xdescriptoreventtype_void            0
// #define xdescriptoreventtype_open            1
// #define xdescriptoreventtype_in              2
// #define xdescriptoreventtype_out             3
// #define xdescriptoreventtype_close           4
// #define xdescriptoreventtype_exception       5
// #define xdescriptoreventtype_rem             6
// #define xdescriptoreventtype_register        7
// #define xdescriptoreventtype_flush           8
// #define xdescriptoreventtype_readoff         9
// #define xdescriptoreventtype_writeoff   1    0
// #define xdescriptoreventtype_opening        11
// #define xdescriptoreventtype_create         12
// #define xdescriptoreventtype_bind           13
// #define xdescriptoreventtype_clear          14
// #define xdescriptoreventtype_alloff         15
// #define xdescriptoreventtype_connect        16
// #define xdescriptoreventtype_listen         17
// #define xdescriptoreventtype_connecting     18
// #define xdescriptoreventtype_unregister     19

// static xint64 xdescriptoron(xdescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result)
// {
//     xlogfunction_start("%s(%p, %u, %p, %ld)", __func__, descriptor, event, param.p, result);

//     if(event == xdescriptoreventtype_exception)
//     {
//         result = descriptor->on(descriptor, event, param, result);
//     }
//     else
//     {
//         result = descriptor->on(descriptor, event, param, result);
//         if(result < 0)
//         {
//             descriptor->status |= xdescriptorstatus_exception;
//             result = descriptor->on(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), result);
//         }
//     }
    
//     xlogfunction_end("%s(...) => %ld", __func__, result);
//     return result;
// }

// extern xint64 xdescriptorregistrationstatus_clear(xdescriptor * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);
//     xdescriptoreventsubscription * subscription = descriptor->subscription;

//     if(subscription)
//     {
//         xdescriptoreventgenerator * generator = subscription->generatornode.generator;
//         if(generator)
//         {
//             xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
//             descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xfalse);
//         }
//     }

//     xlogfunction_end("%s(...) => %ld", xsuccess);
//     return xsuccess;
// }

// extern xint64 xdescriptorclose(xdescriptor * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);

//     if(descriptor->handle.f >= 0)
//     {
//         xdescriptorregistrationclear(descriptor);

//         if(descriptor->handle.f >= xdescriptorsystemno_max)
//         {
//             if(close(descriptor->handle.f) != xsuccess)
//             {
//                 descriptor->status |= xdescriptorstatus_exception;
//                 xexceptionset(xaddressof(descriptor->exception), close, errno, xexceptiontype_system, "");
//                 xdescriptoron(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xnil), xsuccess);
//             }
//             descriptor->status |= xdescriptorstatus_close;
//             xdescriptoron(descriptor, xdescriptoreventtype_close, xdescriptorparamgen(xnil), xsuccess);
//             descriptor->handle.f = xinvalid;
//             descriptor->status = (descriptor->status & xdescriptorstatus_rem);

//             descriptor->process(descriptor, xdescriptoreventtype_clear);
//         }
//         else
//         {

//         }
//     }
    
//     xlogfunction_end("%s(...) => %ld", xsuccess);
//     return xsuccess;
// }

// extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size);
// extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len);
// extern xint32 xdescriptornonblock(xdescriptor * descriptor, xint32 on);

// extern xint32 xdescriptorstatuscheck_open(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_in(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_out(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_close(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_exception(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_rem(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_register(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_readoff(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_writeoff(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_alloff(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_opening(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_create(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_bind(xdescriptor * descriptor);

// extern xint64 xdescriptoreventdispatch(xdescriptor * descriptor, xuint32 event);

// extern xuint32 xdescriptorstatus_get(xdescriptor * descriptor);

// extern xdescriptoreventsubscription * xdescriptoreventsubscription_get(xdescriptor * descriptor);

// extern const char * xdescriptoreventtype_str(xuint32 event);





// extern xint64 xdescriptorclose(xdescriptor * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);

//     xassertion(descriptor == xnil, "");

//     if(descriptor->handle.f > xdescriptorsystemno_max)
//     {
//         if(close(descriptor->handle.f) != xsuccess)
//         {
//             xlogcaution("close(%d) => fail (%d)", descriptor->handle.f, errno);
//         }
//         descriptor->status |= xdescriptorstatus_close;
//         xdescriptoron(descriptor, xdescriptoreventtype_close, xdescriptorparamgen(xnil), xsuccess);
//         descriptor->handle.f = xinvalid;
//     }

//     xlogfunction_end("%s(...) => %ld", xsuccess);
//     return xsuccess;
// }

// extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
// {
//     xlogfunction_start("%s(%p, %p, %lu)", __func__, descriptor, buffer, size);

//     xassertion(descriptor == xnil, "");

//     xint64 n = xfail;

//     if(xdescriptorstatuscheck_in(descriptor))
//     {
//         if(buffer && size)
//         {
//             n = read(descriptor->handle.f, buffer, size);

//             if(n > 0)
//             {
//                 descriptor->status |= xdescriptorstatus_in;
//                 n = xdescriptoron(descriptor, xdescriptoreventtype_in, xdescriptorparamgen(buffer), n);
//             }
//             else if(n == 0)
//             {
//                 descriptor->status &= (~xdescriptorstatus_in);
//                 n = xdescriptoron(descriptor, xdescriptoreventtype_in, xdescriptorparamgen(buffer), n);
//             }
//             else
//             {
//                 if(errno != EAGAIN)
//                 {
//                     xexceptionset(xaddressof(descriptor->exception), read, errno, xexceptiontype_system, "");
//                     descriptor->status |= xdescriptorstatus_exception;
//                     n = xdescriptoron(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xaddressof(descriptor->exception)), n);
//                 }
//                 else
//                 {
//                     descriptor->status &= (~xdescriptorstatus_in);
//                     n = xsuccess;
//                 }
//             }
//         }
//         else
//         {
//             xlogcaution("buffer: %p, size: %lu", buffer, size);
//             n = xsuccess;
//         }
//     }
//     else
//     {
//         n = xdescriptorstatuscheck_close(descriptor) ? xfail : xsuccess;
//     }

//     xlogfunction_end("%s(...) => %ld", n);
//     return n;
// }

// extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len)
// {
//     xlogfunction_start("%s(%p, %p, %lu)", __func__, descriptor, data, len);

//     xassertion(descriptor == xnil, "");

//     xint64 n = xfail;
//     if(xdescriptorstatuscheck_out(descriptor))
//     {
//         if(data && len)
//         {
//             n = write(descriptor->handle.f, data, len);

//             if(n > 0)
//             {
//                 descriptor->status |= xdescriptorstatus_out;
//                 n = xdescriptoron(descriptor, xdescriptoreventtype_out, xdescriptorparamgen_const(data), n);
//             }
//             else if(n == 0)
//             {
//                 xassertion(xtrue, "");
//             }
//             else
//             {
//                 if(errno != EAGAIN)
//                 {
//                     xexceptionset(xaddressof(descriptor->exception), read, errno, xexceptiontype_system, "");
//                     descriptor->status |= xdescriptorstatus_exception;
//                     n = xdescriptoron(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xnil), n);
//                 }
//                 else
//                 {
//                     descriptor->status &= (~xdescriptorstatus_out);
//                     n = xsuccess;
//                 }
//             }
//         }
//         else
//         {
//             xlogcaution("data: %p, size: %lu", data, len);
//             n = xsuccess;
//         }
//     }
//     else
//     {
//         n = xdescriptorstatuscheck_close(descriptor) ? xfail : xsuccess;
//     }

//     xlogfunction_end("%s(...) => %ld", n);
//     return n;
// }

// extern xint64 xdescriptoreventdispatch(xdescriptor * descriptor, xuint32 event)
// {
//     xint64 ret = xsuccess;

//     xdescriptoreventsubscription * subscription = descriptor->subscription;

//     if(subscription)
//     {
//         if(xeventengine_descriptor_dispatch(descriptor, event) != xsuccess)
//         {
//             ret = descriptor->process(descriptor, event);
//             xdescriptoreventprocess(descriptor, xdescriptoreventtype_void);
//         }
//     }
//     else
//     {
//         ret = descriptor->process(descriptor, event);
//     }

//     return ret;
// }




// extern xint64 xdescriptorregister(xdescriptor * descriptor, xeventengine * engine)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);

//     if(xdescriptorstatuscheck_close(descriptor) == xfalse)
//     {
//         if(descriptor->status & (xdescriptorstatus_opening | xdescriptorstatus_open))
//         {
//             xdescriptoreventsubscription * subscription = descriptor->subscription;

//             if(subscription)
//             {
//                 xdescriptoreventgenerator * generator = subscription->generatornode.generator;
//                 if(generator)
//                 {
//                     xassertion(subscription->enginenode.engine == xnil, "");

//                     xint64 n = xdescriptoreventgenerator_descriptor_update(generator, descriptor);
//                     n = descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), n == xsuccess);
//                     xlogfunction_end("%s(...) => %ld", __func__, n);
//                     return n;
//                 }
//                 else if(subscription->enginenode.engine)
//                 {
//                     xint64 n = xdescriptoreventgenerator_descriptor_register(engine->generators.descriptor, descriptor);
//                     n = descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), n == xsuccess);
//                     xlogfunction_end("%s(...) => %ld", __func__, n);
//                     return n;
//                 }
//                 else
//                 {
//                     free(subscription);
//                     descriptor->subscription = xeventengine_descriptor_register(engine, descriptor);
//                     xint64 n = descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xtrue);
//                     xlogfunction_end("%s(...) => %ld", __func__, n);
//                     return n;
//                 }
//             }
//             else
//             {
//                 descriptor->subscription = xeventengine_descriptor_register(engine, descriptor);
//                 xint64 n = descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xtrue);
//                 xlogfunction_end("%s(...) => %ld", __func__, n);
//                 return n;
//             }
//         }
//         else
//         {
//             xlogcaution("");
//             xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
//             return xsuccess;
//         }
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xfail);
//     return xfail;
// }

// extern xint64 xdescriptorunregister(xdescriptor * descriptor)
// {
//     xlogfunction_start("%s(%p)", __func__, descriptor);

//     xdescriptoreventsubscription * subscription = descriptor->subscription;
//     if(subscription)
//     {
//         xdescriptoreventgenerator * generator = subscription->generatornode.generator;
//         if(generator)
//         {
//             xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
//             descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xfalse);
//         }
//     }

//     xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
//     return xsuccess;
// }

// // static xint64 xdescriptoreventprocess_unregister(xdescriptor * descriptor)
// // {

// // }

// // extern xint32 xdescriptorstatuscheck_open(xdescriptor * descriptor)
// // {
// //     if(xdescriptorstatuscheck_close(descriptor))
// //     {
// //         return xfalse;
// //     }
// //     if(descriptor->status & xdescriptorstatus_open)
// //     {
// //         if(descriptor->handle.f >= 0)
// //         {
// //             return xtrue;
// //         }
// //         xassertion(xtrue, "");
// //     }
// //     return xfalse;
// // }

// // extern xint32 xdescriptorstatuscheck_in(xdescriptor * descriptor)
// // {
// //     if(xdescriptorstatuscheck_close(descriptor) || (descriptor->status & xdescriptorstatus_readoff))
// //     {
// //         return xfalse;
// //     }
// //     return descriptor->status & xdescriptorstatus_open;
// // }

// // extern xint32 xdescriptorstatuscheck_out(xdescriptor * descriptor)
// // {
// //     if(xdescriptorstatuscheck_close(descriptor) || (descriptor->status & xdescriptorstatus_writeoff))
// //     {
// //         return xfalse;
// //     }
// //     return descriptor->status & xdescriptorstatus_open;
// // }

// // extern xint32 xdescriptorstatuscheck_close(xdescriptor * descriptor)
// // {
// //     if(descriptor->status & (xdescriptorstatus_close | xdescriptorstatus_exception | xdescriptorstatus_rem))
// //     {
// //         return xtrue;
// //     }
// //     if((descriptor->status & xdescriptorstatus_alloff) == xdescriptorstatus_alloff)
// //     {
// //         return xtrue;
// //     }
// //     if(descriptor->handle.f < 0 && (descriptor->status != xdescriptorstatus_void))
// //     {
// //         return xtrue;
// //     }
// //     return xfalse;
// // }

// // extern xint32 xdescriptorstatuscheck_exception(xdescriptor * descriptor)
// // {
// //     return descriptor->status & xdescriptorstatus_exception;
// // }

// // extern xint32 xdescriptorstatuscheck_rem(xdescriptor * descriptor)
// // {
// //     if((descriptor->status & xdescriptorstatus_rem) == xdescriptorstatus_void)
// //     {
// //         return xfalse;
// //     }
// //     if(descriptor->handle.f >= 0)
// //     {
// //         return xfalse;
// //     }
// //     if(descriptor->event.queue)
// //     {
// //         return xfalse;
// //     }
// //     if(descriptor->status & xdescriptorstatus_register)
// //     {
// //         return xfalse;
// //     }
// //     if(descriptor->subscription->enginenode.engine)
// //     {
// //         return xfalse;
// //     }
// //     if(descriptor->subscription->generatornode.generator)
// //     {
// //         return xfalse;
// //     }
// //     if(descriptor->subscription->generatornode.list)
// //     {
// //         return xfalse;
// //     }
// //     return xtrue;
// // }

// // extern xint32 xdescriptorstatuscheck_register(xdescriptor * descriptor)
// // {
// //     return descriptor->status & xdescriptorstatus_register;
// // }

// // extern xint32 xdescriptorstatuscheck_readoff(xdescriptor * descriptor)
// // {
// //     return descriptor->status & xdescriptorstatus_readoff;
// // }

// // extern xint32 xdescriptorstatuscheck_writeoff(xdescriptor * descriptor)
// // {
// //     return descriptor->status & xdescriptorstatus_writeoff;
// // }

// // extern xint32 xdescriptorstatuscheck_alloff(xdescriptor * descriptor)
// // {
// //     return (descriptor->status & xdescriptorstatus_alloff) == xdescriptorstatus_alloff;
// // }

// // extern xint32 xdescriptorstatuscheck_opening(xdescriptor * descriptor)
// // {
// //     if(xdescriptorstatuscheck_close(descriptor))
// //     {
// //         return xfalse;
// //     }
// //     return descriptor->status & xdescriptorstatus_opening;
// // }

// // extern xint32 xdescriptorstatuscheck_create(xdescriptor * descriptor)
// // {
// //     if(xdescriptorstatuscheck_close(descriptor))
// //     {
// //         return xfalse;
// //     }
// //     return descriptor->status & xdescriptorstatus_create;
// // }

// // extern xint32 xdescriptorstatuscheck_bind(xdescriptor * descriptor)
// // {
// //     if(xdescriptorstatuscheck_close(descriptor))
// //     {
// //         return xfalse;
// //     }
// //     return descriptor->status & xdescriptorstatus_bind;
// // }

// // static xint64 xdescriptoreventprocess_void(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor == xnil, "");

// //     if(xdescriptorstatuscheck_close(descriptor))
// //     {
// //         xdescriptoreventprocess_unregister(descriptor);
// //         xint64 ret = xdescriptoreventprocess_close(descriptor);

// //         xlogfunction_end("%s(...) => %d", __func__, ret);
// //         return ret;
// //     }
// //     if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
// //     {
// //         if((descriptor->status & xdescriptorstatus_opening) == xdescriptorstatus_void)
// //         {
// //             xdescriptoreventprocess_open(descriptor);
// //         }
// //         else
// //         {
// //             xdescriptoreventprocess_opening(descriptor);
// //         }
// //     }

// //     xdescriptoreventprocess_out(descriptor);
// //     xdescriptoreventprocess_in(descriptor);
// //     xdescriptoreventprocess_out(descriptor);

// //     if(xdescriptorstatuscheck_close(descriptor) == xfalse)
// //     {
// //         if((descriptor->status & (xdescriptorstatus_in | xdescriptorstatus_out)) != (xdescriptorstatus_in | xdescriptorstatus_out))
// //         {
// //             xdescriptoreventprocess_register(descriptor);
// //         }
// //     }

// //     if(xdescriptorstatuscheck_close(descriptor))
// //     {
// //         xdescriptoreventprocess_unregister(descriptor);
// //         xdescriptoreventprocess_close(descriptor);
// //         xlogfunction_end("%s(...) => %d", __func__, xfail);
// //         return xfail;
// //     }

// //     xlogfunction_end("%s(...) => %d", __func__, xsuccess);
// //     return xsuccess;
// // }

// // static xint64 xdescriptoreventprocess_open(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_open, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_in(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_in, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_out(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_out, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_close(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");
// //     xassertion(descriptor->event.queue, "");
// //     xassertion(descriptor->status & xdescriptorstatus_register, "");

// //     xdescriptoreventsubscription *  subscription = descriptor->subscription;
// //     if(subscription)
// //     {
// //         xdescriptoreventgenerator * generator = subscription->generatornode.generator;
// //         if(subscription->generatornode.list == generator->alive)
// //         {
// //             xdescriptoreventgeneratorsubscriptionlist_del(descriptor->subscription);
// //         }
// //         descriptor->process(descriptor, xdescriptoreventtype_close, xdescriptorparamgen(xnil));

// //         descriptor->exception = xexception_void;
// //         descriptor->status    = (descriptor->status & xdescriptorstatus_rem) ? xdescriptorstatus_rem : xdescriptorstatus_void;

// //         if(subscription->generatornode.list != generator->queue)
// //         {
// //             xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
// //         }
// //     }
// //     else
// //     {
// //         descriptor->process(descriptor, xdescriptoreventtype_close, xdescriptorparamgen(xnil));
// //     }

// //     xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
// //     return xsuccess;
// // }

// // static xint64 xdescriptoreventprocess_exception(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_exception, xdescriptorparamgen(xnil));

// //     n = xdescriptoreventprocess_close(descriptor);

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_rem(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);
// //     if(xdescriptorstatuscheck_rem(descriptor))
// //     {
// //         xdescriptoreventsubscription * subscription = descriptor->subscription;
// //         if(subscription)
// //         {
// //             xeventengine * engine = subscription->enginenode.engine;
// //             xeventengine_descriptor_unregister(engine, descriptor);

// //             // TODO: CHECK SUBSCRIPTION
// //             xassertion(subscription->enginenode.engine || subscription->enginenode.prev || subscription->enginenode.next, "");
// //             xassertion(subscription->generatornode.prev || subscription->generatornode.next || subscription->generatornode.list, "");

// //             descriptor->subscription = xnil;
// //             descriptor->process(descriptor, xdescriptoreventtype_rem, xdescriptorparamgen(xnil));
// //             free(subscription);
// //         }
// //         else
// //         {
// //             descriptor->process(descriptor, xdescriptoreventtype_rem, xdescriptorparamgen(xnil));
// //         }
// //     }
// //     else
// //     {
// //         xassertion((descriptor->status & xdescriptorstatus_rem) == xdescriptorstatus_void, "");
// //         xdescriptoreventsubscription * subscription = descriptor->subscription;
// //         xdescriptoreventgenerator * generator = subscription->generatornode.generator;
// //         xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
// //     }
// //     xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
// //     return xsuccess;
// // }



// // static xint64 xdescriptoreventprocess_readoff(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_readoff, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_writeoff(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_writeoff, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_opening(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_opening, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_create(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_create, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_bind(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_bind, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_alloff(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_alloff, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_connect(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_connect, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_listen(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_listen, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_connecting(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xassertion(descriptor->process == xnil, "");

// //     xint64 n = descriptor->process(descriptor, xdescriptoreventtype_connecting, xdescriptorparamgen(xnil));

// //     xlogfunction_end("%s(...) => %ld", __func__, n);
// //     return n;
// // }

// // static xint64 xdescriptoreventprocess_unregister(xdescriptor * descriptor)
// // {
// //     xlogfunction_start("%s(%p)", __func__, descriptor);

// //     xdescriptoreventsubscription * subscription = descriptor->subscription;
// //     xdescriptoreventgenerator * generator = subscription->generatornode.generator;
// //     xdescriptoreventgenerator_descriptor_unregister(generator, descriptor);
// //     descriptor->on(descriptor, xdescriptoreventtype_register, xdescriptorparamgen(xnil), xfalse);

// //     xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
// //     return xsuccess;
// // }

// // extern xuint32 xdescriptorstatus_get(xdescriptor * descriptor)
// // {
// //     return descriptor->status;
// // }

// // extern xdescriptoreventsubscription * xdescriptoreventsubscription_get(xdescriptor * descriptor)
// // {
// //     return descriptor->subscription;
// // }

// // extern const char * xdescriptoreventtype_str(xuint32 event)
// // {
// //     switch(event)
// //     {
// //     case xdescriptoreventtype_void:         return "void";
// //     case xdescriptoreventtype_open:         return "open";
// //     case xdescriptoreventtype_in:           return "in";
// //     case xdescriptoreventtype_out:          return "out";
// //     case xdescriptoreventtype_close:        return "close";
// //     case xdescriptoreventtype_exception:    return "exception";
// //     case xdescriptoreventtype_rem:          return "rem";
// //     case xdescriptoreventtype_register:     return "register";
// //     case xdescriptoreventtype_flush:        return "flush";
// //     case xdescriptoreventtype_readoff:      return "readoff";
// //     case xdescriptoreventtype_writeoff:     return "writeoff";
// //     case xdescriptoreventtype_opening:      return "opening";
// //     case xdescriptoreventtype_create:       return "create";
// //     case xdescriptoreventtype_bind:         return "bind";
// //     case xdescriptoreventtype_alloff:       return "alloff";
// //     default: xassertion(xtrue, "");         return "unknown";
// //     }

// // }
// 