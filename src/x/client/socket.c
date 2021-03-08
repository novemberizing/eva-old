#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>

#include "../thread.h"
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

extern xclientsocket * xclientsocket_rem(xclientsocket * o)
{
    // /** INHERITED EVENT TARGET */
    // xclientsocketdestructor          rem;           /**!< destructor */
    // xclientsocketeventsubscription * subscription;  /**!< subscription */
    // xsync *                          sync;          /**!< synchronization */
    // xuint32                          mask;          /**!< mask */
    // xuint32                          status;        /**!< status */
    // /** DESCRIPTOR EVENT HANDLE */
    // xdescriptorhandle                handle;        /**!< descriptor handle */
    // xclientsocketprocessor           process;       /**!< descriptor process function */
    // xclientsocketcheck               check;         /**!< descriptor status checker  */
    // xclientsocketsubscriber          on;            /**!< descriptor event subscriber */
    // xclientsocketevent               event;         /**!< descriptor default event */
    // xexception                       exception;     /**!< descriptor exception */
    // /** SOCKET MEMBER */
    // xint32                           domain;        /**!< domain */
    // xint32                           type;          /**!< type */
    // xint32                           protocol;      /**!< protocol */
    // /** CLIENT SOCKET MEMBER */
    // void *                           addr;          /**!< address */
    // xuint32                          addrlen;       /**!< address length */
    // xsocketstream                    stream;        /**!< socket input/output stream */
    // xclient *                        client;        /**!< client */

    return xnil;
}

static xint64 xclientsocketprocessor_tcp(xclientsocket * o, xuint32 event, void * parameter)
{
    xassertion(xtrue, "implement this");
    return xfail;
}

static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * parameter, xint64 result)
{
    xassertion(xtrue, "implement this");
    return xfail;
}

static xint32 xclientsocketcheck_tcp(xclientsocket * o, xuint32 event)
{
    xassertion(xtrue, "implement this");
    return xfail;
}

static void xclientsocketeventhandler_tcp(xclientsocketevent * event)
{
    xassertion(xtrue, "implement this");
}
