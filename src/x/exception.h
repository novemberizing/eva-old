#ifndef   __NOVEMBERIZING_X__EXCEPTION__H__
#define   __NOVEMBERIZING_X__EXCEPTION__H__

#include <x/std.h>

#define xexceptiontype_void                     0
#define xexceptiontype_system                   1
#define xexceptiontype_user                     2
#define xexceptiontype_descriptor               3
#define xexceptiontype_lib                      4

struct xexception;

typedef struct xexception xexception;

struct xexception
{
    void *       func;
    xint32       number;
    xuint32      type;
    const char * message;
};

#define xexception_void     ((xexception) { xnil, 0, 0, xnil })

extern void xexceptionset(xexception * exception, void * func, xint32 number, xuint32 type, const char * message);
extern xint32 xexceptionno(xint32 number);

#endif // __NOVEMBERIZING_X__EXCEPTION__H__
