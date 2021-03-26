#ifndef   __NOVEMBERIZING_X__SOCKET__H__
#define   __NOVEMBERIZING_X__SOCKET__H__

#include <x/io.h>
#include <x/sync.h>
#include <x/exception.h>

#include <x/descriptor/handle.h>

#include <x/socket/event.h>
#include <x/socket/event/type.h>
#include <x/socket/event/subscription.h>

typedef xint64 (*xsocketprocessor)(xsocket *, xuint32, xdescriptorparam);
typedef xint64 (*xsocketobserver)(xsocket *, xuint32, xdescriptorparam, xint64);
typedef xint32 (*xsocketstatuschecker)(xsocket *, xuint32);

struct xsocket
{
    /** INHERITED EVENT TARGET */
    xsocketdestructor          rem;             /**!< destructor */
    xsocketeventsubscription * subscription;    /**!< subscription */
    xsync *                    sync;            /**!< synchronization */
    xuint32                    mask;            /**!< mask */
    xuint32                    status;          /**!< status */
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle          handle;          /**!< descriptor handle */
    xsocketprocessor           process;         /**!< descriptor process function */
    xsocketstatuschecker       check;           /**!< descriptor status checker  */
    xsocketobserver            on;              /**!< descriptor event subscriber */
    xsocketevent               event;           /**!< descriptor default event */
    xexception                 exception;       /**!< descriptor exception */
    /** SOCKET MEMBER */
    xint32                     domain;          /**!< domain */
    xint32                     type;            /**!< type */
    xint32                     protocol;        /**!< protocol */
};

extern xint64 xsocketcreate(xsocket * o);
extern xint64 xsocketbind(xsocket * o, void * addr, xuint32 addrlen);
extern xint64 xsocketshutdown(xsocket * o, xuint32 how);

extern xint32 xsocketresuseaddr(xsocket * o, xint32 on);
extern xint32 xsocketnodelay(xsocket * o, xint32 on);
extern xint32 xsocketerror(xsocket * o);

// extern xint64 xsocketlisten(xsocket * o, xint32 backlog);   // MOVE TO SERVER SOCKET
// extern xint64 xsocketconnect(xsocket * o, void * addr, xuint32 addrlen);    // MOVE TO CLIENT SOCKTE

#endif // __NOVEMBERIZING_X__SOCKET__H__
