/**
 * 
 * xeventengine * engine = xeventengine_new();
 * 
 * ```
 * xeventengine * engine = xeventengine_new();
 * ...
 * return xeventengine_run(engine);
 * ```
 * 
 * 
 * 이벤트 엔진의 상태는 어떤 변수로 설정할 수 있는가 ?
 */
#ifndef   __NOVEMBERIZING_X__EVENT__ENGINE__H__
#define   __NOVEMBERIZING_X__EVENT__ENGINE__H__

#include <x/event.h>
#include <x/event/queue.h>

#include <x/descriptor.h>
#include <x/console.h>
#include <x/event/subscription/list.h>
#include <x/event/generator/set.h>
#include <x/descriptor/event/generator.h>

#define xeventenginestatus_off      1

typedef void (*xeventenginesubscriber)(xeventengine *, xuint32);
typedef void (*xeventenginefunc)(xeventengine *);       /**!< 이벤트 엔진의 기본 가상 함수입니다. */

/**
 * 사용자는 이벤트 엔진 객체의 내부를 알아야 할 필요가 없습니다.
 * 사용자는 인터페이스만 알고 내부 멤버는 PRIVATE 으로 사용자가 알아야 하지 않습니다.
 * 다만, 스택에 구조체를 생성할 경우는 ... 
 */
struct xeventengine
{
    xeventenginesubscriber                             on;
    xeventenginefunc                                   cancel;
    xeventqueue *                                      queue;
    xeventqueue *                                      main;
    xsync *                                            sync;
    xeventsubscriptionlist                             subscriptions;
    xeventgeneratorset                                 generators;
    xeventprocessorpool *                              processors;
};

extern xeventengine * xeventengine_new(void);
extern xint32 xeventengine_run(xeventengine * engine);
extern void xeventengine_cancel(xeventengine * engine, xeventenginefunc callback);

extern void xeventengine_sync(xeventengine * engine, xint32 on);

extern xint32 xeventengine_descriptor_dispatch(xdescriptor * descriptor, xuint32 event);
extern xint32 xeventengine_event_dispatch(xeventengine * engine, xevent * event);

extern xeventsubscription * xeventengine_descriptor_register(xeventengine * engine, xdescriptor * descriptor);
extern xeventsubscription * xeventengine_descriptor_unregister(xeventengine * engine, xdescriptor * descriptor);

extern xeventsubscription * xeventengine_server_register(xeventengine * engine, xserver * server);
extern xeventsubscription * xeventengine_server_unregister(xeventengine * engine, xserver * server);

extern xeventsubscription * xeventengine_session_register(xeventengine * engine, xsession * session);
extern xeventsubscription * xeventengine_session_unregister(xeventengine * engine, xsession * session);

extern void xeventengine_clientpool_register(xeventengine * engine, xclientpool * pool);
extern void xeventengine_clientpool_unregister(xeventengine * engine, xclientpool * pool);

extern xeventsubscription * xeventengine_client_register(xeventengine * engine, xclient * client);
extern xeventsubscription * xeventengine_client_unregister(xeventengine * engine, xclient * client);

extern void xeventengine_main_push(xeventengine * engine, xevent * event);
extern void xeventengine_queue_push(xeventengine * engine, xevent * event);

#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
