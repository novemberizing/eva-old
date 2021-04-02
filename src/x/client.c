#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
       
#include <signal.h>
#include <poll.h>

#include "thread.h"

#include "socket.h"

#include "descriptor/event/avail.h"

#include "client.h"
#include "client/pool.h"
#include "client/socket.h"
#include "client/socket/status.h"

#include "res.h"

static const xuint64 streambuffersize = 8192;

extern xclient * xclientnew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xclientobserver on, xuint64 size)
{
    xassertion(size < sizeof(xclient), "");

    xclient * client = (xclient *) calloc(size, 1);

    client->descriptor = xclientsocket_new(client, domain, type, protocol, addr, addrlen);
    client->on         = on;

    client->pool       = xnil;
    client->prev       = xnil;
    client->next       = xnil;
    
    return client;
}

extern xclient * xclientrem(xclient * client)
{
    if(client)
    {
        client->descriptor = client->descriptor->rem(client->descriptor);

        xclientpooldel(client);

        free(client);
    }

    return xnil;
}

extern xint64 xclientconnect(xclient * client)
{
    xclientsocket * o = client->descriptor;

    if(o->subscription == xnil)
    {
        xsocketcreate((xsocket *) o);
        xclientsocketconnect(o, o->addr, o->addrlen);

        return xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse && (o->status & (xsocketstatus_connect | xsocketstatus_connecting));
    }
    else
    {
        xassertion(xtrue, "");
        return xsuccess;
    }
}

extern xint64 xclientread(xclient * client)
{
    return xdescriptorstreamread((xdescriptor *) client->descriptor, client->descriptor->stream.in, streambuffersize);
}

extern xint64 xclientwrite(xclient * client)
{
    return xdescriptorstreamwrite((xdescriptor *) client->descriptor, client->descriptor->stream.out);
}

extern xint64 xclientclose(xclient * client)
{
    return xdescriptorclose((xdescriptor *) client->descriptor);
}

extern xint64 xclientsend(xclient * client, const char * data, xuint64 len)
{
    if(xdescriptorstatuscheck_open((xdescriptor *) client->descriptor))
    {
        xstreampush(client->descriptor->stream.out, data, len);
        return xdescriptorstreamwrite((xdescriptor *) client->descriptor, client->descriptor->stream.out);
    }

    return xfail;
}

extern xint64 xclientrecv(xclient * client, char * buffer, xuint64 size)
{
    if(xdescriptorstatuscheck_open((xdescriptor *) client->descriptor))
    {
        return xdescriptorstreamread((xdescriptor *) client->descriptor, client->descriptor->stream.in, streambuffersize);
    }

    return xfail;
}

extern xint64 xclientsendf(xclient * client, xstringserializer serialize, const char * format, ...)
{
//    xassertion(xtrue, "implement this");

    xclientsocket * o = client->descriptor;
    if(xdescriptoreventavail_in((xdescriptor *) o))
    {
        va_list ap;
        va_start(ap, format);
        xstreamformatv(o->stream.out, serialize, format, ap);
        va_end(ap);

        return xdescriptorstreamwrite((xdescriptor *) o, o->stream.out);
        
    }
    
    return xdescriptorstatuscheck_close((xdescriptor *) o) ? xfail : xsuccess;
    
}

extern xstream * xclientstreamin_get(xclient * client)
{
    return client->descriptor->stream.in;
}

extern xstream * xclientstreamout_get(xclient * client)
{
    return client->descriptor->stream.out;
}

extern xres * xclientreq(xclient * client, xreq * req)
{
    xassertion(client == xnil || req == xnil, "");
    xassertion(client->descriptor == xnil, "");
    xassertion(client->descriptor->subscription && client->descriptor->subscription->enginenode.engine, "");
    xassertion(xstreamlen(client->descriptor->stream.out) > 0, "");

    xstream * out = client->descriptor->stream.out;

    req->start    = xtimeget();
    xuint64 start = xstreamsize_get(out);
    xuint64 end   = start + req->serialize(req, out);
    xint64 ret    = 0;

    xuint64 len   = xstreamlen(out);

    while(xstreamlen(out) > 0 && ret >= 0)
    {
        xbyte * front = xstreamfront(out);
        ret = xdescriptorwrite((xdescriptor *) client->descriptor, front, xstreamlen(out));

        if(ret > 0)
        {
            xstreampos_set(out, xstreampos_get(out) + ret);

            ret = xdescriptoron((xdescriptor *) client->descriptor, xdescriptoreventtype_out, xdescriptorparamgen(front), ret);
        }
    }

    req->end      = xtimeget();

    if(xdescriptorstatuscheck_close((xdescriptor *) client->descriptor) == xfalse)
    {
        xstreamadjust(out, streambuffersize, xfalse);  // capacity reset ... 

        return req->gen(req);
    }

    return xnil;
}

extern void xclientmask_add(xclient * client, xuint32 mask)
{
    client->descriptor->mask |= mask;
}

extern xuint32 xclientwait(xclient * client, xuint32 status, xint64 millisecond)
{
    xuint32 result = xsocketstatus_void;

    if(xdescriptorstatuscheck_close((xdescriptor *) client->descriptor) == xfalse)
    {
        struct pollfd pfd;
        pfd.fd = client->descriptor->handle.f;
        pfd.events = (POLLPRI | POLLRDHUP | POLLHUP | POLLERR | POLLNVAL);
        pfd.revents = 0;

        if(status == xdescriptorstatus_open)
        {
            if(client->descriptor->status & xdescriptorstatus_open)
            {
                return xdescriptorstatus_open;
            }

            pfd.events |= POLLOUT;
        }
        else if(status == xdescriptorstatus_in)
        {
            pfd.events |= POLLIN;
        }

        int nfds = poll(xaddressof(pfd), 1, millisecond);

        if(nfds == 1)
        {
            if(status == xdescriptorstatus_open)
            {
                xint32 code = xsocketerror((xsocket *) client->descriptor);

                if(code == xsuccess)
                {
                    client->descriptor->status &= (~xdescriptorstatus_connecting);
                    client->descriptor->status |= (xdescriptorstatus_open | xdescriptorstatus_connect | xdescriptorstatus_out);
                    if(xdescriptoron((xdescriptor *) client->descriptor, xdescriptoreventtype_open, xdescriptorparamgen(xnil), xsuccess) == xsuccess)
                    {
                        if(client->descriptor->stream.in == xnil)
                        {
                            client->descriptor->stream.in = xstreamnew(xstreamtype_buffer);
                        }
                        if(client->descriptor->stream.out == xnil)
                        {
                            client->descriptor->stream.out = xstreamnew(xstreamtype_buffer);
                        }
                        return xdescriptorstatus_open;
                    }
                }
                else
                {
                    if((client->descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
                    {
                        if(code != EAGAIN && errno != EINPROGRESS)
                        {
                            xdescriptorexception((xdescriptor *) client->descriptor, connect, code, xexceptiontype_sys, "");
                        }
                        else
                        {
                            return xdescriptorstatus_open;
                        }
                    }
                }
                return xdescriptorstatus_void;
            }
            else if(status == xdescriptorstatus_in)
            {
                if(pfd.revents & (POLLPRI | POLLRDHUP | POLLHUP | POLLERR | POLLNVAL))
                {
                    return xdescriptorstatus_void;
                }
                if(pfd.revents & POLLIN)
                {
                    return xdescriptorstatus_in;
                }
            }
        }
    }

    return xdescriptorstatus_void;
}

extern xres * xclientwaitres(xclient * client, xres * res, xint64 millisecond)
{
    xdescriptor * descriptor = (xdescriptor *) client->descriptor;
    xstream * stream = client->descriptor->stream.in;
    // response -> 
    xuint64 capacity = 8192;

    while((res->status & xresponsestatus_complete) == xresponsestatus_void && xdescriptorstatuscheck_close(descriptor) == xfalse)
    {
        if(xclientwait(client, xdescriptorstatus_in, millisecond) == xdescriptorstatus_in)
        {
            if(xstreamremain(stream) < capacity)
            {
                xstreamcapacity_set(stream, xstreamcapacity_get(stream) + capacity - xstreamremain(stream));
            }

            xbyte * back = xstreamback(stream);

            xint64 ret = xdescriptorread(descriptor, xstreamback(stream), res->predict(res, xstreamlen(stream)));

            if(ret > 0)
            {
                xstreamsize_set(stream, xstreamsize_get(stream) + ret);

                xdescriptoron(descriptor, xdescriptoreventtype_in, xdescriptorparamgen(back), ret);

                ret = res->deserialize(res, stream);

                if(ret > 0)
                {
                    xstreampos_set(stream, xstreampos_get(stream) + ret);
                }
                else if(ret < 0)
                {
                    res->status |= xresponsestatus_exception;
                    xdescriptorexception(descriptor, res->deserialize, ret, xexceptiontype_user, "");
                }
            }
        }

        if(millisecond < 0)
        {
            res->status |= xresponsestatus_timeout;
            break;
        }
    }

    

    return res;
}