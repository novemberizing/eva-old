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

#define xserversocketeventtype_open     xdescriptoreventtype_open
#define xserversocketeventtype_in       xdescriptoreventtype_in
#define xserversocketeventtype_out      xdescriptoreventtype_out
#define xserversocketeventtype_close    xdescriptoreventtype_close
#define xserversocketeventtype_register xdescriptoreventtype_register

#define xserversocketstatus_void        xsocketstatus_void
#define xserversocketstatus_open        xsocketstatus_open
#define xserversocketstatus_in          xsocketstatus_in
#define xserversocketstatus_out         xsocketstatus_out
#define xserversocketstatus_close       xsocketstatus_close
#define xserversocketstatus_exception   xsocketstatus_exception
#define xserversocketstatus_rem         xsocketstatus_rem
#define xserversocketstatus_register    xsocketstatus_register

#define xserversocketstatus_create      xsocketstatus_create
#define xserversocketstatus_bind        xsocketstatus_bind
// #define xserversocketstatus_connect     xsocketstatus_connect
// #define xserversocketstatus_connecting  xsocketstatus_connecting
#define xserversocketstatus_listen      xsocketstatus_listen

typedef xserversocket * (*xserversocketdestructor)(xserversocket *);
typedef xint64 (*xserversocketprocessor)(xserversocket *, xuint32, void *);
typedef xint64 (*xserversocketsubscriber)(xserversocket *, xuint32, void *, xint64);
typedef xint32 (*xserversocketcheck)(xserversocket *, xuint32);

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
    xserversocketcheck               check;         /**!< descriptor status checker  */
    xserversocketsubscriber          on;            /**!< descriptor event subscriber */
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

extern xint32 xserversocketcheck_open(xserversocket * descriptor);
extern xint32 xserversocketcheck_rem(xserversocket * descriptor);
extern void xserversocketbacklog_set(xserversocket * descriptor, xint32 backlog);
// 
// extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen);
// extern xclientsocket * xclientsocket_rem(xclientsocket * o);

#endif // __NOVEMBERIZING_X__SERVER__SOCKET__H__
