/**
 * @todo        문서화
 *              외부/내부 소스를 나누자.
 */
#ifndef   __NOVEMBERIZING_X__IO__H__
#define   __NOVEMBERIZING_X__IO__H__

#include <x/std.h>
#include <x/sync.h>

#define xtransmissioncontrolprotocol    1
#define xuserdatagramprotocol           2

struct xdescriptor;

typedef struct xdescriptor xdescriptor;

struct xclient;
struct xserver;
struct xsession;
struct xclientsocket;
struct xserversocket;
struct xsessionsocket;
struct xsocket;
struct xclientpool;

struct xdescriptoreventgenerator;
struct xdescriptoreventgeneratorsubscriptions;
struct xdescriptoreventsubscription;


typedef struct xdescriptoreventgenerator xdescriptoreventgenerator;
typedef struct xdescriptoreventsubscription xdescriptoreventsubscription;
typedef struct xdescriptoreventgeneratorsubscriptions xdescriptoreventgeneratorsubscriptions;
typedef struct xclient xclient;
typedef struct xserver xserver;
typedef struct xsession xsession;
typedef struct xclientsocket xclientsocket;
typedef struct xserversocket xserversocket;
typedef struct xsessionsocket xsessionsocket;
typedef struct xsocket xsocket;
typedef struct xclientpool xclientpool;

typedef xsocket * (*xsocketdestructor)(xsocket *);
typedef xdescriptor * (*xdescriptordestructor)(xdescriptor *);

#include <x/descriptor/mask.h>
#include <x/descriptor/event/type.h>
#include <x/descriptor/status.h>
#include <x/socket/event/type.h>
#include <x/socket/status.h>

#endif // __NOVEMBERIZING_X__IO__H__
