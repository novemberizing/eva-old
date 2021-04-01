#ifndef   __NOVEMBERIZING_X__REQUEST__H__
#define   __NOVEMBERIZING_X__REQUEST__H__

#include <x/std.h>
#include <x/time.h>
#include <x/stream.h>

struct xrequest;
struct xresponse;

typedef struct xrequest xrequest;
typedef struct xresponse xresponse;

typedef xrequest * (*xrequestdestructor)(xrequest *);
typedef xint32 (*xrequestserializer)(xrequest *, xstream *);


struct xrequest
{
    xrequestdestructor rem;
    xtime time;
    xrequestserializer serialize;
};

/**
 * xresponse * response = xclientreq(client, xrequestgen(...));
 * xresponsecheck(response, xresponsestatus_complete, 1, 0);
 * xresponse * response = xresponsewait(xclientreq(client, xrequestgen(...)), xresponsestatus_complete, 1, 0);
 * if(xresponsecheck(response, xresponsestatus_complete))
 * {
 *      ....
 * }
 */

#endif // __NOVEMBERIZING_X__REQUEST__H__
