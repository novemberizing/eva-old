#ifndef   __NOVEMBERIZING_X__COMMAND__STRING__H__
#define   __NOVEMBERIZING_X__COMMAND__STRING__H__

#include <x/command.h>

struct xcommandstring;

typedef struct xcommandstring xcommandstring;

typedef void (*xcommandstringcall)(xcommandstring *);

struct xcommandstring
{
    xcommandstringcall       exec;
    struct { char ** cntr; 
             xuint64 size; } strings;
};

extern const char ** xcommandstringscntr_get(xcommandstring * command);
extern xuint64 xcommandstringssize_get(xcommandstring * command);

extern xcommandstring * xcommandstringfrom_line(const char * line, xcommandstringcall exec);

extern xcommandstring * xcommandstring_rem(xcommandstring * command);

#endif // __NOVEMBERIZING_X__COMMAND__STRING__H__
