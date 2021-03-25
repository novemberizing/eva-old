#ifndef   __NOVEMBERIZING_X__CLIENT__SOCKET__H__
#define   __NOVEMBERIZING_X__CLIENT__SOCKET__H__

#include <x/std.h>
#include <x/socket.h>
#include <x/socket/stream.h>

#include <x/client.h>
#include <x/client/socket/event.h>
#include <x/client/socket/event/subscription.h>


struct xclientsocket;

typedef struct xclientsocket xclientsocket;

typedef xclientsocket * (*xclientsocketdestructor)(xclientsocket *);
typedef xint64 (*xclientsocketprocessor)(xclientsocket *, xuint32);
typedef xint64 (*xclientsocketobserver)(xclientsocket *, xuint32, xdescriptorparam, xint64);
typedef xint32 (*xclientsocketchecker)(xclientsocket *, xuint32);

struct xclientsocket
{
    /** INHERITED EVENT TARGET */
    xclientsocketdestructor          rem;           /**!< destructor */
    xclientsocketeventsubscription * subscription;  /**!< subscription */
    xsync *                          sync;          /**!< synchronization */
    xuint32                          mask;          /**!< mask */
    xuint32                          status;        /**!< status */
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle                handle;        /**!< descriptor handle */
    xclientsocketprocessor           process;       /**!< descriptor process function */
    xclientsocketchecker             check;         /**!< descriptor status checker  */
    xclientsocketobserver            on;            /**!< descriptor event subscriber */
    xclientsocketevent               event;         /**!< descriptor default event */
    xexception                       exception;     /**!< descriptor exception */
    /** SOCKET MEMBER */
    xint32                           domain;        /**!< domain */
    xint32                           type;          /**!< type */
    xint32                           protocol;      /**!< protocol */
    /** CLIENT SOCKET MEMBER */
    void *                           addr;          /**!< address */
    xuint32                          addrlen;       /**!< address length */
    xsocketstream                    stream;        /**!< socket input/output stream */
    xclient *                        client;        /**!< client */
};

extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen);
extern xclientsocket * xclientsocket_rem(xclientsocket * o);

extern xint64 xclientsocketconnect(xclientsocket * o, void * addr, xuint32 addrlen);
extern xint64 xclientsocketclear(xclientsocket * o);


#endif // __NOVEMBERIZING_X__CLIENT__SOCKET__H__
