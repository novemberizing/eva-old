#ifndef   __NOVEMBERIZING_X__SERVER__SOCKET__H__
#define   __NOVEMBERIZING_X__SERVER__SOCKET__H__

#include <x/io.h>
#include <x/server.h>
#include <x/sync.h>
#include <x/exception.h>

#include <x/descriptor/handle.h>

#include <x/socket/stream.h>

#include <x/server/socket/event.h>
#include <x/server/socket/event/subscription.h>

extern const char * xserversocketeventtype_str(xuint32 event);

typedef xserversocket * (*xserversocketdestructor)(xserversocket *);
typedef xint64 (*xserversocketprocessor)(xserversocket *, xuint32);
typedef xint64 (*xserversocketobserver)(xserversocket *, xuint32, xdescriptorparam, xint64);
typedef xint32 (*xserversocketchecker)(xserversocket *, xuint32);

struct xserversocket
{
    /** INHERITED EVENT TARGET */
    xserversocketdestructor          rem;           /**!< destructor */
    xserversocketeventsubscription * subscription;  /**!< subscription */
    xsync *                          sync;          /**!< synchronization */
    xuint32                          mask;          /**!< mask */
    xuint32                          status;        /**!< status */
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle                handle;        /**!< descriptor handle */
    xserversocketprocessor           process;       /**!< descriptor process function */
    xserversocketchecker             check;         /**!< descriptor status checker  */
    xserversocketobserver            on;            /**!< descriptor event subscriber */
    xserversocketevent               event;         /**!< descriptor default event */
    xexception                       exception;     /**!< descriptor exception */
    /** INHERITED SOCKET */
    xint32                           domain;        /**!< domain */
    xint32                           type;          /**!< type */
    xint32                           protocol;      /**!< protocol */
    /** SERVER SOCKET MEMBER */
    void *                           addr;          /**!< address */
    xuint32                          addrlen;       /**!< address length */
    xint32                           backlog;       /**!< backlog */
    xserver *                        server;        /**!< parent server reference */
};

extern xserversocket * xserversocket_new(xserver * server, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen);
extern xserversocket * xserversocket_rem(xserversocket * descriptor);


// extern xint32 xserversocketcheck_open(xserversocket * descriptor);
// extern xint32 xserversocketcheck_rem(xserversocket * descriptor);

// extern void xserversocketbacklog_set(xserversocket * descriptor, xint32 backlog);


#endif // __NOVEMBERIZING_X__SERVER__SOCKET__H__
