#ifndef   __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR__H__

#include <x/std.h>
#include <x/exception.h>
#include <x/sync.h>
#include <x/stream.h>
#include <x/console.h>
#include <x/descriptor.h>
#include <x/descriptor/event/subscription.h>
#include <x/console/descriptor/event.h>
#include <x/console/descriptor/event/subscription.h>

typedef xconsoledescriptor * (*xconsoledescriptordestructor)(xconsoledescriptor *);
typedef xint64 (*xconsoledescriptorprocessor)(xconsoledescriptor *, xuint32, xdescriptorparam);             /**!< 디스크립터 이벤트 프로세서 */
typedef xint64 (*xconsoledescriptorobserver)(xconsoledescriptor *, xuint32, xdescriptorparam, xint64);    /**!< 디스크립터 이벤트 서브스크리라이버 */
typedef xint32 (*xconsoledescriptorchecker)(xconsoledescriptor *, xuint32);

struct xconsoledescriptor
{
    /** INHERITED EVENT TARGET */
    xconsoledescriptordestructor            rem;            /**!< destructor */
    xconsoledescriptoreventsubscription *   subscription;   /**!< subscription */
    xsync *                                 sync;           /**!< synchronization */
    xuint32                                 mask;           /**!< mask */
    xuint32                                 status;         /**!< status */
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle                       handle;         /**!< descriptor handle */
    xconsoledescriptorprocessor             process;        /**!< descriptor process function */
    xconsoledescriptorchecker               check;          /**!< descriptor status checker  */
    xconsoledescriptorobserver              on;             /**!< descriptor event subscriber */
    xconsoledescriptorevent                 event;          /**!< descriptor default event */
    xexception                              exception;      /**!< descriptor exception */
    /** CONSOLE DESCRIPTOR MEMBER */
    xconsole *                              console;        /** console */
    xstream *                               stream;         /** stream */
};

/**
 * 사용자는 몰라야 하는 메서드 하지만, 내부에서는 사용되어져쟈 한다.
 */
extern xconsoledescriptor * xconsoledescriptordestruct(xconsoledescriptor * descriptor);
extern xint32 xconsoledescriptorstatuscheck(xconsoledescriptor * descriptor, xuint32 status);




#endif // __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR__H__
