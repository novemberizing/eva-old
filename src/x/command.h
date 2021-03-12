#ifndef   __NOVEMBERIZING_X__COMMAND__H__
#define   __NOVEMBERIZING_X__COMMAND__H__

#include <x/std.h>
#include <x/function.h>

struct xcommand;

typedef struct xcommand xcommand;

typedef void (*xcommandcall)(xcommand * o);

struct xcommand
{
    xcommandcall exec;
};

#define xfunctionexec(o)    (o->exec(o))

#endif // __NOVEMBERIZING_X__COMMAND__H__
