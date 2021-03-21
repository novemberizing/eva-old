#include "tcp.h"

typedef xint64 (*xserversocketfunc)(xserversocket * o);

static xint64 xserversocketprocess(xserversocket * o);      // 0
static xint64 xserversocketopen(xserversocket * o);         // 1
static xint64 xserversocketaccept(xserversocket * o);       // 2

static xint64 xserversocketclose(xserversocket * o);        // 4
static xint64 xserversocketexception(xserversocket * o);    // 5
static xint64 xserversocketrem(xserversocket * o);          // 6
static xint64 xserversocketregister(xserversocket * o);     // 7
static xint64 xserversocketreadoff(xserversocket * o);      // 9
static xint64 xserversocketwriteoff(xserversocket * o);     // 10
static xint64 xserversocketcreate(xserversocket * o);       // 12
static xint64 xserversocketbind(xserversocket * o);         // 13
static xint64 xserversocketclear(xserversocket * o);        // 14
static xint64 xserversocketalloff(xserversocket * o);       // 15
static xint64 xserversocketlisten(xserversocket * o);       // 17
static xint64 xserversocketunregister(xserversocket * o);   // 19

static xserversocketfunc processors[20] = {
    xserversocketprocess,           // 0 
    xserversocketopen,              // 1
    xserversocketaccept,            // 2
    xnil,                           // 3
    xserversocketclose,             // 4
    xserversocketexception,         // 5
    xserversocketrem,               // 6
    xserversocketregister,          // 7
    xnil,                           // 8
    xserversocketreadoff,           // 9
    xserversocketwriteoff,          // 10
    xnil,                           // 11
    xserversocketcreate,            // 12
    xserversocketbind,              // 13
    xserversocketclear,             // 14
    xserversocketalloff,            // 15
    xnil,                           // 16
    xserversocketlisten,            // 17
    xnil,                           // 18
    xserversocketunregister         // 19
};

extern xint64 xsocketprocessortcp_server(xserversocket * o, xuint32 event, xdescriptorparam param)
{
    xlogfunction_start("%s(%p, %u, %p)", __func__, o, event, param.p);



    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

static xint64 xserversocketprocess(xserversocket * o)
{
    xlogfunction_start("%s(%p, %u, %p)", __func__, o);
    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xserversocketunregister(o);
        xserversocketclose(o);
        return xsuccess;
    }

    xserversocketopen(o);
    xserversocketaccept(o);
    xserversocketregister(o);

    if(xdescriptorstatuscheck_close((xdescriptor *) o))
    {
        xserversocketunregister(o);
        xserversocketclose(o);
    }
    xlogfunction_end("%s(...) => %ld", __func__, xsuccess);
    return xsuccess;
}

static xint64 xserversocketopen(xserversocket * o)
{
    xlogfunction_start("%s(%p, %u, %p)", __func__);
    xint64 ret = xfail;
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->status & xsocketstatus_open)
        {
            ret = xsuccess;
        }
        else if(o->status & xsocketstatus_opening)
        {
            xassertion(xtrue, "");  // 서버 소켓은 오프닝 상태를 허용하지 않는다. 비동기 업셉트만 
        }
        else
        {
            if(xsocketcreate((xsocket *) o) == xsuccess)
            {
                if(xsocketbind((xsocket *) o, o->addr, o->addrlen) == xsuccess)
                {
                    if(xsocketlisten((xsocket *) 0, o->backlog) == xsuccess)
                    {
                        ret = xsuccess;
                    }
                }
            }
        }
    }
    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

static xint64 xserversocketaccept(xserversocket * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xint64 ret = xfail;
    if(xdescriptorstatuscheck_close((xdescriptor *) o) == xfalse)
    {
        if(o->status & xsocketstatus_open)
        {
            xint32 f = accept(o->handle.f, xnil, xnil);
            if(f >= 0)
            {

            }
            else
            {
                // EAGAIN,

                // EFALUT
                // EMFILE
                // ENFILE
                // ENOBUFS, ENOMEM
                // EPERM


       ENOTSOCK
              The file descriptor sockfd does not refer to a socket.

       EOPNOTSUPP
              The referenced socket is not of type SOCK_STREAM.

       EPROTO Protocol error.

       In addition, Linux accept() may fail if:

       EPERM  Firewall rules forbid connection.

       In addition, network errors for the new socket and as defined for the protocol may be returned.  Various Linux kernels can return other errors such as ENOSR, ESOCKTNOSUPPORT, EPROTONOSUPPORT, ETIMEDOUT.  The value ERESTARTSYS
       may be seen during a trace.
            }
            xsessionsocket * descriptor = xsessionsocket_n
            // session descriptor
            // o->create()
        }
        else
        {
            xassertion((o->status & xsocketstatus_open) == xsocketstatus_void, "");
        }
    }
    xlogfunction_end("%s(...) => %ld", __func__, ret);
    return ret;
}

static xint64 xserversocketclose(xserversocket * o);        // 4
static xint64 xserversocketexception(xserversocket * o);    // 5
static xint64 xserversocketrem(xserversocket * o);          // 6
static xint64 xserversocketregister(xserversocket * o);     // 7
static xint64 xserversocketreadoff(xserversocket * o);      // 9
static xint64 xserversocketwriteoff(xserversocket * o);     // 10
static xint64 xserversocketcreate(xserversocket * o);       // 12
static xint64 xserversocketbind(xserversocket * o);         // 13
static xint64 xserversocketclear(xserversocket * o);        // 14
static xint64 xserversocketalloff(xserversocket * o);       // 15
static xint64 xserversocketlisten(xserversocket * o);       // 17
static xint64 xserversocketunregister(xserversocket * o);   // 19