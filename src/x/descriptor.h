/**
 * @file        x/descriptor.h
 * @brief       [internal] 디스크립터 객체, 가상 함수를 정의한 파일입니다.
 * 
 * 정리가 필요하다.
 * 
 * 실 사용자는 타입의 존재하는 것만 알고 객체의 멤버는 확인할 수 없다.
 * 
 * 그렇기 때문에 이 파일은 내부에서만 사용되어 진다.
 */
#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include <x/io.h>

#include <x/exception.h>

#include <x/descriptor/handle.h>
#include <x/descriptor/event.h>

union xdescriptorparam;

#define xdescriptorsystemno_max     2

struct xdescriptoreventsubscription;

typedef union xdescriptorparam xdescriptorparam;

typedef struct xdescriptoreventsubscription xdescriptoreventsubscription;

typedef xint64 (*xdescriptorobserver)(xdescriptor *, xuint32, xdescriptorparam, xint64);
typedef xint64 (*xdescriptorprocessor)(xdescriptor *, xuint32);
typedef xint32 (*xdescriptorstatuschecker)(xdescriptor *, xuint32);

/**
 * @struct      xdescriptor
 * @brief       이벤트 디스크립터 객체
 * @details
 * 
 * @todo        사용자는 인터페이스 말고는 몰라야 한다.
 */
struct xdescriptor
{
    /** INHERITED EVENT TARGET */
    xdescriptordestructor          rem;            /**!< destructor */
    xdescriptoreventsubscription * subscription;   /**!< subscription */
    xsync *                        sync;           /**!< synchronization */
    xuint32                        mask;           /**!< mask */
    xuint32                        status;         /**!< status */
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle              handle;         /**!< descriptor handle */
    xdescriptorprocessor           process;        /**!< descriptor process function */
    xdescriptorstatuschecker       check;          /**!< descriptor status checker  */
    xdescriptorobserver            on;             /**!< descriptor event subscriber */
    xdescriptorevent               event;          /**!< descriptor default event */
    xexception                     exception;      /**!< descriptor exception */
};

union xdescriptorparam
{
    void * p;
    const void * c;
};

#define xdescriptorparamgen(v)          (xdescriptorparam) { .p = v }
#define xdescriptorparamgen_const(v)    (xdescriptorparam) { .c = v }

extern xint64 xdescriptoron(xdescriptor * descriptor, xuint32 event, xdescriptorparam param, xint64 result);

extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size);
extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len);
extern xint64 xdescriptorclose(xdescriptor * descriptor);
extern xint64 xdescriptorexception(xdescriptor * descriptor, void * func, xint32 number, xuint32 type, const char * message);

extern xint32 xdescriptornonblock(xdescriptor * descriptor, xint32 on);

// extern xint64 xdescriptoreventdispatch(xdescriptor * descriptor, xuint32 event);




// extern xuint32 xdescriptorstatus_get(xdescriptor * descriptor);


// extern xint64 xdescriptorclose(xdescriptor * descriptor);
// extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size);
// extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len);
// extern xint64 xdescriptorclear(xdescriptor * descriptor);
// extern xint32 xdescriptornonblock(xdescriptor * descriptor, xint32 on);



// extern xint64 xdescriptoreventdispatch(xdescriptor * descriptor, xuint32 event);

// extern xuint32 xdescriptorstatus_get(xdescriptor * descriptor);

// extern xdescriptoreventsubscription * xdescriptoreventsubscription_get(xdescriptor * descriptor);

// extern const char * xdescriptoreventtype_str(xuint32 event);

// extern xint64 xdescriptoreventprocess(xdescriptor * descriptor, xuint32 event);

// static xint64 xdescriptoreventprocess_void(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_open(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_in(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_out(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_close(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_exception(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_rem(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_register(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_readoff(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_writeoff(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_opening(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_create(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_bind(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_alloff(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_connect(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_listen(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_connecting(xdescriptor * descriptor, xdescriptorobserver on);
// static xint64 xdescriptoreventprocess_unregister(xdescriptor * descriptor, xdescriptorobserver on);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
