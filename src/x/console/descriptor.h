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
typedef xint64 (*xconsoledescriptorprocessor)(xconsoledescriptor *, xuint32, void *);             /**!< 디스크립터 이벤트 프로세서 */
typedef xint64 (*xconsoledescriptorsubscriber)(xconsoledescriptor *, xuint32, void *, xint64);    /**!< 디스크립터 이벤트 서브스크리라이버 */
typedef xint32 (*xconsoledescriptorcheck)(xconsoledescriptor *, xuint32);

struct xconsoledescriptor
{
    /** INHERITED EVENT TARGET */
    xconsoledescriptordestructor            rem;            /**!< destructor */
    xconsoledescriptoreventsubscription *   subscription;   /**!< subscription */
    xsync *                                 sync;           /**!< synchronization */
    xuint32                                 mask;           /**!< mask */
    xuint32                                 status;         /**!< status */
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle                       handle;         /**!< descriptor handle */
    xconsoledescriptorprocessor             process;        /**!< descriptor process function */
    xconsoledescriptorcheck                 check;          /**!< descriptor status checker  */
    xconsoledescriptorsubscriber            on;             /**!< descriptor event subscriber */
    xconsoledescriptorevent                 event;          /**!< descriptor default event */
    xexception                              exception;      /**!< descriptor exception */
    /** CONSOLE DESCRIPTOR MEMBER */
    xconsole *                              console;        /** console */
    xstream *                               stream;         /** stream */
};

#endif // __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR__H__
