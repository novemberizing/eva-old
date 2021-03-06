#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "socket.h"

static xint64 xclientsocketprocessor_tcp(xclientsocket * o, xuint32 event, void * parameter);
static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * parameter, xint64 result);
static xint32 xclientsocketcheck_tcp(xclientsocket * o, xuint32 event);
static void xclientsocketeventhandler_tcp(xclientsocketevent * event);

extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xclientsocket * o = (xclientsocket *) calloc(sizeof(xclientsocket), 1);

    o->rem              = xclientsocket_rem;
    o->handle.f         = xinvalid;
    o->process          = xclientsocketprocessor_tcp;
    o->check            = xclientsocketcheck_tcp;
    o->on               = xclientsocketsubscriber_tcp;
    o->event.descriptor = o;
    o->event.on         = xclientsocketeventhandler_tcp;
    o->domain           = domain;
    o->type             = type;
    o->protocol         = protocol;
    o->addr             = xobjectdup(addr, addrlen);
    o->addrlen          = addrlen;
    o->client           = client;

    return o;
}