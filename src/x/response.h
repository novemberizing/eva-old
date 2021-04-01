#ifndef   __NOVEMBERIZING_X__RESPONSE__H__
#define   __NOVEMBERIZING_X__RESPONSE__H__

#include <x/std.h>
#include <x/time.h>
#include <x/stream.h>

struct xresponse;
struct xrequest;

typedef struct xresponse xresponse;
typedef struct xrequest xrequest;

typedef xresponse * (*xresponsedestructor)(xresponse *);
typedef xint32 (*xresponsestatuscheker)(xresponse *);
typedef xint32 (*xresponsedeserializer)(xresponse *, xstream *);

struct xresponse
{
    xresponsedestructor rem;
    xtime time;
    xrequest * request;
    xresponsestatuscheker check;
};

#endif // __NOVEMBERIZING_X__RESPONSE__H__
