#ifndef   __NOVEMBERIZING_X__COMMAND__STRING__H__
#define   __NOVEMBERIZING_X__COMMAND__STRING__H__

#include <x/command.h>

struct xcommandstring;

typedef struct xcommandstring xcommandstring;

typedef void (*xcommandstringcall)(xcommandstring *, const char **, xuint64);

struct xcommandstring
{
    xcommandstringcall       exec;
    struct { char ** cntr; 
             xuint64 size; } strings;
};

extern xcommandstring * xcommandstringfrom_line(const char * line, xcommandstringcall exec);

#endif // __NOVEMBERIZING_X__COMMAND__STRING__H__
