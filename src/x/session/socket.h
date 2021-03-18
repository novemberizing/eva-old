#ifndef   __NOVEMBERIZING_X__SESSION__SOCKET__H__
#define   __NOVEMBERIZING_X__SESSION__SOCKET__H__

#include <x/session.h>

#include <x/exception.h>
#include <x/socket/stream.h>
#include <x/descriptor/handle.h>
#include <x/session/socket/event.h>
#include <x/session/socket/event/subscription.h>

#define xsessionsocketeventtype_open        xdescriptoreventtype_open
#define xsessionsocketeventtype_in          xdescriptoreventtype_in
#define xsessionsocketeventtype_out         xdescriptoreventtype_out
#define xsessionsocketeventtype_close       xdescriptoreventtype_close
#define xsessionsocketeventtype_exception   xdescriptoreventtype_exception

#define xsessionsocketstatus_void           xsocketstatus_void
#define xsessionsocketstatus_open           xsocketstatus_open
#define xsessionsocketstatus_in             xsocketstatus_in
#define xsessionsocketstatus_out            xsocketstatus_out
#define xsessionsocketstatus_close          xsocketstatus_close
#define xsessionsocketstatus_exception      xsocketstatus_exception
#define xsessionsocketstatus_rem            xsocketstatus_rem
#define xsessionsocketstatus_register       xsocketstatus_register

#define xsessionsocketstatus_create         xsocketstatus_create
#define xsessionsocketstatus_bind           xsocketstatus_bind
// #define xserversocketstatus_connect     xsocketstatus_connect
// #define xserversocketstatus_connecting  xsocketstatus_connecting
#define xsessionsocketstatus_listen         xsocketstatus_listen

typedef xsessionsocket * (*xsessionsocketdestructor)(xsessionsocket *);
typedef xint64 (*xsessionsocketprocessor)(xsessionsocket *, xuint32, void *);
typedef xint64 (*xsessionsocketsubscriber)(xsessionsocket *, xuint32, void *, xint64);
typedef xint32 (*xsessionsocketchecker)(xsessionsocket *, xuint32);

struct xsessionsocket
{
    /** INHERITED EVENT TARGET */
    xsessionsocketdestructor rem;
    xsessionsocketeventsubscription * subscription;
    xsync * sync;
    xuint32 mask;
    xuint32 status;
    /** DESCRIPTOR EVENT HANDLER */
    xdescriptorhandle handle;
    xsessionsocketprocessor process;
    xsessionsocketchecker check;
    xsessionsocketsubscriber on;
    xsessionsocketevent event;
    xexception exception;
    /** INHERITED SOCKET */
    xint32 domain;
    xint32 type;
    xint32 protocol;
    /** SESSION SOCKET MEMBER */
    xsocketstream stream;
    xsession * session;
};

extern xsessionsocket * xsessionsocket_new(xint32 domain, xint32 type, xint32 protocol);
extern xsessionsocket * xsessionsocket_rem(xsessionsocket * descriptor);

extern xstream * xsessionsocketstreamin_get(xsessionsocket * descriptor);
extern void xsessionsocketstreamin_del(xsessionsocket * descriptor);
extern xstream * xsessionsocketstreamin_set(xsessionsocket * descriptor, xstream * stream);
extern xstream * xsessionsocketstreamout_get(xsessionsocket * descriptor);
extern void xsessionsocketstreamout_del(xsessionsocket * descriptor);
extern xstream * xsessionsocketstreamout_set(xsessionsocket * descriptor, xstream * stream);

#endif // __NOVEMBERIZING_X__SESSION__SOCKET__H__
