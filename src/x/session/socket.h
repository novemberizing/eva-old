#ifndef   __NOVEMBERIZING_X__SESSION__SOCKET__H__
#define   __NOVEMBERIZING_X__SESSION__SOCKET__H__

#include <x/io.h>
#include <x/session.h>

#include <x/exception.h>
#include <x/socket/stream.h>
#include <x/descriptor/handle.h>
#include <x/session/socket/event.h>
#include <x/session/socket/event/subscription.h>

typedef xsessionsocket * (*xsessionsocketdestructor)(xsessionsocket *);
typedef xint64 (*xsessionsocketprocessor)(xsessionsocket *, xuint32);
typedef xint64 (*xsessionsocketobserver)(xsessionsocket *, xuint32, xdescriptorparam, xint64);
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
    xsessionsocketobserver on;
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

// extern xstream * xsessionsocketstreamin_get(xsessionsocket * descriptor);
// extern void xsessionsocketstreamin_del(xsessionsocket * descriptor);
// extern xstream * xsessionsocketstreamin_set(xsessionsocket * descriptor, xstream * stream);
// extern xstream * xsessionsocketstreamout_get(xsessionsocket * descriptor);
// extern void xsessionsocketstreamout_del(xsessionsocket * descriptor);
// extern xstream * xsessionsocketstreamout_set(xsessionsocket * descriptor, xstream * stream);

#endif // __NOVEMBERIZING_X__SESSION__SOCKET__H__
