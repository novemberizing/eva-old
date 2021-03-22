#ifndef   __NOVEMBERIZING_X__SESSION__H__
#define   __NOVEMBERIZING_X__SESSION__H__

#include <x/io.h>

#include <x/stream.h>
#include <x/socket.h>
#include <x/session/list.h>

#define xsessioneventtype_open      xsocketeventtype_open
#define xsessioneventtype_in        xsocketeventtype_in
#define xsessioneventtype_out       xsocketeventtype_out
#define xsessioneventtype_close     xsocketeventtype_close

struct xsession;
struct xsessionsocket;

typedef struct xsession xsession;
typedef struct xsessionsocket xsessionsocket;

typedef xint64 (*xsessionobserver)(xsession *, xuint32, xdescriptorparam, xint64);

typedef xsession * (*xsessionfactory)(xserver *, xint32, xint32, xint32);
typedef void (*xsessionreleaser)(xsession *);

struct xsession
{
    xsessionsocket * descriptor;

    xserver * server;

    xsession * prev;
    xsession * next;
    xsessionlist * cntr;
};

#endif // __NOVEMBERIZING_X__SESSION__H__
