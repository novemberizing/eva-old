#ifndef   __NOVEMBERIZING_X__EXTENSION__ECHO_REQ__H__
#define   __NOVEMBERIZING_X__EXTENSION__ECHO_REQ__H__

#include <x/req.h>

struct xechoreq;
struct xechores;

typedef struct xechoreq xechoreq;
typedef struct xechores xechores;

typedef xechoreq * (*xechoreqdestructor)(xechoreq *);
typedef xint64 (*xechoreqserializer)(xechoreq *, xstream *);
typedef xechores * (*xechoresgenerator)(xechoreq *);

struct xechoreq
{
    /** INHERITED REQ */
    xechoreqdestructor rem;
    xtime              start;
    xtime              end;
    xechoreqserializer serialize;
    xechoresgenerator  gen;
    /** ECHO REQ MEMBER */
    xuint64            size;
    char *             data;
};

extern xechoreq * xechoreqnew(const char * s);
extern xechoreq * xechoreqrem(xechoreq * o);

#endif // __NOVEMBERIZING_X__EXTENSION__ECHO_REQ__H__
